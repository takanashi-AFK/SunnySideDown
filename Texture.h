#pragma once
#pragma once
#include <d3d11.h>
#include "string"
#include"D3D.h"
#include <wincodec.h>

class Texture
{

	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();

	HRESULT LoadFromCommonPic(std::string fileName);
	HRESULT LoadFromOtherPic(std::string fileName);

	ID3D11SamplerState* GetSampler();
	ID3D11ShaderResourceView* GetSRV();

	void CreateSampler();
	void CreateSRV(ID3D11Texture2D* _pTexture);

	wchar_t* MulchByteToWide(std::string _fileName);

	ID3D11Texture2D* CreateDX11Texture(UINT _imgWidth, UINT _imgHeight, IWICFormatConverter* _pFormatConverter);

};

//D3Dのインスタンスも引数でとれるようにしたほうがいいのかな


