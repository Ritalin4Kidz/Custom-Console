#pragma once
#include "Character.h"
#include <vector>
#include <string>


class Player : public Character
{
public:
	Player() {}

	virtual void init_Char(int lvl) {}

	std::vector<std::string> getMovePool() { return m_MovePool; }
	void addXPToPlayer(int x) { xp += x; while (xp >= xpToNextLevel) { xp -= xpToNextLevel; xpToNextLevel *= 1.5; m_Level++; levelUpStats(); } }

	virtual void levelUpStats() {}

	string getXPStr() { return to_string(xp) + "xp/" + to_string(xpToNextLevel) + "xp"; }
protected:
	//THIS SHOULD NOT BE OVERRIDDEN, AS WE CAN MAKE CERTAIN MOVES TEACHABLE TO ALL CHARACTERS
	//WE SHOULD ONLY ADD TO THIS
	std::vector<std::string> m_MovePool = std::vector<std::string>(
		{

		});

	int xp = 0;
	int xpToNextLevel = 500;
};