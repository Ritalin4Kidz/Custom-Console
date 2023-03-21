#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class AliBoss : public Enemy
{
public:
	AliBoss() {}
	AliBoss(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};