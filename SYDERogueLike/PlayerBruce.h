#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerBruce : public Player
{
public:
	PlayerBruce() {}
	PlayerBruce(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;

	void addMovePool();
	void levelUpStats() override;
private:

};