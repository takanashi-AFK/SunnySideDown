#include "Window.h"
#include"D3D.h"
//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //�v���O�����I��
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
void Window::Initialize()
{
    CreateWndClass();
    pD3D = new D3D(hWnd);
    
    pD3D->Initialize();
}

void Window::Execute()
{
   
    MsgLoop();
}

void Window::MsgLoop()
{
 
    //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            //�Q�[���̏���
            //�w�i�̐F
            float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

            //��ʂ��N���A
            pD3D->pContext->ClearRenderTargetView(pD3D->pRenderTargetView, clearColor);

            //�`�揈��
            //�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
            pD3D->pSwapChain->Present(0, 0);

        }
    }
}

HWND Window::GetHWnd()
{
    return hWnd;
}

Window::Window()
    :hInstance_(nullptr), nCmdShow_(0)
{
}

Window::Window(HINSTANCE _hInstance, int _nCmdShow)
    :hInstance_(_hInstance),nCmdShow_(_nCmdShow)
{
 
}

Window::~Window()
{
}


void Window::CreateWndClass()
{
    //�E�B���h�E�N���X�i�݌v�}�j���쐬
    WNDCLASSEX wc;
    RegisterClassEx(&wc);  //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

    ////////////////�N���X�̐ݒ�///////////////
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance_;                   //�C���X�^���X�n���h��
    wc.lpszClassName = "SampleGame";            //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
    wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
    RegisterClassEx(&wc); //�N���X��o�^
    ///////////////////////////////////////////
    
    ///////////////window�̏ڍ�////////////////
    //�E�B���h�E���쐬
    hWnd = CreateWindow(
        "SampleGame",         //�E�B���h�E�N���X��
        "�T���v���Q�[��",     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,                 //�E�B���h�E��
        winH,                 //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance_,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );
    ///////////////////////////////////////////
    ////�E�B���h�E��\��
    ShowWindow(hWnd, nCmdShow_);
}
