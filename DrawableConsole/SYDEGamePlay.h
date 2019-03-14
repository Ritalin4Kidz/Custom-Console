#pragma once
#include "SYDEWindowGame.h"
#include "ConsoleWindow.h"
#include "SYDETime.h"
#include <windows.h>
#include <iostream>
#include <string>
#include "Artwork.h"
#include "Activation.h"
using namespace std;
class SYDEGamePlay {
public:
	static void opening_splashscreens(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	static ConsoleWindow play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
private:
	static void _introductionScript();
	static void _introCreditsScript(ConsoleWindow& window);
	static void _drawBee(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	static void _poweredBySYDEEngine(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);

	static bool _activated;

	static string _returnRandomNonsense();
};