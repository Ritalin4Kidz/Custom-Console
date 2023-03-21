#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
#include <memory>
class FishEnemy : public Enemy
{
public:
	FishEnemy() {}
	FishEnemy(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};