#include "Quad.h"
#include "AssimpLoader.h"
using namespace DirectX;


Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::Initialize()
{
	ImportSettings importSetting = // これ自体は自作の読み込み設定構造体
	{
		modelFile,
		importMeshes,
		false,
		true // アリシアのモデルは、テクスチャのUVのVだけ反転してるっぽい？ので読み込み時にUV座標を逆転させる
	};

	D3D& pD3D = D3D::GetInstance();
	//importMeshes.clear();
	//importMeshes.reserve();
	//importSetting.filename = modelFile;
	//importSetting.meshes

	AssimpLoader loader = {};

	if (!loader.Load(&importSetting))
	{
		auto l = 0;
		MessageBox(NULL, "LoaderError", "error!", 0);
	}

	for (const auto& mesh : importMeshes)
	{		
		meshVertex = mesh.Vertices;

		ID3D11Buffer* pVertexBuffer;
		// 頂点データ用バッファの設定
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(Vertex) * meshVertex.size();
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex{};

		data_vertex.pSysMem = meshVertex.data();
		pD3D.pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer);

		pVertexBufferList_.push_back(pVertexBuffer);

		meshIndex = mesh.Indices;

		// インデックスバッファを生成する
		ID3D11Buffer* pIndexBuffer;
		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(uint32_t) * meshIndex.size();
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
	
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = meshIndex.data();
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		pD3D.pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer);

		pIndexBufferList_.push_back(pIndexBuffer);

		//コンスタントバッファ作成
		ID3D11Buffer* pConstantBuffer ;
		D3D11_BUFFER_DESC cb;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// コンスタントバッファの作成
		pD3D.pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer);

		pConstantBufferList_.push_back(pConstantBuffer);
	}
}

void Quad::Draw()
{
	D3D& pD3D = D3D::GetInstance();
	for (int i = 0;i < importMeshes.size();++i)
	{
		//コンスタントバッファに渡す情報
		XMVECTOR position = { 0, 140, 100, 0 };	//カメラの位置
		XMVECTOR target = { 0, 120, 0, 0 };	//カメラの焦点
		XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
		XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);//射影行列

		CONSTANT_BUFFER cb;
		cb.matWVP = XMMatrixTranspose(view * proj);//ここにあとでworldMatrixかける
		D3D11_MAPPED_SUBRESOURCE pdata;
		pD3D.pContext->Map(pConstantBufferList_[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
		pD3D.pContext->Unmap(pConstantBufferList_[i], 0);	//再開

		//頂点バッファ
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pD3D.pContext->IASetVertexBuffers(0, 1, &pVertexBufferList_[i], &stride, &offset);

		// インデックスバッファーをセット
		pD3D.pContext->IASetIndexBuffer(pIndexBufferList_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		pD3D.pContext->VSSetConstantBuffers(0, 1, &pConstantBufferList_[i]);	//頂点シェーダー用	
		pD3D.pContext->PSSetConstantBuffers(0, 1, &pConstantBufferList_[i]);	//ピクセルシェーダー用
		pD3D.pContext->DrawIndexed(importMeshes[i].Indices.size(), 0, 0);

	}
}

void Quad::Release()
{
}
