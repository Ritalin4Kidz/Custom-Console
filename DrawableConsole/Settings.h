#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
#include <windows.h>
using namespace std;
class Settings {
public:
	Settings() {}
	Settings(string settingsFile);
	virtual ~Settings() {}

	Vector2 getOffset() { return Vector2(xOffset, yOffset); }

	vector<string> ReturnCheats();

	int getConsoleHeight() { return ConsoleSizeHeight; }
	int getConsoleWidth() { return ConsoleSizeWidth; }

	void volumeControl(int volume);

private:
	int xOffset = 0;
	int yOffset = 0;
	int ConsoleSizeWidth = 40;
	int ConsoleSizeHeight = 20;
	string cheats;

	DWORD VOLUME_LOW = DWORD(858993459);
	DWORD VOLUME_NML = DWORD(1717986918);
	DWORD VOLUME_MED = DWORD(-1717986918);
	DWORD VOLUME_HIG = DWORD(-858993459);
	DWORD VOLUME_OFF = DWORD(0);
};