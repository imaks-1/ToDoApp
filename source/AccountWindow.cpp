#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;
HWND newhwnd;
HWND shwnd1;
HWND ehwnd1;
HWND shwnd2;
HWND ehwnd2;
HWND shwnd3;
HWND bhwnd1;
HWND text;
HWND lrBtn;
HWND showPass;
HFONT font = CreateFontW(
	18,                 // height
	0,                  // width
	0,
	0,
	FW_BOLD,            // weight
	FALSE,
	FALSE,
	FALSE,
	DEFAULT_CHARSET,
	OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS,
	CLEARTYPE_QUALITY,
	VARIABLE_PITCH,
	L"Segoe UI"
);
HFONT hfont = CreateFontW(
	21,                 // height
	0,                  // width
	0,
	0,
	FW_BOLD,            // weight
	FALSE,
	FALSE,
	FALSE,
	DEFAULT_CHARSET,
	OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS,
	CLEARTYPE_QUALITY,
	VARIABLE_PITCH,
	L"Segoe UI"
);

extern "C" __declspec(dllexport)
HWND init(const HINSTANCE& hInstance,LPCWSTR cName, WNDPROC WindProc) {
	cout << "[AccountWindow] Creating WS..." << endl;
	WNDCLASSW ws = {};
	ws.lpfnWndProc = WindProc;
	ws.lpszClassName = cName;
	ws.hInstance = hInstance;
	cout << "[AccountWindow] Registring the WS..." << endl;
	RegisterClassW(&ws);
	DWORD style =
		WS_OVERLAPPEDWINDOW |
		WS_VISIBLE;
	style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	newhwnd = CreateWindowExW(0, cName, L"", style, 200, 300, 500, 500, NULL, NULL, hInstance, NULL);
	if (!newhwnd) {
		DWORD err = GetLastError();
		wchar_t buf[256];
		wsprintfW(buf, L"CreateWindowExW failed: %lu", err);
		MessageBoxW(NULL, buf, L"ERROR", MB_OK);
		return NULL;
	}
	cout << "[AccountWindow] Initializing UI..." << endl;
	shwnd1 = CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE | WS_CHILD, 125, 25, 300, 50, newhwnd, (HMENU)1, hInstance, NULL);
	ehwnd1 = CreateWindowExW(0, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 165, 115, 150, 20, newhwnd, (HMENU)2, hInstance, NULL);
	shwnd2 = CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE | WS_CHILD, 90, 115, 75, 50, newhwnd, (HMENU)3, hInstance, NULL);
	ehwnd2 = CreateWindowExW(0, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 165, 145, 150, 20, newhwnd, (HMENU)4, hInstance, NULL);
	shwnd3 = CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE | WS_CHILD, 90, 145, 75, 50, newhwnd, (HMENU)5, hInstance, NULL);
	bhwnd1 = CreateWindowExW(0, L"BUTTON", L"", WS_VISIBLE | WS_CHILD, 225, 175, 50, 25, newhwnd, (HMENU)8, hInstance, NULL);
	text = CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE | WS_CHILD, 175, 225, 250, 25, newhwnd, (HMENU)9, hInstance, NULL);
	lrBtn = CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE | WS_CHILD | SS_NOTIFY, 215, 265, 200, 30, newhwnd, (HMENU)10, hInstance, NULL);
	showPass = CreateWindowExW(0,
		L"BUTTON",
		L"Show password",
		WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		325, 145, 120, 20,
		newhwnd,
		(HMENU)11,
		hInstance,
		NULL);
	SendMessageW(shwnd1, WM_SETFONT, (WPARAM)hfont, TRUE);
	SendMessageW(shwnd2, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessageW(shwnd3, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessageW(bhwnd1, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessageW(text, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessageW(lrBtn, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessageW(ehwnd2, EM_SETPASSWORDCHAR, L'\x25CF', 0);
	cout << "[AccountWindow] UI initialized!" << endl;
	return newhwnd;
}

extern "C" __declspec(dllexport)
void switchToLogin(const LPCWSTR& cName, HINSTANCE hInstance) {
	SetWindowTextW(newhwnd, L"Login");
	SetWindowTextW(shwnd1, L"Welcome to 'ToDoApp', please login");
	SetWindowTextW(shwnd2, L"Username");
	SetWindowTextW(shwnd3, L"Password");
	SetWindowTextW(bhwnd1, L"Login");
	SetWindowTextW(text, L"Don't have an account?");
	SetWindowTextW(lrBtn, L"Then Register!");
	InvalidateRect(lrBtn, NULL, TRUE);
	UpdateWindow(lrBtn);
}
extern "C" __declspec(dllexport)
void switchToRegister(const LPCWSTR& cName, HINSTANCE hInstance) {
	SetWindowTextW(newhwnd, L"Register");
	SetWindowTextW(shwnd1, L"Welcome to 'ToDoApp', please register");
	SetWindowTextW(shwnd2, L"Username");
	SetWindowTextW(shwnd3, L"Password");
	SetWindowTextW(bhwnd1, L"Register");
	SetWindowTextW(text, L"Already have an account?");
	SetWindowTextW(lrBtn, L"Then login!");
	InvalidateRect(lrBtn, NULL, TRUE);
	UpdateWindow(lrBtn);
}