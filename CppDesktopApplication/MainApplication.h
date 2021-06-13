#define REGISTER_WINDOW 100
#define LOGIN_IN_WINDOW 101

#include "PopupWindow.h"

struct StateInfo {  };
BOOL WindowResize(HWND, WPARAM, LPARAM);
HWND hwndMainWindow, hwndRegister, hwndLogin; //hwndDialogWindow;

inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}