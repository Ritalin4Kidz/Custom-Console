#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerFuri : public Player
{
public:
	PlayerFuri() {}
	PlayerFuri(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
	void levelUpStats() override;
private:

};