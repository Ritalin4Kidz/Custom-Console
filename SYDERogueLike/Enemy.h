#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy() {}
	virtual ~Enemy() {}
	
	virtual void init_Char(int lvl) {}

	virtual Move* determineMove(Character opponent) { return new Move(); }

private:
};