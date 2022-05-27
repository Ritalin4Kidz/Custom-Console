#pragma once

#include "GameTypes.h"
#include <string>
#include "SYDEEngineAssets.h"
#include "Character.h"
/*
TODO: DESIGN HOW MOVES WILL WORK PROPERLY
*/

class Move {
public:
	Move() {}
	virtual ~Move() { }
	_SQType getType() { return m_Type; }
	std::string getName() { return m_Name; }
	virtual void Execute(Character* Attacker, Character* Defender) {};

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
	static float DetermineMultiplier(Move* Attack, Character* Defender);
	static AssetsClass astVars;
};