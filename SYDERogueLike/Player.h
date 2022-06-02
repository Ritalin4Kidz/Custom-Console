#pragma once
#include "Character.h"
#include <vector>
#include <string>


class Player : public Character
{
public:
	Player() {}
	virtual ~Player() {}

	virtual void init_Char(int lvl) {}


protected:
	//THIS SHOULD NOT BE OVERRIDDEN, AS WE CAN MAKE CERTAIN MOVES TEACHABLE TO ALL CHARACTERS
	//WE SHOULD ONLY ADD TO THIS
	std::vector<std::string> m_MovePool = std::vector<std::string>(
		{

		});
};