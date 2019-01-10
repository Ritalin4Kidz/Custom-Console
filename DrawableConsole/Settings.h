#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
using namespace std;
class Settings {
public:
	Settings() {}
	Settings(string settingsFile);
	virtual ~Settings() {}

	Vector2 getOffset() { return Vector2(xOffset, yOffset); }
private:
	int xOffset = 0;
	int yOffset = 0;
};