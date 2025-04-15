#include <Windows.h>

// windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	//出力ウインドウへの文字出力
	OutputDebugStringA("HELLO,DirectX!\n");

	return 0;
}