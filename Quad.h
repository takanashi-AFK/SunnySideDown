#pragma once

#include "D3D.h"
class Quad
{
public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
};