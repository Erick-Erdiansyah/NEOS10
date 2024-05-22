#include "cheat.h"
#include "proc.h"
#include "gameEntry.h"
#include <Windows.h>

void cheat::healthCheat(int key) {
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, Entry.getProcessId());
	currentHPAddess = FindDMAAddy(hProcess, Entry.dynamicAddress(), Entry.hpOffset(key));
	ReadProcessMemory(hProcess, (BYTE*)currentHPAddess, &currentHp, sizeof(currentHp), nullptr);
	newHp = currentHp;
	std::cout << "current hp value : " << std::dec << newHp << std::endl;
	while (true) {
		ReadProcessMemory(hProcess, (BYTE*)currentHPAddess, &currentHp, sizeof(currentHp), nullptr);
		if (currentHp > newHp) {
			std::cout << "current hp value : " << std::dec << newHp << std::endl;
			newHp = currentHp;
			std::cout << "new hp value : " << std::dec << newHp << std::endl;
		}
		if (currentHp < newHp) {
			WriteProcessMemory(hProcess, (BYTE*)currentHPAddess, &newHp, sizeof(newHp), nullptr);
		}
		if (GetAsyncKeyState(VK_ADD) & 1) {
			std::cout << "deactive\n";
			break;
		}
		Sleep(10);
	}
}

int cheat::consumableCheat(int item){
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, Entry.getProcessId());
	currentConsumableAddress = FindDMAAddy(hProcess, Entry.dynamicAddress(), Entry.consumableAddress(item));
	switch (item) {
	case 1:
		itemValue = 1083127808;
		WriteProcessMemory(hProcess, (BYTE*)currentConsumableAddress, &itemValue, sizeof(itemValue), nullptr);
		std::cout << "current coin value set to : " << std::dec << itemValue << std::endl;
		break;
	case 2:
		itemValue = 1079558144;
		WriteProcessMemory(hProcess, (BYTE*)currentConsumableAddress, &itemValue, sizeof(itemValue), nullptr);
		std::cout << "current bomb value set to: " << std::dec << itemValue << std::endl;
		break;
	case 3:
		itemValue = 1079558144;
		WriteProcessMemory(hProcess, (BYTE*)currentConsumableAddress, &itemValue, sizeof(itemValue), nullptr);
		std::cout << "current key value set to: " << std::dec << itemValue << std::endl;
		break;
	case 4:
		itemValue = 1075314688;
		WriteProcessMemory(hProcess, (BYTE*)currentConsumableAddress, &itemValue, sizeof(itemValue), nullptr);
		std::cout << "current gem value set to: " << std::dec << itemValue << std::endl;
		break;
	default:
		break;
	}
	return 0;
}

int cheat::runMe() {
	std::cout << "press + key to activate/deactivate godmode\n";
	std::cout << "press left arrow key to activate max coin\n";
	std::cout << "press right arrow key to activate max bomb\n";
	std::cout << "press up arrow key to activate max key\n";
	std::cout << "press down arrow key to activate max gem\n";
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, Entry.getProcessId());
	DWORD dwExit = 0;
	while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
		if (GetAsyncKeyState(VK_ADD) & 1) {
			cheat::healthCheat(0);
		}
		if (GetAsyncKeyState(VK_LEFT) & 1) {
			cheat::consumableCheat(1);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1) {
			cheat::consumableCheat(2);
		}
		if (GetAsyncKeyState(VK_UP) & 1) {
			cheat::consumableCheat(3);
		}
		if (GetAsyncKeyState(VK_DOWN) & 1) {
			cheat::consumableCheat(4);
		}
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			return 0;
		}
		Sleep(10);
	}
	getchar();
}