#pragma once
#include <Windows.h>
#include "D3D.h"
//ImGui関連データのインクルード
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
class D3D;
namespace ImGuiManager
{
	void Initialize(HWND _hWnd, D3D* _pD3D);

	void Update();

	void Draw();

	void Feature();

	void Release();

};

