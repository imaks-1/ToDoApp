#pragma once
#include <Windows.h>

extern "C" __declspec(dllexport)
HWND createMainWindow(
    HINSTANCE hInstance,
    int nCmdShow,
    LPCWSTR wName,
    LPCWSTR cName
);
HINSTANCE getHinstance();
LPCWSTR getCName();