#include "PopupWindow.h"
#include <Windows.h>

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void registerDialog(HINSTANCE hInstance) 
{
	WNDCLASS dialogBox = {0};

	dialogBox.lpfnWndProc = DialogProc;
	dialogBox.lpszClassName = L"dialogClass";
	dialogBox.hInstance = hInstance;
	dialogBox.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&dialogBox);
}

void displayRegisterDialog(HWND hwnd) 
{
	CreateWindow(TEXT("dialogClass"), TEXT("Register"), WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, hwnd, NULL, NULL, NULL);
}

LRESULT DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return 0;
			break;
	}
}
