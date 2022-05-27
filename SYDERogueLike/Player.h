#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player() {}
	virtual ~Player() {}

	virtual void init_Char(int lvl) {}

protected:
};