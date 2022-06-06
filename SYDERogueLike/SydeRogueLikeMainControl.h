#pragma once
#include "SYDEstdafx.h"
#include "GameScene.h"
#include "MainMenuScenes.h"
#include "SydeRogueLikeStatics.h"
#include "BattleScene.h"
#include "MainMapScene.h"
#include "CharacterSelectScene.h"
#include "PostBattleScene.h"
#include "ShopScene.h"
class SYDERogueLikeMainControl : public SYDEWindowGame {
public:
	SYDERogueLikeMainControl() { init(); }
	virtual ~SYDERogueLikeMainControl() {}

	void init();

	void initNewScene();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;

private:
	std::vector<GameScene*> m_ScenesList = std::vector<GameScene*>(
		{
			new MainSplashScreenScene(),
			new MainMenuScene(),
			new BattleScene(),
			new MainMapScene(),
			new CharacterSelectScene(),
			new PostBattleScene(),
			new ShopScene()
		});

	GameScene* mainScene;
};