#pragma once
#include <Windows.h>

extern "C" __declspec(dllexport)
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);