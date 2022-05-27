#pragma once

#include "GameTypes.h"
#include <string>
#include "SYDEEngineAssets.h"
#include "json.hpp"
using json = nlohmann::json;
/*
TODO: DESIGN HOW MOVES WILL WORK PROPERLY
*/
class Move {
public:
	Move() {}
	virtual ~Move() { }
	_SQType getType() { return m_Type; }
	std::string getName() { return m_Name; }
	virtual void Execute(json* Attacker, json* Defender) {};

	float getPower() { return BasePower; }
	float BaseDamageCalculation(int level, float AttackStat, float DefenceStat, float Bonus_Damage);

	CustomAnimationAsset getAnimation() { return m_Animation; }

protected:
	_SQType m_Type;
	std::string m_Name;
	float BasePower;
	std::string m_Info = "";

	CustomAnimationAsset m_Animation;
};

class BattleFunctions {
public:
	static float DetermineMultiplier(Move* Attack, _SQType Defender);
	static AssetsClass astVars;
};