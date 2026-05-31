#include <Windows.h>
#include "window.hpp"
#include <cstdio>
#include <iostream>
using namespace std;

const static bool DEBUG_MODE = false;

using createMainWindow_t = HWND(*)(HINSTANCE, int, LPCWSTR, LPCWSTR);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    if (DEBUG_MODE) {
        AllocConsole();

        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        cout << "[ToDoApp/DEBUG] Debug mode ON" << endl;
    }
    HMODULE dll = LoadLibraryW(L"window.dll");
    if (!dll) {
        MessageBoxW(NULL, L"window.dll not found", L"Fatal Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    auto createMainWindowF = reinterpret_cast<createMainWindow_t>(
        GetProcAddress(dll, "createMainWindow")
        );

    if (!createMainWindowF) {
        MessageBoxW(NULL, L"createMainWindow not found", L"Fatal Error", MB_ICONERROR | MB_OK);
        return 0;
    }
    cout << "[ToDoApp] Starting the app!" << endl;
    createMainWindowF(hInstance, nCmdShow, L"idk", L"IDK");
    return 0;
}