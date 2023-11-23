#pragma once

#include "D3D.h"
#include <DirectXMath.h>

using namespace DirectX;
//ConstantBuffer

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

class Quad
{
public:
	Quad();
	Quad(D3D* _D3D);
	~Quad();
	void Initialize();
	void Draw();
	void Release();

private:
	ID3D11Buffer* pVertexBuffer_;	//VertexBuffer
	ID3D11Buffer* pIndexBuffer_;	//IndexBuffer
	ID3D11Buffer* pConstantBuffer_;	//ConstantBuffer

	D3D* pD3D;
};