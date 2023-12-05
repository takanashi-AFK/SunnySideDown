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

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
};