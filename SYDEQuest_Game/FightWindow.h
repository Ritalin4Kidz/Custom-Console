#pragma once
#include <string.h>
#include <vector>
class FightWindow {
public:
	FightWindow() {}
	virtual ~FightWindow() { clear(); }

	void AddFString(std::string fstring);
	std::string getFString(int index) { if (index >= _fightStrings.size()) { return ""; } return _fightStrings[index]; }

	void clear() { _fightStrings.clear(); }
private:
	std::vector<std::string> _fightStrings = std::vector<std::string>();
};