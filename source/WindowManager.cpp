#include <Windows.h>
#include "validator.h"
using namespace std;
typedef HWND(*init)(HINSTANCE hInstance, LPCWSTR cName, WNDPROC WindProc);
typedef void(*switchToLogin)(const LPCWSTR& cName, HINSTANCE hInstance);
typedef void(*switchToRegister)(const LPCWSTR& cName, HINSTANCE hInstance);
enum CWIND {
	REGISTER_WIND,
	LOGIN_WIND,
	TODO_WIND
};
HINSTANCE hInstance;
LPCWSTR cName;
WNDPROC WindProc;
CWIND curent = CWIND::REGISTER_WIND;
HMODULE dll = LoadLibraryW(L"AccountWindow.dll");

init initF =
(init)GetProcAddress(dll, "init");

switchToLogin switchToLoginF =
(switchToLogin)GetProcAddress(dll, "switchToLogin");

switchToRegister switchToRegisterF =
(switchToRegister)GetProcAddress(dll, "switchToRegister");
bool validateReq();

extern "C" __declspec(dllexport)
HWND initself(HINSTANCE hinstance, LPCWSTR cname, WNDPROC Windproc) {
	if (!validateReq()) {
		return NULL;
	}
	hInstance = hinstance;
	cName = cname;
	WindProc = Windproc;
	HWND hwnd = initF(hInstance, cName, WindProc);
	return hwnd;
}

extern "C" __declspec(dllexport)
CWIND getCurrentWind() {
	return curent;
}

extern "C" __declspec(dllexport)
void switchTo(CWIND wind) {
	switch (wind) {
		case CWIND::REGISTER_WIND: {
			switchToRegisterF(cName, hInstance);
			curent = CWIND::REGISTER_WIND;
			break;
		}
		case CWIND::LOGIN_WIND: {
			switchToLoginF(cName, hInstance);
			curent = CWIND::LOGIN_WIND;
			break;
		}
	}
}

bool validateReq() {
	if (!switchToRegisterF) {
		MessageBoxW(NULL, L"switchToRegister not found", L"Fatal Error", MB_ICONERROR | MB_OK);
		return false;
	}
	if (!switchToLoginF) {
		MessageBoxW(NULL, L"switchToLogin not found", L"Fatal Error", MB_ICONERROR | MB_OK);
		return false;
	}
	if (!initF) {
		MessageBoxW(NULL, L"init not found", L"Fatal Error", MB_ICONERROR | MB_OK);
		return false;
	}
	if (!dll) {
		MessageBoxW(NULL, L"AccountWindow.dll not found", L"Fatal Error", MB_ICONERROR | MB_OK);
		return false;
	}
	return true;
}