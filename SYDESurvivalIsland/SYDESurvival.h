#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"

#include "NoiseMap.h"


class SYDESurvival : public SYDEWindowGame {
public:
	SYDESurvival() { init(); }
	virtual ~SYDESurvival() {}
	void init();

	void test();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;
private:
	CustomAsset m_Island;
	Vector2 m_CameraPos = Vector2(0,0);

	//LOWER THE NUMBER, THE STRONGER THE GRADIENT
	double gradientStrength = 0.999;

	double gradientLength = 85;

	int _height = 1000;
	int _width = 500;
};