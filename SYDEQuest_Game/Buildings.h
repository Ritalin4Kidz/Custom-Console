#pragma once
#include "Scene.h"
#include "SYDEstdafx.h"
#include "SYDEQuestGame.h"

class Building_Defaults {
public:
	static ConsoleWindow Base_Input(ConsoleWindow window, CustomAsset m_Map);
};

class Test_Building : public GameScene {
public:
	Test_Building();
	~Test_Building();
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	static CustomAsset m_bg;
	static CustomAsset m_Map;
	static bool hasLoaded;
};