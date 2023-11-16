#include "D3D.h"

D3D::D3D()
{
}

D3D::D3D(HWND _hWnd)
	:hWnd_(_hWnd)
{

}

D3D::~D3D()
{
}

void D3D::Initialize()
{
	SetSCchain();
	CreateDevContSc();
	CreateRenderTargetView();
	SettingViewPort();
}

ID3D11Device D3D::GetDevice()
{
	return ID3D11Device();
}

ID3D11DeviceContext D3D::GetContext()
{
	return ID3D11DeviceContext();
}

IDXGISwapChain D3D::GetSC()
{
	return IDXGISwapChain();
}

ID3D11RenderTargetView D3D::GetRenderTargetView()
{
	return ID3D11RenderTargetView();
}

void D3D::SetSCchain()
{
	///////////////////////////いろいろ準備するための設定///////////////////////////////
	//いろいろな設定項目をまとめた構造体
	
	//とりあえず全部0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//描画先のフォーマット
	scDesc.BufferDesc.Width = WINDOW_WIDTH;		//画面幅
	scDesc.BufferDesc.Height = WINDOW_HEIGHT;	//画面高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

	//FPS（1/60秒に1回）
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
	scDesc.OutputWindow = hWnd_;		//ウィンドウハンドル
	scDesc.BufferCount = 1;			//バックバッファの枚数
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
	scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
	scDesc.SampleDesc.Quality = 0;		//　〃
}

void D3D::CreateDevContSc()
{
	////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,				// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,				// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		0,					// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,				// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,					// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,			// SDKのバージョン。必ずこの値
		&scDesc,				// 上でいろいろ設定した構造体
		&pSwapChain,				// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice,				// 無事完成したDeviceアドレスが返ってくる
		&level,					// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext);				// 無事完成したContextのアドレスが返ってくる
}

void D3D::CreateRenderTargetView()
{
	///////////////////////////レンダーターゲットビュー作成///////////////////////////////
	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//レンダーターゲットビューを作成
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	//一時的にバックバッファを取得しただけなので解放
	pBackBuffer->Release();
}

void D3D::SettingViewPort()
{
	///////////////////////////ビューポート（描画範囲）設定///////////////////////////////
	//レンダリング結果を表示する範囲
	D3D11_VIEWPORT vp;
	vp.Width = (float)WINDOW_WIDTH;	//幅
	vp.Height = (float)WINDOW_HEIGHT;//高さ
	vp.MinDepth = 0.0f;	//手前
	vp.MaxDepth = 1.0f;	//奥
	vp.TopLeftX = 0;	//左
	vp.TopLeftY = 0;	//上

	//データを画面に描画するための一通りの設定（パイプライン）
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
	pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);            // 描画先を設定
	pContext->RSSetViewports(1, &vp);
}
