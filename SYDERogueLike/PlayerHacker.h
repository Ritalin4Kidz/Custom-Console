#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerHacker : public Player
{
public:
	PlayerHacker() {}
	PlayerHacker(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	void levelUpStats() override;

	void addMovePool();
private:

};