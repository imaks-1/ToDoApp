#include <Windows.h>
#include "WindowManager.hpp"
#include "accountSysCli.hpp"
#include <iostream>
using namespace std;

typedef CWIND(*getCurrentWind_t)();
typedef void(*switchTo_t)(CWIND);

HMODULE dll = LoadLibraryW(L"WindowManager.dll");

getCurrentWind_t getCurrentWindF =
(getCurrentWind_t)GetProcAddress(dll, "getCurrentWind");

switchTo_t switchToF =
(switchTo_t)GetProcAddress(dll, "switchTo");

static HWND usernameedit = nullptr;
static HWND passwordedit = nullptr;

int registerAcc(const LPWSTR& username, const LPWSTR& password) {
    Account acc(username, password);
    int res = acc.validate();

    if (res != ASR_SUCCES) {
        cout << res << endl;
        return 1;
    }
    cout << "[messageManager]Succesfully validated" << endl;
    cout << res << endl;
    return 0;
}

extern "C" __declspec(dllexport)

LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        cout << "[messageManager]Exiting!" << endl;
        PostQuitMessage(0);
        return 0;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
            // Exit
        case 6:
        {
            PostQuitMessage(0);
            return 0;
        }

        // Then Login / Then Register
        case 10:
        {
            if (getCurrentWindF)
            {
                if (getCurrentWindF() == CWIND::REGISTER_WIND)
                {
                    cout << "[messageManager]Switching to LOGIN_WIND" << endl;
                    switchToF(CWIND::LOGIN_WIND);
                }
                else
                {
                    cout << "[messageManager]Switching to REGISTER_WIND" << endl;
                    switchToF(CWIND::REGISTER_WIND);
                }
            }

            return 0;
        }

        // Show Password checkbox
        case 11:
        {
            HWND passwordEdit =
                GetDlgItem(hwnd, 4);

            if (passwordEdit)
            {
                BOOL checked =
                    (BOOL)SendMessageW(
                        (HWND)lParam,
                        BM_GETCHECK,
                        0,
                        0
                    );

                if (checked == BST_CHECKED)
                {
                    // показать пароль
                    SendMessageW(
                        passwordEdit,
                        EM_SETPASSWORDCHAR,
                        0,
                        0
                    );
                }
                else
                {
                    // скрыть пароль
                    SendMessageW(
                        passwordEdit,
                        EM_SETPASSWORDCHAR,
                        L'\x25CF',
                        0
                    );
                }

                InvalidateRect(
                    passwordEdit,
                    NULL,
                    TRUE
                );
            }

            return 0;
        }
        case 8: {
            wchar_t ubuffer[256];
            wchar_t pbuffer[256];
            usernameedit = GetDlgItem(hwnd, 4);
            passwordedit = GetDlgItem(hwnd, 2);
            GetWindowTextW(usernameedit, ubuffer, 256);
            GetWindowTextW(usernameedit, pbuffer, 256);
            if (getCurrentWindF() == CWIND::REGISTER_WIND) {
                cout << "[messageManager]Calling the registerAcc function!" << endl;
                registerAcc(ubuffer, pbuffer);
            }
        }
        }

        break;
    }

    //case WM_CTLCOLORSTATIC:
    //{
    //    HDC hdcStatic = (HDC)wParam;

    //    SetBkMode(
    //        hdcStatic,
    //        TRANSPARENT
    //    );

    //    return (INT_PTR)GetStockObject(NULL_BRUSH);
    //}

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

        FillRect(
            hdc,
            &rect,
            GetSysColorBrush(COLOR_WINDOW)
        );

        EndPaint(hwnd, &ps);
        return 0;
    }
    }

    return DefWindowProcW(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}