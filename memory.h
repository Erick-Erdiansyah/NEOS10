#pragma once
#include<vector>
#include<Windows.h>
#include<TlHelp32.h>

namespace mem {
	void patchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void Nope(BYTE* dst, unsigned int size, HANDLE hProcess);
}
