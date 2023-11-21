#pragma once

//インクルード
#include <Windows.h>
#include"Global.h"


class D3D;
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
private:
	HINSTANCE hInstance_;
	int nCmdShow_;
	HWND hWnd;
	D3D* pD3D;
};

//プロトタイプ宣言
 LRESULT static CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
