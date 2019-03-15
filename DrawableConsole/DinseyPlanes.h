#pragma once
#include "SYDEWindowGame.h"
class DinseyPlanes : public SYDEWindowGame {
public:
	DinseyPlanes() {}
	virtual ~DinseyPlanes() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
};