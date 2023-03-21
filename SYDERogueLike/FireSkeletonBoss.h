#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class FireSkeletonBoss : public Enemy
{
public:
	FireSkeletonBoss() {}
	FireSkeletonBoss(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};