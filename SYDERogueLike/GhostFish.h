#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class GhostFish : public Enemy
{
public:
	GhostFish() {}
	GhostFish(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};