#include "Window.h"
#include"D3D.h"
#include"Quad.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    //ImGuiに情報を渡す
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;


    return DefWindowProc(hWnd, msg, wParam, lParam);
}


Window::Window()
    :hInstance_(nullptr), nCmdShow_(0)
{
}


Window::Window(HINSTANCE _hInstance, int _nCmdShow)
    :hInstance_(_hInstance),nCmdShow_(_nCmdShow)
{
 
}


void Window::Initialize()
{
    CreateWndClass();
    pD3D = new D3D(hWnd);
    
    pD3D->Initialize();
    ImGuiManager::Initialize(hWnd,pD3D);

}

void Window::Execute()
{

    MsgLoop();
}

void Window::MsgLoop()
{
    //メッセージループ（何か起きるのを待つ）
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            //ゲームの処理
            pD3D->Update();
            //ImGuiの更新処理
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Hello, world!");//ImGuiの処理を開始
            {
                //この中にしたい処理を記述
                //描画されるボタンを押したら...
                if (ImGui::Button("button")) {
                    PostQuitMessage(0);	//プログラム終了
                }

            }
            ImGui::End();//ImGuiの処理を終了

        }
    }
}

HWND Window::GetHWnd()
{
    return hWnd;
}



void Window::Release()
{
    SAFE_RELEASE(pD3D);
    SAFE_DELETE(hWnd);
    SAFE_DELETE(hInstance_);
}


Window::~Window()
{
}


void Window::CreateWndClass()
{
    //ウィンドウクラス（設計図）を作成
    WNDCLASSEX wc = {};
    RegisterClassEx(&wc);  //クラスを登録

    //ウィンドウサイズの計算
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

    ////////////////クラスの設定///////////////
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance_;                   //インスタンスハンドル
    wc.lpszClassName = "SampleGame";            //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
    wc.lpszMenuName = NULL;                     //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
    RegisterClassEx(&wc); //クラスを登録
    ///////////////////////////////////////////
    
    ///////////////windowの詳細////////////////
    //ウィンドウを作成
    hWnd = CreateWindow(
        "SampleGame",         //ウィンドウクラス名
        "サンプルゲーム",     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,                 //ウィンドウ幅
        winH,                 //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance_,           //インスタンス
        NULL                 //パラメータ（なし）
    );
    ///////////////////////////////////////////
    ////ウィンドウを表示
    ShowWindow(hWnd, nCmdShow_);
}
