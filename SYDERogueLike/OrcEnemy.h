#pragma once
#include "Enemy.h"
#include "MovesHeader.h"
class OrcEnemy : public Enemy
{
public:
	OrcEnemy() {}
	OrcEnemy(int lvl) { init_Char(lvl); }
	virtual ~OrcEnemy() {}
	void init_Char(int lvl) override;
	Move* determineMove(Character opponent) override;
private:
};