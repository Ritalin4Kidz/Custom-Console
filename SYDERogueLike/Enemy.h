#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy() {}
	//~Enemy() = delete;
	
	virtual void init_Char(int lvl) {}

	virtual std::shared_ptr<Move> determineMove(Character opponent) { return nullptr; }

	string getEnemyTag() { return m_EnemyTag; }
	int getXpGain() { return xpGainedFromFight; }
protected:
	int xpGainedFromFight = 0;
	string m_EnemyTag = "Normal";
};