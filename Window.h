#pragma once

//インクルード
#include <Windows.h>
#include"Global.h"
#include"D3D.h"
class Window
{
public:
	Window();
	Window(HINSTANCE _hInstance, int nCmdShow);
	~Window();
	void CreateWndClass();

	void Execute();

	void MsgLoop();

	HWND GetHWnd();

private:
	HINSTANCE hInstance_;
	int nCmdShow_;
	HWND hWnd;

};

//プロトタイプ宣言
 LRESULT static CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
