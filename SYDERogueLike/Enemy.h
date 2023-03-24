#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy() {}
	//~Enemy() = delete;
	
	virtual void init_Char(int lvl) {}

	virtual std::shared_ptr<Move> determineMove(Character opponent) { return nullptr; }

	void addStats(int lvl)
	{
		while (lvl > 0)
		{
			int HPBuff = rand() % 3 + 1;
			this->setHealth(getHealth() + HPBuff);
			this->setMaxHealth(getMaxHealth() + HPBuff);
			addRandomStats();
			lvl--;
		}
	}

	string getEnemyTag() { return m_EnemyTag; }
	int getXpGain() { return xpGainedFromFight; }

	bool getRequireBG() { return requireBG; }
	int getDrawPos() { return xDrawPos; }
protected:
	int xpGainedFromFight = 0;
	string m_EnemyTag = "Normal";
	int xDrawPos = 40;
	bool requireBG = false;
};