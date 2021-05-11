#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "Vector2.h"

class SYDEPlatformer : public SYDEWindowGame {
public:
	SYDEPlatformer() { init(); }
	virtual ~SYDEPlatformer() {}
	void init();
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;


	void AddPositionX(Vector2 add);

	void ApplyMomentum();

private:
	Vector2 PlayerPos = Vector2(2, 3);

	Vector2 CheckPoint = Vector2(2, 3);

	bool checkGrounded();
	bool checkGrounded(ConsoleWindow window);
	float movementTime = 0;
	float momentumTime = 0;

	Vector2 m_Momentum = Vector2(0, 0);
	CustomAsset m_MainMap = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Map\\MainLevel.bmp", 1000, 1000));
};