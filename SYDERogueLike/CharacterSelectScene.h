#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"
#include "PlayerIncludeHeader.h"
#include "TagToPlayer.hpp"
#include <vector>

class CharacterSelectScene : public GameScene
{
public:
	CharacterSelectScene() { m_SceneTag = "Character Select Scene"; }
	virtual ~CharacterSelectScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void destroyScene() override;

	static void CallNextChar() { nextCharCall = true; }
	static void CallPrevChar() { prevCharCall = true; }
	static void CallStartGame() { startGameCall = true; }

private:

	static bool nextCharCall;
	static bool prevCharCall;
	static bool startGameCall;

	std::vector<PlayerSelectObject> m_PlayersVec;
	CustomAsset m_Spotlight = CustomAsset(40, 20, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\CharSelectBG.bmp", 20, 20));
	int m_SelectedPlayer = 0;

	vector<SYDEUI*> m_UIControl = vector<SYDEUI*>();
};