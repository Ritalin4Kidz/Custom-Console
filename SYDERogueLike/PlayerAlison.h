#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerAlison : public Player
{
public:
	PlayerAlison() {}
	PlayerAlison(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
private:

};