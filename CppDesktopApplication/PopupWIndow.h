#define DIALOG_REGISTER_WINDOW 102
#define USERNAME_WINDOW 103
#define PASSWORD_WINDOW 104
#define SUBMIT_BUTTON 105

#include <Windows.h>

//extern HWND hwndDialogWindow;

void RegisterDialog(HINSTANCE);
void DisplayRegisterDialog(HWND);
void DisableMinimizeButton(HWND);
void DisableMaximizeButton(HWND);