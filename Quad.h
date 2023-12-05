#pragma once

#include "D3D.h"

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
};