#include "PopupWindow.h"
#include "SQLConnection.h"

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CONST wchar_t DIALOG_WINDOW_NAME[] = L"DialogClass";

HWND hwndMainWindowInstance, hwndUserNameEntry, hwndPasswordEntry, hwndSubmit;

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
	hwndMainWindowInstance = hwnd;
	HWND hwndDialogWindow = CreateWindowW(DIALOG_WINDOW_NAME, L"Register User", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, hwnd, NULL, NULL, NULL);
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
			DestroyWindow(hwnd);
			EnableWindow(hwndMainWindowInstance, true);
			break;
		case WM_CREATE:
			CreateWindowW(L"static", L"Username", WS_CHILD | WS_VISIBLE, 50, 25, 100, 25, hwnd, NULL, NULL, NULL);
			hwndUserNameEntry = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 157, 25, 200, 25, hwnd, (HMENU)USERNAME_WINDOW, NULL, NULL);
			CreateWindowW(L"static", L"Password", WS_CHILD | WS_VISIBLE, 50, 52, 100, 25, hwnd, NULL, NULL, NULL);
			hwndPasswordEntry = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 157, 52, 200, 25, hwnd, (HMENU)PASSWORD_WINDOW, NULL, NULL);
			hwndSubmit = CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD, 157, 80, 100, 50, hwnd, (HMENU)SUBMIT_BUTTON, NULL, NULL);
			if (hwndSubmit == NULL) {
				int result = GetLastError();
				MessageBox(NULL, L"Failed to submit", L"ERROR", 0);
			}
			break;

		case WM_COMMAND:
			SQLWCHAR Username[30], Password[30];
			switch (LOWORD(wParam))
			{
				case SUBMIT_BUTTON:
					SQLWCHAR UsernameEntry = GetWindowText(hwndUserNameEntry, Username, 30);
					SQLWCHAR PasswordEntry = GetWindowText(hwndPasswordEntry, Password, 30);
					SQLMain(UsernameEntry, PasswordEntry);
					break;
			}
			break;
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
