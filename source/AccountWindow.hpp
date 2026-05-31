#include <Windows.h>
extern "C" __declspec(dllexport)
HWND init(const HINSTANCE& hInstance, LPCWSTR cName, WNDPROC WindProc);
extern "C" __declspec(dllexport)
void switchToLogin(const LPCWSTR& cName, HINSTANCE hInstance);
extern "C" __declspec(dllexport)
void switchToRegister(const LPCWSTR& cName, HINSTANCE hInstance);