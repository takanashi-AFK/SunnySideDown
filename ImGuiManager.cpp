#include "ImGuiManager.h"

void ImGuiManager::Initialize(HWND _hWnd,D3D *_pD3D)
{
	IMGUI_CHECKVERSION();	//ImGui導入バージョンを確認
	ImGui::CreateContext();	//コンテキストを作成
	ImGuiIO& io = ImGui::GetIO();	//必要なデータを取得
	ImGui::StyleColorsDark();	//カラーを黒に設定

	//ImGuiを初期化
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(_pD3D->pDevice, _pD3D->pContext);
}

void ImGuiManager::Update()
{
}
