#pragma once

#include "D3D.h"
#include <DirectXMath.h>
#include "AssimpLoader.h"
#include <vector>
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

	vector<ID3D11Buffer*> pVertexBufferList_;	//���_�o�b�t�@
	vector<ID3D11Buffer*> pIndexBufferList_;
	vector<ID3D11Buffer*> pConstantBufferList_;	//�R���X�^���g�o�b�t�@

	vector<Mesh> importMeshes;
	vector<Vertex> meshVertex;
	vector<uint32_t> meshIndex;
};