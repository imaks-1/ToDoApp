#include "accountSysCli.hpp"
#include <cwchar>
#include <iostream>
using namespace std;

#define ASR_PASSWORDSUCCES 4
#define ASR_USERNAMESUCCES 5

const wchar_t USERNAME_CHARS[] =
L"abcdefghijklmnopqrstuvwxyz"
L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
L"0123456789"
L"_.-";

const wchar_t PASSWORD_CHARS[] =
L"abcdefghijklmnopqrstuvwxyz"
L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
L"0123456789"
L"_.-!@#$%^&*()";

bool isAllowedUsername(wchar_t c)
{
    wcout << "[accountSysCli/USERNAME] validating char: " << c << endl;
    bool res = wcschr(USERNAME_CHARS, c) != nullptr;
    wcout << "[accountSysCli/USERNAME] validating char: " << c << ", result: " << res << endl;
    return res;
}

bool isAllowedPassword(wchar_t c)
{
    wcout << "[accountSysCli/PASSWORD] validating char: " << c << endl;
    bool res = wcschr(PASSWORD_CHARS, c) != nullptr;
    wcout << "[accountSysCli/PASSWORD] validating char: " << c << ", result: " << res << endl;
    return res;
}

constexpr int REQ_SIZE = 8;
constexpr int MAX_SIZE = 16;

int validatePassword(const std::wstring& password)
{
    wcout << "[accountSysCli] validating password: " << password << endl;
    if (password.size() < REQ_SIZE)
        return ASR_SHORTPASSWORD;

    for (wchar_t c : password)
    {
        if (!isAllowedPassword(c))
            return ASR_INVALIDPASSWORD;
    }

    return ASR_PASSWORDSUCCES;
}

int validateUsername(const std::wstring& username)
{
    wcout << "[accountSysCli] validating username: " << username << endl;
    if (username.empty())
        return ASR_INVALIDUSERNAME;

    if (username.size() > MAX_SIZE)
        return ASR_LONGUSERNAME;

    for (wchar_t c : username)
    {
        if (!isAllowedUsername(c))
            return ASR_INVALIDUSERNAME;
    }

    return ASR_USERNAMESUCCES;
}

Account::Account(
    const std::wstring& username,
    const std::wstring& password
)
{
    this->username = username;
    this->password = password;
}

int Account::validate()
{
    wcout << "[accountSysCli] validating username: " << username << ", and password: " << password << endl;
    int result = validateUsername(username);

    if (result != ASR_USERNAMESUCCES)
        return result;

    result = validatePassword(password);

    if (result != ASR_PASSWORDSUCCES)
        return result;

    return ASR_SUCCES;
}