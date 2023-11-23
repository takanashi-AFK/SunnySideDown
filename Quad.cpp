#include "Quad.h"



Quad::Quad()
{
}

Quad::Quad(D3D* _D3D)
	:pD3D(_D3D)
{
}

Quad::~Quad()
{
}

void Quad::Initialize()
{

	// VertexData
	XMVECTOR vertices[] =
	{
		XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	// TopLeft
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	// TopRight
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	// BotLeft	
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	// BotRight
	};

	// VertexBufferSetting
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	pD3D->pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

	//IndexData
	int index[] = { 0,2,3, 0,1,2 };

	// Generate Index Buffer
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	pD3D->pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	//Create Constant Buffer
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	pD3D->pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

void Quad::Draw()
{
	//コンスタントバッファに渡す情報
	XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(view * proj);

	D3D11_MAPPED_SUBRESOURCE pdata;
	pD3D->pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	pD3D->pContext->Unmap(pConstantBuffer_, 0);	//再開


	//頂点バッファ
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	pD3D->pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	pD3D->pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	pD3D->pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	pD3D->pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	pD3D->pContext->DrawIndexed(6, 0, 0);
}

void Quad::Release()
{
}
