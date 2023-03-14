#pragma once
#include "Player.h"
#include "Move.h"
#include "MovesHeader.h"
class PlayerJordan : public Player
{
public:
	PlayerJordan() {}
	PlayerJordan(int lvl) { init_Char(lvl); }
	void init_Char(int lvl) override;

	void addMovePool();
private:

};