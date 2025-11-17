#include "WinApp.h"
#include <windows.h>
#include <cassert>
#include <objbase.h>
#include <iostream>
#include <cstdint>

void WinApp::Initialize()
{
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	//WNDCLASS wc{};
	// ウィンドウプロシーシャ
	wc.lpfnWndProc = WindowProc;
	// ウィンドウクラス名（なんでもいい）
	wc.lpszClassName = L"CG2WindowClass";
	// インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	// カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&wc);

	

	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	// クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	/*HWND*/ hwnd = CreateWindow(
		wc.lpszClassName,      // 利用するクラス名
		L"CG2",                // タイトルバーの文字(なんでもいい)
		WS_OVERLAPPEDWINDOW,   // よく見るウィンドウスタイル
		CW_USEDEFAULT,		   // 表示X座標(Windowsに任せる)
		CW_USEDEFAULT,		   // 表示Y座標(WindowsOSに任せる)
		wrc.right - wrc.left,  // ウィンドウ横幅
		wrc.bottom - wrc.top,  // ウィンドウ立幅
		nullptr,			   // 親ウィンドウハンドル
		nullptr,			   // メニューハンドル
		wc.hInstance,		   // インスタンスハンドル
		nullptr				   // オプション
	);
	// ウィンドウを表示
	ShowWindow(hwnd, SW_SHOW);
}
void WinApp::Update()
{
	//メッセージ処理
}
void WinApp::Finalize()
{
	CloseWindow(hwnd);
	// COMライブラリの終了
	CoUninitialize();
}
LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// メッセージに応じて対応した処理を行う
	switch (msg)
	{
	case WM_DESTROY: // ウィンドウが閉じられたら
		// OSに対して、このプログラムの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 上記以外のメッセージは、デフォルトのプロシージャに処理を任せる
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool WinApp::ProcessMessage()
{

	MSG msg{};

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	if (msg.message == WM_QUIT)
	{
		return true;
	}
	return false;
}