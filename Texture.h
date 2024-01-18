#pragma once
#pragma once
#include <d3d11.h>
#include "string"
#include"D3D.h"

class Texture
{

	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();

	bool LoadFromCommonPic(std::string fileName);
	bool LoadFromOtherPic(std::string fileName);

	ID3D11SamplerState* GetSampler();
	ID3D11ShaderResourceView* GetSRV();

};;

