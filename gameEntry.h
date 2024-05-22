#include <Windows.h>
#include <vector>
#include <atlstr.h>
#pragma once
class gameEntry{
private:
	uintptr_t moduleBase = 0;
	uintptr_t dAddress = 0;
	const CString processName = L"NeonAbyss.exe";
	CString unityPlayerDll = L"UnityPlayer.dll";
	uintptr_t RelativeOffset = 0x01566CE8;
	std::vector<unsigned int> basicInfoOffsets = { 0x8, 0x80, 0x28, 0x238, 0x20, 0x78 };
	std::vector<unsigned int> OffsetLists = { 0x25C, 0x214, 0x2A4, 0x514, 0x274 };

public:
	CString getProcessName() const;
	CString getMainClass() const;
	DWORD getProcessId() const;
	uintptr_t dynamicAddress();
	BOOL gameIsRunning();
	std::vector<unsigned int> basicOffset() const;
	std::vector<unsigned int> hpOffset(int keypress);
	std::vector<unsigned int> consumableAddress(int keyPressed);
};

