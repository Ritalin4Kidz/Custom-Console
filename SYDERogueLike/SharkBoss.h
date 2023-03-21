#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class SharkBoss : public Enemy
{
public:
	SharkBoss() {}
	SharkBoss(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};