//�C���N���[�h
#include <Windows.h>
#include"Window.h"
#include"D3D.h"


//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Window* pWnd = new Window(hInstance, nCmdShow);
	pWnd->Initialize();
	pWnd->Execute();




	return 0;
}