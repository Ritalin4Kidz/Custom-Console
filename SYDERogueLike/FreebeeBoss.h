#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class FreebeeBoss : public Enemy
{
public:
	FreebeeBoss() {}
	FreebeeBoss(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};