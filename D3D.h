#pragma once

//�C���N���[�h
#include <Windows.h>
#include <d3d11.h>
#include"Global.h"
#include "Window.h"
#include<DirectXMath.h>


//�����J
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

	ID3D11Device* pDevice;						//�f�o�C�X
	ID3D11DeviceContext* pContext;				//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain;					//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	ID3D11InputLayout* pVertexLayout;			//���_�C���v�b�g���C�A�E�g

	ID3D11Texture2D* pDepthStencil;			//�[�x�X�e���V��
	ID3D11DepthStencilView* pDepthStencilView;		//�[�x�X�e���V���r���[

	//Shader//
	void InitShader();
	void InitVertexShader();
	void InitPixelShader();
	void CreateRasterizer();
	void StartDraw();
	void EndDraw();

	ID3D11VertexShader* pVertexShader;			//���_�V�F�[�_�[
	ID3D11PixelShader* pPixelShader;			//�s�N�Z���V�F�[�_�[
	ID3D11RasterizerState* pRasterizerState;	//���X�^���C�U�[


	//other
	HWND hWnd_;
	DXGI_SWAP_CHAIN_DESC scDesc;
  	void Release();
};

