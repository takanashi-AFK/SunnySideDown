//インクルード
#include <Windows.h>
#include"Window.h"
#include"D3D.h"


//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Window* pWnd = new Window(hInstance, nCmdShow);
	pWnd->Initialize();
	pWnd->Execute();
	return 0;
}