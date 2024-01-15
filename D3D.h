#pragma once

//インクルード
#include <Windows.h>
#include <d3d11.h>
#include"Global.h"
#include "Window.h"
#include<DirectXMath.h>


//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

class Quad;

class D3D
{
private:
	D3D();
	~D3D();
public:
	static D3D& GetInstance() {
		static D3D instance;
		return instance;
	}

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
	void Initialize(HWND _hWnd);

	ID3D11Device* pDevice;						//デバイス
	ID3D11DeviceContext* pContext;				//デバイスコンテキスト
	IDXGISwapChain* pSwapChain;					//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;	//レンダーターゲットビュー
	ID3D11InputLayout* pVertexLayout;			//頂点インプットレイアウト

	ID3D11Texture2D* pDepthStencil;			//深度ステンシル
	ID3D11DepthStencilView* pDepthStencilView;		//深度ステンシルビュー

	//Shader//
	void InitShader();
	void InitVertexShader();
	void InitPixelShader();
	void CreateRasterizer();
	void StartDraw();
	void EndDraw();

	ID3D11VertexShader* pVertexShader;			//頂点シェーダー
	ID3D11PixelShader* pPixelShader;			//ピクセルシェーダー
	ID3D11RasterizerState* pRasterizerState;	//ラスタライザー


	//other
	HWND hWnd_;
	DXGI_SWAP_CHAIN_DESC scDesc;
  	void Release();
};

