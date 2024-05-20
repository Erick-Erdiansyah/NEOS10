#include <Windows.h>
#include <vector>
#include <iostream>
#include "gameEntry.h"

class cheat
{
public:
	gameEntry Entry;
	void healthCheat();
	int runMe();
	int consumableCheat(int item);

private:
	uintptr_t currentHPAddess, currentConsumableAddress;
	int32_t currentHp, newHp, itemValue;
	HANDLE hProcess = 0;
	DWORD dwExit = 0;
};