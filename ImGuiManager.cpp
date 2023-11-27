#include "ImGuiManager.h"

void ImGuiManager::Initialize(HWND _hWnd,D3D *_pD3D)
{
	IMGUI_CHECKVERSION();	//ImGui�����o�[�W�������m�F
	ImGui::CreateContext();	//�R���e�L�X�g���쐬
	ImGuiIO& io = ImGui::GetIO();	//�K�v�ȃf�[�^���擾
	ImGui::StyleColorsDark();	//�J���[�����ɐݒ�

	//ImGui��������
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(_pD3D->pDevice, _pD3D->pContext);
}

void ImGuiManager::Update()
{
}
