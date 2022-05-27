#pragma once
#include "Player.h"
#include "Move.h"
#include "SmokeBreakMove.h"
class PlayerFuri : public Player
{
public:
	PlayerFuri() {}
	PlayerFuri(int lvl) { init_Char(lvl); }
	virtual ~PlayerFuri() {}
	void init_Char(int lvl) override;
private:

};