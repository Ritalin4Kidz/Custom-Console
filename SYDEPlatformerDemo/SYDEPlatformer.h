#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"

enum GameStateSYDE
{
	MainLevel_STATE,
	MainMenu_STATE,
	LevelSelect_STATE,
	Win_STATE
};

class SYDEPlatformer : public SYDEWindowGame {
public:
	SYDEPlatformer() { init(); }
	virtual ~SYDEPlatformer() {}
	void init();
	ConsoleWindow draw_game(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow draw_title(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow draw_levelSelect(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow draw_WinState(ConsoleWindow window, int windowWidth, int windowHeight);


	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;


	void AddPositionX(Vector2 add);
	void winMap();
	void ApplyMomentum();

private:
	Vector2 PlayerPos = Vector2(2, 3);

	Vector2 CheckPoint = Vector2(2, 3);
	GameStateSYDE m_State = MainMenu_STATE;
	bool checkGrounded();
	bool checkGrounded(ConsoleWindow window);
	float movementTime = 0;
	float momentumTime = 0;

	double gameTime = 0.0f;

	Vector2 m_Momentum = Vector2(0, 0);
	CustomAsset m_MainMap; //= CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Map\\Sewers.bmp", 1000, 1000));

	std::vector<std::string> m_Levels;
	int SelectedLevel = 0;
};