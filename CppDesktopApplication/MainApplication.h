#define SIGN_IN_WINDOW 100
#define LOGIN_IN_WINDOW 101
#define SIGN_IN_BOX 102
#include <Windows.h>

struct StateInfo {  };
BOOL WindowResize(HWND hwnd, WPARAM wParam, LPARAM lParam);
HWND hwndSignIn;
HWND hwndLogin;
HWND signInBox;

inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}