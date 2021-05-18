#pragma once
#include <Windows.h>

struct StateInfo {  };
BOOL WindowResize(HWND hwnd, WPARAM wParam, LPARAM lParam);
HWND hwndSignIn;
HWND hwndLogin;

inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}