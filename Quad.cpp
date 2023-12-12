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

		D3D& pD3D = D3D::GetInstance();
		//importMeshes.clear();
		//importMeshes.reserve();

		ImportSettings importSetting = // ���ꎩ�͎̂���̓ǂݍ��ݐݒ�\����
		{
			modelFile,
			importMeshes,
			false,
			true // �A���V�A�̃��f���́A�e�N�X�`����UV��V�������]���Ă���ۂ��H�̂œǂݍ��ݎ���UV���W���t�]������
		};
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
			// ���_�f�[�^�p�o�b�t�@�̐ݒ�
			D3D11_BUFFER_DESC bd_vertex;
			bd_vertex.ByteWidth = sizeof(Vertex) * meshVertex.size();
			bd_vertex.Usage = D3D11_USAGE_DEFAULT;
			bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd_vertex.CPUAccessFlags = 0;
			bd_vertex.MiscFlags = 0;
			bd_vertex.StructureByteStride = 0;
			D3D11_SUBRESOURCE_DATA data_vertex;

			data_vertex.pSysMem = meshVertex.data();
			pD3D.pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);


			meshIndex = mesh.Indices;

			// �C���f�b�N�X�o�b�t�@�𐶐�����
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
			pD3D.pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

			//�R���X�^���g�o�b�t�@�쐬
			D3D11_BUFFER_DESC cb;
			cb.ByteWidth = sizeof(CONSTANT_BUFFER);
			cb.Usage = D3D11_USAGE_DYNAMIC;
			cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cb.MiscFlags = 0;
			cb.StructureByteStride = 0;

			// �R���X�^���g�o�b�t�@�̍쐬
			pD3D.pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
		}
	}

	void Quad::Draw()
	{
			D3D& pD3D = D3D::GetInstance();
		for (const auto& mesh : importMeshes)
		{
			//�R���X�^���g�o�b�t�@�ɓn�����
			XMVECTOR position = { 0, 0, -100, 0 };	//�J�����̈ʒu
			XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
			XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s��
			XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s��

			CONSTANT_BUFFER cb;
			cb.matWVP = XMMatrixTranspose(view * proj);

			D3D11_MAPPED_SUBRESOURCE pdata;
			pD3D.pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
			pD3D.pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

			//���_�o�b�t�@
			UINT stride = sizeof(XMVECTOR);
			UINT offset = 0;
			pD3D.pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

			// �C���f�b�N�X�o�b�t�@�[���Z�b�g
			stride = sizeof(int);
			offset = 0;
			pD3D.pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

			//�R���X�^���g�o�b�t�@
			pD3D.pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
			pD3D.pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
			pD3D.pContext->DrawIndexed(mesh.Vertices.size(), 0, 0);
		}
	}

	void Quad::Release()
	{
	}
