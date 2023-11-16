#pragma once

//インクルード
#include <Windows.h>
#include <d3d11.h>
#include"Global.h"
#include "Window.h"

//リンカ
#pragma comment(lib, "d3d11.lib")

class D3D
{
public:
	D3D();
	D3D(HWND _hWnd);
	~D3D();
	void SetSCchain();
	void CreateDevContSc();
	void CreateRenderTargetView();
	void SettingViewPort();
	void Initialize();

	ID3D11Device GetDevice();
	ID3D11DeviceContext GetContext();
	IDXGISwapChain GetSC();
	ID3D11RenderTargetView GetRenderTargetView();


	ID3D11Device* pDevice;		//デバイス
	ID3D11DeviceContext* pContext;		//デバイスコンテキスト
	IDXGISwapChain* pSwapChain;		//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;	//レンダーターゲットビュー

	HWND hWnd_;
	DXGI_SWAP_CHAIN_DESC scDesc;
};

