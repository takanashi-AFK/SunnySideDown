#pragma once

//�C���N���[�h
#include <Windows.h>
#include"Global.h"
#include"ImGuiManager.h"

class D3D;
class Quad;
class Window
{
public:
	Window();
	Window(HINSTANCE _hInstance, int nCmdShow);
	~Window();

	void Initialize();

	void CreateWndClass();

	void Execute();

	void MsgLoop();

	HWND GetHWnd();



	void Release();
private:
	HINSTANCE hInstance_;
	int nCmdShow_;
	HWND hWnd;
	Quad *qu;
};

//�v���g�^�C�v�錾
 LRESULT static CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
