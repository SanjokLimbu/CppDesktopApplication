#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <tchar.h>
#include <WinUser.h>

typedef struct SizeAndPos_s {
	int x, y, width, height;
}SizeAndPost_t;

//void CreateDialog(HINSTANCE, LPCTSTR, HWND, DLGPROC);