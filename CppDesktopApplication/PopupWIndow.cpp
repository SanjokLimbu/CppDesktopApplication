#include "PopupWindow.h"

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CONST wchar_t DIALOG_WINDOW_NAME[] = L"DialogClass";

HWND hwndDialogWindow;

//Create instance of main window to use as dialog window
void RegisterDialog(HINSTANCE hInstance)
{
	WNDCLASS dialogBox = {};

	dialogBox.lpfnWndProc = DialogProc;
	dialogBox.lpszClassName = DIALOG_WINDOW_NAME;
	dialogBox.hInstance = hInstance;
	dialogBox.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (RegisterClass(&dialogBox) == 0) {
		int nresult = GetLastError();
		MessageBox(NULL, L"Dialog window registration failed", L"Error", 0);
	}
}

void DisplayRegisterDialog(HWND hwnd) 
{
	hwndDialogWindow = CreateWindow(DIALOG_WINDOW_NAME, L"Register User", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, hwnd, NULL, NULL, NULL);
	if (hwndDialogWindow == NULL) {
		int rresult = GetLastError();
		MessageBox(NULL, L"Dialog window creation failed", L"Error", 0);
	}
	DisableMinimizeButton(hwndDialogWindow);
	DisableMaximizeButton(hwndDialogWindow);
}

//Disable and hide minimize and mazimize button of window caption
void DisableMinimizeButton(HWND hwnd)
{
	SetWindowLong(hwnd, GWL_STYLE,
		GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
}

void DisableMaximizeButton(HWND hwnd)
{
	SetWindowLong(hwnd, GWL_STYLE,
		GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
			if (hwndDialogWindow) {
				SendMessage(hwndDialogWindow, WM_CLOSE, 0, NULL);
				//EnableWindow(hwnd, true);
			}
			break;
		case WM_CREATE:
			HWND hwndUserNameText = CreateWindow(L"static", L"Username", WS_CHILD | WS_VISIBLE, 50, 25, 100, 25, hwnd, NULL, NULL, NULL);
			HWND hwndUserNameEntry = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 157, 25, 200, 25, hwnd, (HMENU)USERNAME_WINDOW, NULL, NULL);
			HWND hwndPasswordText = CreateWindow(L"static", L"Password", WS_CHILD | WS_VISIBLE, 50, 52, 100, 25, hwnd, NULL, NULL, NULL);
			HWND hwndPasswordEntry = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 157, 52, 200, 25, hwnd, (HMENU)PASSWORD_WINDOW, NULL, NULL);
			HWND hwndSubmit = CreateWindow(L"Button", L"Submit", WS_VISIBLE | WS_CHILD, 157, 80, 100, 50, hwnd, (HMENU)SUBMIT_BUTTON, NULL, NULL);
			if (hwndSubmit == NULL) {
				int result = GetLastError();
				MessageBox(NULL, L"Failed to Password", L"ERROR", 0);
			}
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
