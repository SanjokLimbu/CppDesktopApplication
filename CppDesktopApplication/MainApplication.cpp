#include "MainApplication.h"
#include <windows.h>
#include <new>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	//Register Window class
	CONST wchar_t CLASS_NAME[] = L"CppDesktopApplication";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;

	RegisterClass(&wc);
	//Manage application state
	StateInfo* pstate = new (std::nothrow) StateInfo;

	if (pstate == NULL) {
		return 0;
	}

	//Create Window
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"DesktopApplication",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		pstate
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	//Run message loop
	MSG msg = {};
	while ((GetMessage(&msg, NULL, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	StateInfo* pState;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		pState = GetAppState(hwnd);
	}

	RECT windowRect;
	if (!GetWindowRect(GetDesktopWindow(), &windowRect))
		return FALSE;

	int posX = windowRect.right - 100;
	int posY = windowRect.bottom - 100;

	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;

		case WM_CREATE: 
			CreateWindow(TEXT("BUTTON"), TEXT("Sign In"), WS_VISIBLE | WS_CHILD, posX, posY, 100, 50, hwnd, (HMENU)1, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("Login"), WS_VISIBLE | WS_CHILD, 350, 200, 100, 50, hwnd, (HMENU)2, NULL, NULL);
			break;

		case WM_PAINT: 
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			break;
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}