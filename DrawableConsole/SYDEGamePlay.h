#pragma once
#include "SYDEWindowGame.h"
#include "ConsoleWindow.h"
#include "SYDETime.h"
#include <windows.h>
#include <iostream>
class SYDEGamePlay {
public:
	static ConsoleWindow play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
private:
};