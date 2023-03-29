#pragma once
#include "Character.h"
#include <vector>
#include <string>
#include "MovePoolItem.h"
#include "MovesHeader.h"
class Player : public Character
{
public:
	Player() {}

	virtual void init_Char(int lvl) {}

	std::vector<MovePoolItem> getMovePool() { return m_MovePool; }
	void addXPToPlayer(int x) { xp += x; while (xp >= xpToNextLevel) { xp -= xpToNextLevel; xpToNextLevel *= 1.5; m_Level++; addRandomStats(); levelUpStats(); } }

	int getMinRoll() { return minimumRoll; }
	int getRollSize() { return rollSize; }

	void saveStats()
	{
		savedAttackStat			= m_Attack;
		savedDefenceStat		= m_Defence;
		savedMagicAttackStat	= m_MagicAttack;
		savedMagicDefenceStat	= m_MagicDefence;
		savedSpeedStat			= m_Speed;
		savedAbility			= m_Ability;
		savedType				= m_Type;
	}
	void reviveStats()
	{
		m_Attack				= savedAttackStat;
		m_Defence				= savedDefenceStat;
		m_MagicAttack			= savedMagicAttackStat;
		m_MagicDefence			= savedMagicDefenceStat;
		m_Speed					= savedSpeedStat;
		m_Ability				= savedAbility;
		m_Type					= savedType;
		m_turnsSleeping = 0;
	}
	string getXPStr() { return to_string(xp) + "xp/" + to_string(xpToNextLevel) + "xp"; }
protected:
	//THIS SHOULD NOT BE OVERRIDDEN, AS WE CAN MAKE CERTAIN MOVES TEACHABLE TO ALL CHARACTERS
	//WE SHOULD ONLY ADD TO THIS
	std::vector<MovePoolItem> m_MovePool = std::vector<MovePoolItem>(
		{
			MovePoolItem(std::shared_ptr<Move>(new SlashMove()), 30),
			MovePoolItem(std::shared_ptr<Move>(new BulkUpMove()), 35),
			MovePoolItem(std::shared_ptr<Move>(new SnowballMove()), 40),
			MovePoolItem(std::shared_ptr<Move>(new TypeBeamMove()), 50)
		}); 
	int savedAttackStat;
	int savedDefenceStat;
	int savedMagicAttackStat;
	int savedMagicDefenceStat;
	int savedSpeedStat;
	AbilityStruct savedAbility;
	_SQType savedType;
	int xp = 0;
	int xpToNextLevel = 500;

	int minimumRoll = 1;
	int rollSize = 6;
};