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
	//ImGui�̍X�V����
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
}

void ImGuiManager::Draw()
{
	//ImGui�̕`�揈��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Feature()
{
	ImGui::Begin("Hello, world!");//ImGui�̏������J�n
		//���̒��ɂ������������L�q
		//�`�悳���{�^������������...
		if (ImGui::Button("button")) {
			PostQuitMessage(0);	//�v���O�����I��
		}
	ImGui::End();
}

void ImGuiManager::Release()
{
	//ImGui�̊J������
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

}
