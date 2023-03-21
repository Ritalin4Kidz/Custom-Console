#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerAlison : public Player
{
public:
	PlayerAlison() {}
	PlayerAlison(int lvl) { init_Char(lvl); }

	void addMovePool();
	void init_Char(int lvl) override;
	void levelUpStats() override;
private:

};