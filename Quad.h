#pragma once

#include "D3D.h"
#include <DirectXMath.h>
#include "AssimpLoader.h"
using namespace DirectX;

const string modelFile = "Assets/Alicia/FBX/Alicia_solid_Unity.FBX";

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};


class Quad
{
public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	 
	vector<Mesh> importMeshes;
	vector<Vertex> meshVertex;
	vector<uint32_t> meshIndex;
};