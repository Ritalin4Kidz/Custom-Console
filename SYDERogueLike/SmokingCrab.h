#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class SmokingCrab : public Enemy
{
public:
	SmokingCrab() {}
	SmokingCrab(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	Move* determineMove(Character opponent) override;
private:
};