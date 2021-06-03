#pragma once
#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"
#include "SRLGame.h"
#include <iostream>
#include <fstream>
#include <iterator>
enum GameStateSYDE
{
	MainLevel_STATE,
	MainMenu_STATE,
	LevelSelect_STATE,
	Win_STATE
};

class SRLGame : public SYDEWindowGame {
public:
	SRLGame() { init(); }
	virtual ~SRLGame() {}
	void init();

	vector<SRLPlayer> createRandomTeam(string prefix);

	void test();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;

private:
};