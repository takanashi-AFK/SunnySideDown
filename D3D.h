#pragma once

//インクルード
#include <Windows.h>
#include <d3d11.h>
#include"Global.h"
#include "Window.h"

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")



class D3D
{
public:
	D3D();
	D3D(HWND _hWnd);
	~D3D();
	//rendering

	/// <summary>
	/// Setting SwapChain struct
	/// </summary>
	void SetSCchain();

	/// <summary>
	/// Use SCData,Create Device,Context,and SwapChain
	/// </summary>
	void CreateDevContSc();

	void CreateRenderTargetView();
	void SettingViewPort();

	/// <summary>
	/// Execute those function
	/// </summary>
	void Initialize();

	ID3D11Device* pDevice;						//デバイス
	ID3D11DeviceContext* pContext;				//デバイスコンテキスト
	IDXGISwapChain* pSwapChain;					//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;	//レンダーターゲットビュー
	ID3D11InputLayout* pVertexLayout;			//頂点インプットレイアウト

	//Shader//
	void InitShader();

	ID3D11VertexShader* pVertexShader;			//頂点シェーダー
	ID3D11PixelShader* pPixelShader;			//ピクセルシェーダー
	ID3D11RasterizerState* pRasterizerState;	//ラスタライザー


	//other
	HWND hWnd_;
	DXGI_SWAP_CHAIN_DESC scDesc;

	void Release();
};

