#pragma once
#include <string>

#define ASR_SUCCES 0
#define ASR_INVALIDUSERNAME 1
#define ASR_SHORTPASSWORD 2
#define ASR_INVALIDPASSWORD 3
#define ASR_LONGUSERNAME 6
#define ASR_FAILURE 7

class Account {
private:
    std::wstring username;
    std::wstring password;
    std::wstring password_hashed;
    std::wstring validateToken;

public:
    Account(
        const std::wstring& username,
        const std::wstring& password
    );

    int validate();
};