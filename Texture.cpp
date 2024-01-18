#include "Texture.h"

#include<filesystem>

#pragma comment( lib, "WindowsCodecs.lib" )

Texture::Texture()
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(std::string fileName)
{
	HRESULT hr;
	std::filesystem::path filePath = fileName;
	std::string ext = filePath.extension().string();

	if (ext == ".png" || ext == ".jpeg" || ext == ".PNG" || ext == ".JPEG")
	{
		hr = LoadFromCommonPic(fileName);
		if (hr != S_OK) {
#ifdef _DEBUG
			MessageBox(nullptr, "LoadFromCommonPic", "Error!", 0);
#endif // _DEBUG
			return hr;
		}

			return S_OK;
	}

	if (ext == ".tga")
		hr = LoadFromOtherPic(fileName);
		if (hr != S_OK){
#ifdef _DEBUG
			MessageBox(nullptr, "LoadFromOtherPic", "Error!", 0);
#endif // _DEBUG
			return hr;
		}
	
	return S_OK;
}

void Texture::Release()
{
	delete pSampler_;
	delete pSRV_;
}

HRESULT Texture::LoadFromCommonPic(std::string _fileName)
{

	HRESULT hr;
	D3D& pD3D = D3D::GetInstance();
	wchar_t *pw_filename;
	pw_filename = MulchByteToWide(_fileName);

	hr = CoInitialize(nullptr);
	if (hr != S_OK)return hr;

	IWICImagingFactory* pFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pFormatConverter = nullptr;
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pFactory));

	hr = pFactory->CreateDecoderFromFilename(pw_filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (hr != S_OK)return hr;

	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK)return hr;
	pFactory->CreateFormatConverter(&pFormatConverter);
	hr = pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (hr != S_OK)return hr;

	UINT imgWidth;
	UINT imgHeight;

	ID3D11Texture2D* pTexture  = nullptr;
	pFormatConverter->GetSize(&imgWidth, &imgHeight);

	CreateDX11Texture(imgWidth,imgHeight, pFormatConverter);

	D3D11_MAPPED_SUBRESOURCE hMappedres;
	pD3D.pContext->Map(pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &hMappedres);
	pFormatConverter->CopyPixels(nullptr, imgWidth * 4, imgWidth * imgHeight * 4, (BYTE*)hMappedres.pData);
	pD3D.pContext->Unmap(pTexture, 0);

	CreateSampler();
	CreateSRV(pTexture);
	pTexture->Release();
	return S_OK;
}

HRESULT Texture::LoadFromOtherPic(std::string fileName)
{
	return S_OK;
}


ID3D11SamplerState* Texture::GetSampler()
{
	return pSampler_;
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pSRV_;
}

void Texture::CreateSampler()
{
	D3D& pD3D = D3D::GetInstance();

	D3D11_SAMPLER_DESC  r_samDesc;
	ZeroMemory(&r_samDesc, sizeof(D3D11_SAMPLER_DESC));
	r_samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	r_samDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	r_samDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	r_samDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	pD3D.pDevice->CreateSamplerState(&r_samDesc, &pSampler_);
}

void Texture::CreateSRV(ID3D11Texture2D* _pTexture)
{

	D3D& pD3D = D3D::GetInstance();

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	pD3D.pDevice->CreateShaderResourceView(_pTexture, &srv, &pSRV_);

}

wchar_t* Texture::MulchByteToWide(std::string _fileName)
{
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, _fileName.c_str(), _fileName.length());
	return wtext;
}

ID3D11Texture2D* Texture::CreateDX11Texture(UINT _imgWidth, UINT _imgHeight, IWICFormatConverter* _pFormatConverter)
{
	D3D& pD3D = D3D::GetInstance();

	ID3D11Texture2D* pTexture;
	D3D11_TEXTURE2D_DESC texdec;
	texdec.Width = _imgWidth;
	texdec.Height = _imgHeight;
	texdec.MipLevels = 1;
	texdec.ArraySize = 1;
	texdec.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texdec.SampleDesc.Count = 1;
	texdec.SampleDesc.Quality = 0;
	texdec.Usage = D3D11_USAGE_DYNAMIC;
	texdec.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texdec.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texdec.MiscFlags = 0;
	pD3D.pDevice->CreateTexture2D(&texdec, nullptr, &pTexture);

	return pTexture;

}
