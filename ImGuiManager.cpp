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
	//ImGuiの更新処理
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	Feature();
	ImGui::End();
	
}

void ImGuiManager::Draw()
{
	//ImGuiの描画処理
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Feature()
{
	ImGui::Begin("Hello, world!");//ImGuiの処理を開始
		//この中にしたい処理を記述
		//描画されるボタンを押したら...
		if (ImGui::Button("button")) {
			PostQuitMessage(0);	//プログラム終了
		}

}

void ImGuiManager::Release()
{
	//ImGuiの開放処理
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

}
