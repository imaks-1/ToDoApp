#include <Windows.h>
#include "window.hpp"
#include "validator.h"
#include "WindowManager.hpp"
#include <iostream>
HINSTANCE g_hinstance;
LPCWSTR g_cName;
typedef void(*newMenu)(HWND hwnd);
typedef HWND(*initself_t)(HINSTANCE hinstance, LPCWSTR cname, WNDPROC Windproc);
typedef void(*switchTo_t)(CWIND wind);
bool validateReq();

extern "C" __declspec(dllexport)
HWND createMainWindow(
    HINSTANCE hInstance,
    int nCmdShow,
    LPCWSTR wName,
    LPCWSTR cName
) {
    g_hinstance = hInstance;
    g_cName = cName;
    cout << "[window] Setting g_ variables..." << endl;
    cout << "[window] Validating requested DLL's..." << endl;
    if (!validateReq()) {
        return NULL;
    }
    HMODULE dll = LoadLibraryW(L"messageManager.dll");
    HMODULE dll_2 = LoadLibraryW(L"WindowManager.dll");
    HMODULE dll_3 = LoadLibraryW(L"menu.dll");
    initself_t initselfF = (initself_t)GetProcAddress(dll_2, "initself");
    switchTo_t switchToF = (switchTo_t)GetProcAddress(dll_2, "switchTo");
    WNDPROC WindProc = (WNDPROC)GetProcAddress(dll, "WndProc");
    newMenu newMenuF = (newMenu)GetProcAddress(dll_3, "newMenu");
    if (!WindProc) {
        MessageBoxW(NULL, L"WndProc not found", L"ERROR", MB_OK);
        return NULL;
    }
    HWND mainhwnd = initselfF(hInstance, cName, WindProc);

    SetWindowLongPtrW(mainhwnd, GWLP_USERDATA, (LONG_PTR)hInstance);
    SetPropW(mainhwnd, L"cName", (HANDLE)cName);
    if (mainhwnd == NULL) {
        MessageBoxW(NULL, L"CreateWindowExW FAILED", L"ERROR", MB_OK);
        return NULL;
    }
    if (!initselfF) {
        MessageBoxW(NULL, L"initself not found", L"ERROR", MB_OK);
        return NULL;
    }
    if (!switchToF) {
        MessageBoxW(NULL, L"switchTo not found", L"ERROR", MB_OK);
        return NULL;
    }
    switchToF(CWIND::REGISTER_WIND);
    newMenuF(mainhwnd);
    ShowWindow(mainhwnd, nCmdShow);
    UpdateWindow(mainhwnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        DispatchMessageW(&msg);
        TranslateMessage(&msg);
    }
    FreeLibrary(dll);
    return mainhwnd;
}

bool validateReq() {
    if (!validateDLL(L"messageManager.dll")) {
        MessageBoxW(NULL, L"messageManager.dll not found", L"Fatal Error", MB_ICONERROR | MB_OK);
        return false;
    }
    if (!validateDLL(L"menu.dll")) {
        MessageBoxW(NULL, L"menu.dll not found", L"Fatal Error", MB_ICONERROR | MB_OK);
        return false;
    }
    if (!validateDLL(L"WindowManager.dll")) {
        MessageBoxW(NULL, L"WindowManager.dll not found", L"Fatal Error", MB_ICONERROR | MB_OK);
        return false;
    }
    return true;
}