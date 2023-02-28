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

protected:
	string m_EnemyTag = "Normal";
};