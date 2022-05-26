#pragma once

#include "GameTypes.h"
#include <string>

/*
TODO: DESIGN HOW MOVES WILL WORK PROPERLY
*/

class Move {
public:
	Move() {}
	virtual ~Move() { }
	GameType getType() { return m_Type; }
	std::string getName() { return m_Name; }


	float getPower() { return BasePower; }
	float BaseDamageCalculation(int level, float AttackStat, float DefenceStat, float Bonus_Damage);

	std::string toStatsJsonString();
protected:
	GameType m_Type;
	std::string m_Name;
	float BasePower;
	std::string m_Info = "";
};