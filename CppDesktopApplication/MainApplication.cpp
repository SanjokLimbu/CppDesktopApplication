#include "MainApplication.h"
#include <new>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	//Register Window class
	CONST wchar_t CLASS_NAME[] = L"CppDesktopApplication";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wc);

	//Pass instance of main window to dialog window instance
	RegisterDialog(hInstance);

	//Manage application state
	StateInfo* pstate = new (std::nothrow) StateInfo;

	if (pstate == NULL) {
		return 0;
	}

	//Create main Window
	hwndMainWindow = CreateWindowEx(
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

	if (hwndMainWindow == NULL) {
		return 0;
	}

	ShowWindow(hwndMainWindow, nCmdShow);
	UpdateWindow(hwndMainWindow);

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
	
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_SIZE:
			WindowResize(hwnd, wParam, lParam);
			break;

		case WM_CREATE: 
			hwndRegister = CreateWindow(TEXT("BUTTON"), TEXT("Register"), WS_VISIBLE | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, 100, 50, hwnd, (HMENU)REGISTER_WINDOW, NULL, NULL);
			hwndLogin = CreateWindow(TEXT("BUTTON"), TEXT("Login"), WS_VISIBLE | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, 100, 50, hwnd, (HMENU)LOGIN_IN_WINDOW, NULL, NULL);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case REGISTER_WINDOW:
					DisplayRegisterDialog(hwnd);
					EnableWindow(hwnd, false);
					break;
			}
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

BOOL WindowResize(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int width = LOWORD(lParam);
	int height = HIWORD(lParam);

	RECT windowRect;
	//Initialize child window button
	RECT childRect{};
	childRect.left = 0;
	childRect.top = 0;
	childRect.right = 100;
	childRect.bottom = 50;

	GetWindowRect(hwnd, &windowRect);
	//Calculate center co ordinate of window and set button

	int parentWidth = windowRect.right - windowRect.left;
	int parentHeight = windowRect.bottom - windowRect.top;

	int childWidth = childRect.right - childRect.left;
	int childHeight = childRect.bottom - childRect.top;

	int button_x = (parentWidth / 2) - (childWidth / 2);
	int button_y = (parentHeight / 2) - (childHeight / 2);

	SetWindowPos(hwndRegister, NULL, button_x - 50, button_y, 100, 50, SWP_NOZORDER);
	SetWindowPos(hwndLogin, NULL, button_x + 50, button_y, 100, 50, SWP_NOZORDER);
	return true;
}