#pragma once
#include <Windows.h>

bool validateDLL(LPCWSTR dllName) {
	HMODULE dll = LoadLibraryW(dllName);

	if (!dll) {
		return false;
	}
	FreeLibrary(dll);
	return true;
}