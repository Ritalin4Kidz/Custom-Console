#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy() {}
	//~Enemy() = delete;
	
	virtual void init_Char(int lvl) {}

	virtual Move* determineMove(Character opponent) { return new Move(); }

	string getEnemyTag() { return m_EnemyTag; }

protected:
	string m_EnemyTag = "Normal";
};