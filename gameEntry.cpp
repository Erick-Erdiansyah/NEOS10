#include "gameEntry.h"
#include "proc.h"
#include <Windows.h>
#include <vector>
#include <iostream>

CString gameEntry::getProcessName() const {
	return processName;
}

CString gameEntry::getMainClass() const {
	return unityPlayerDll;
}

DWORD gameEntry::getProcessId() const {
	return GetProcId(getProcessName());
}

uintptr_t gameEntry::dynamicAddress() {
	moduleBase = GetModuleBaseAddress(gameEntry::getProcessId(), gameEntry::getMainClass());
	dAddress = moduleBase + RelativeOffset;
	return dAddress;
}

BOOL gameEntry::gameIsRunning() {
	return getProcessId() != 0;
}


std::vector<unsigned int> gameEntry::basicOffset() const {
	return basicInfoOffsets;
}

std::vector<unsigned int> gameEntry::hpOffset() {
	const auto& offsets = gameEntry::basicOffset();
	std::vector<unsigned int> hp = { 0x25C };
	hp.insert(hp.begin(), offsets.begin(), offsets.end());
	return hp;
}

std::vector<unsigned int> gameEntry::consumableAddress(int keypressed) {
	const auto& offsets = gameEntry::basicOffset();
	std::vector<unsigned int> Offset;
	switch (keypressed) {
	case 0:
		Offset.push_back(OffsetLists.at(0));
		break;
	case 1:
		Offset.push_back(OffsetLists.at(1));
		break;
	case 2:
		Offset.push_back(OffsetLists.at(2));
		break;
	case 3:
		Offset.push_back(OffsetLists.at(3));
		break;
	default:
		break;
	}
	Offset.insert(Offset.begin(), offsets.begin(), offsets.end());
	return Offset;
}
