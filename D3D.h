#pragma once

//�C���N���[�h
#include <Windows.h>
#include <d3d11.h>
#include"Global.h"
#include "Window.h"

//�����J
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

	ID3D11Device* pDevice;		//�f�o�C�X
	ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain;		//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView;	//�����_�[�^�[�Q�b�g�r���[

	HWND hWnd_;
	DXGI_SWAP_CHAIN_DESC scDesc;
};

