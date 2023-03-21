#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
#include <memory>
class CrabEnemy : public Enemy
{
public:
	CrabEnemy() {}
	CrabEnemy(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	std::shared_ptr<Move> determineMove(Character opponent) override;
private:
};