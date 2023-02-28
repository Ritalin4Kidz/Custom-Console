#pragma once
#include "SYDEstdafx.h"
#include "GameScene.h"
#include "MainMenuScenes.h"
#include "SydeRogueLikeStatics.h"
#include "BattleScene.h"
#include "SydeCoastLevel.h"
#include "CharacterSelectScene.h"
#include "PostBattleScene.h"
#include "ShopScene.h"
#include "PlayerStateScene.h"
class SYDERogueLikeMainControl : public SYDEWindowGame {
public:
	SYDERogueLikeMainControl() { init(); }

	void init();

	void initNewScene();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;

private:
	//DO NOT ADD TRANSIENT SCENES INTO THIS LIST, INSTEAD LET'S DO IT MANUALLY
	std::vector<GameScene*> m_ScenesList = std::vector<GameScene*>(
		{
			new MainSplashScreenScene(),
			new MainMenuScene(),
			new SydeCoastLevel(),
			new CharacterSelectScene(),
			new PostBattleScene(),
			new PlayerStateScene()
		});

	GameScene* mainScene;
};