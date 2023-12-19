#include "D3D.h"
#include <iostream>
#include <d3dcompiler.h>


D3D::D3D():
	scDesc({}),

	pDevice(nullptr),
	pContext(nullptr),
	pSwapChain(nullptr),
	pRenderTargetView(nullptr),
	pVertexLayout(nullptr),

	pVertexShader(nullptr),
	pPixelShader(nullptr),
	pRasterizerState(nullptr)
{
}

D3D::~D3D()
{
}

void D3D::Initialize(HWND _hWnd)
{
	hWnd_ = _hWnd;
	SetSCchain();
	CreateDevContSc();
	CreateRenderTargetView();
	SettingViewPort();
	InitShader();
}

void D3D::InitShader()
{
	InitVertexShader();
	InitPixelShader();
	CreateRasterizer();

	//setting for Device Context
	pContext->VSSetShader(pVertexShader, NULL, 0);	//VertexShader
	pContext->PSSetShader(pPixelShader, NULL, 0);	//PixelShader
	pContext->IASetInputLayout(pVertexLayout);	//VertexShader
	pContext->RSSetState(pRasterizerState);		//Rasterizer
}

void D3D::InitVertexShader()
{// create Vertex Shader
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);

	pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);

	//Vartex Input Layout
	//���͂��ꂽ�o�b�t�@���ǂ�ȃf�[�^�\����
	D3D11_INPUT_ELEMENT_DESC layout[] = {	
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::XMFLOAT2), D3D11_INPUT_PER_VERTEX_DATA, 0},	//�e�N�X�`���iUV�j���W
	};

	pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);

	pCompileVS->Release();
}

void D3D::InitPixelShader()
{// create Pixel Shader
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);

	pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);

	pCompilePS->Release();
}

void D3D::CreateRasterizer()
{//Create Rasterizer

	D3D11_RASTERIZER_DESC rdc = {};

	//////////CULL MODE IS HERE//////////
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	//////////CULL MODE IS HERE//////////

	rdc.FrontCounterClockwise = FALSE;
	pDevice->CreateRasterizerState(&rdc, &pRasterizerState);
}



void D3D::SetSCchain()
{

	///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
	//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
	ZeroMemory(&scDesc, sizeof(scDesc));

	//�`���̃t�H�[�}�b�g
	scDesc.BufferDesc.Width = WINDOW_WIDTH;		//��ʕ�
	scDesc.BufferDesc.Height = WINDOW_HEIGHT;	//��ʍ���
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

	//FPS�i1/60�b��1��j
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//���̑�
	scDesc.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
	scDesc.OutputWindow = hWnd_;		//�E�B���h�E�n���h��
	scDesc.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
	scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
	scDesc.SampleDesc.Quality = 0;		//�@�V
}

void D3D::CreateDevContSc()
{
	////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬////////////////////////
	D3D_FEATURE_LEVEL level;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,				// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
		D3D_DRIVER_TYPE_HARDWARE,		// �h���C�o�̃^�C�v��n���B�ӂ���HARDWARE
		nullptr,				// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵�Ȃ�������nullptr
		0,					// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
		nullptr,				// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ���OK
		0,					// ��̈����Ń��x�������w�肵����
		D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
		&scDesc,				// ��ł��낢��ݒ肵���\����
		&pSwapChain,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
		&pDevice,				// ������������Device�A�h���X���Ԃ��Ă���
		&level,					// ������������Device�AContext�̃��x�����Ԃ��Ă���
		&pContext);				// ������������Context�̃A�h���X���Ԃ��Ă���

	if (FAILED(hr)) {
		char msg[128];
		sprintf_s(msg, "D3D11CreateDeviceAndSwapChain failed with error 0x%X", hr);
		MessageBoxA(nullptr, msg, "Error", MB_OK | MB_ICONERROR);
		
	}
}

void D3D::CreateRenderTargetView()
{
	///////////////////////////�����_�[�^�[�Q�b�g�r���[�쐬///////////////////////////////
	//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� �����_�[�^�[�Q�b�g�j
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//�����_�[�^�[�Q�b�g�r���[���쐬
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŉ��
	pBackBuffer->Release();
}

void D3D::SettingViewPort()
{
	///////////////////////////�r���[�|�[�g�i�`��͈́j�ݒ�///////////////////////////////
	//�����_�����O���ʂ�\������͈�
	D3D11_VIEWPORT vp;
	vp.Width = (float)WINDOW_WIDTH;	//��
	vp.Height = (float)WINDOW_HEIGHT;//����
	vp.MinDepth = 0.0f;	//��O
	vp.MaxDepth = 1.0f;	//��
	vp.TopLeftX = 0;	//��
	vp.TopLeftY = 0;	//��

	//�[�x�X�e���V���r���[�̍쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);

	//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�i�p�C�v���C���j
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);            // �`����ݒ�
	pContext->RSSetViewports(1, &vp);
}

void D3D::Release()
{
	pRasterizerState->Release();
	pVertexLayout->Release();
	pPixelShader->Release();
	pVertexShader->Release();

	pRenderTargetView->Release();
	pSwapChain->Release();
	pContext->Release();
	pDevice->Release();
}

void D3D::Draw()
{
	//�Q�[���̏���
	//�w�i�̐F
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//��ʂ��N���A
	pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	//�[�x�o�b�t�@�N���A
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}



void D3D::Update()
{
	//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
	pSwapChain->Present(0, 0);
}