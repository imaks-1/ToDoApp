#include <Windows.h>
using namespace std;

extern "C" __declspec(dllexport)
void newMenu(HWND hwnd) {
	HMENU menu = CreateMenu();
	HMENU filemenu = CreatePopupMenu();
	HMENU helpmenu = CreatePopupMenu();
	AppendMenuW(helpmenu, MF_STRING, 7, L"About");
	AppendMenuW(filemenu, MF_STRING, 6, L"Exit");

	AppendMenuW(menu, MF_POPUP, (UINT_PTR)filemenu, L"File");
	AppendMenuW(menu, MF_POPUP, (UINT_PTR)helpmenu, L"Help");
	SetMenu(hwnd, menu);
}