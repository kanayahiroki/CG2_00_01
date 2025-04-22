#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>




// ウインドウプロシージャ

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
	WPARAM wparam, LPARAM lparam) {
	//メッセージに対してゲーム固有の処理を行う
	switch (msg)
	{
		//ウインドウが破壊された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理を伝える
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
void Log(const std::string& message)
{
	OutputDebugStringA(message.c_str());
}


std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}


	auto sizeNeeded = MultiByteToWideChar(
		CP_UTF8,
		0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		NULL,
		0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(
		CP_UTF8,
		0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		&result[0],
		sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}
	auto sizeNeeded = WideCharToMultiByte(
		CP_UTF8,
		0,
		str.data(),
		static_cast<int>(str.size()),
		NULL,
		0,
		NULL,
		NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(
		CP_UTF8,
		0,
		str.data(),
		static_cast<int>(str.size()),
		result.data(),
		sizeNeeded,
		NULL,
		NULL);
	return result;
}

// windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	Log(ConvertString(std::format(L"WSTRING{}\n", L"abc")));
	


	// 文字列を格納する
	std::string str0("STRING!!!");

	// 整数を文字列にする
	std::string str1(std::to_string(10));

	//出力ウインドウへの文字出力
	OutputDebugStringA("HELLO,DirectX!\n");

	WNDCLASS wc{};

	// ウインドウプロシージャ
	wc.lpfnWndProc = WindowProc;

	// ウインドウクラス名(何でもいい)
	wc.lpszClassName = L"CGWindowClass";

	// インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);

	// カーソル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// ウインドウクラスを登録する
	RegisterClass(&wc);

	// クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	// ウインドウクラスを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	// クライアント領域を基に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウインドウの作成
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		L"CG2",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);

	// ウインドウを表示する
	ShowWindow(hwnd, SW_SHOW);

	MSG msg{};



	// wstring->string
	// ウインドウのｘボタンが押されるまでループ
	while (msg.message != WM_QUIT)
	{
		// Windoeに名が来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		} else
		{
			// ゲームの処理
		}
	}



	return 0;


}

