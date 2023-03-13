#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerFuego : public Player
{
public:
	PlayerFuego() {}
	PlayerFuego(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;
private:

};