#include <Windows.h>
#include "validator.h"
using namespace std;
enum CWIND {
	REGISTER_WIND,
	LOGIN_WIND,
	TODO_WIND
};

extern "C" __declspec(dllexport)
HWND initself(HINSTANCE hinstance, LPCWSTR cname, WNDPROC Windproc);

extern "C" __declspec(dllexport)
CWIND getCurrentWind();

extern "C" __declspec(dllexport)
HWND switchTo(CWIND wind);