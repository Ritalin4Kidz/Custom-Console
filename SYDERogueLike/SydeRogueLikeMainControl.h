#pragma once
#include "SYDEstdafx.h"
#include "GameScene.h"
#include "MainMenuScenes.h"
#include "SydeRogueLikeStatics.h"
#include "BattleScene.h"
#include "SydeCoastLevel.h"
#include "MeowCoastLevel.h"
#include "CharacterSelectScene.h"
#include "PostBattleScene.h"
#include "ShopScene.h"
#include "PlayerStateScene.h"
#include "ChallengeMapLevel.h"
#include "LevelSelectScene.h"
#include "ChallengeSelectScene.h"
class SYDERogueLikeMainControl : public SYDEWindowGame {
public:
	SYDERogueLikeMainControl() { init(); }

	void init();

	void initNewScene();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;

	static bool exitGameCall;

private:
	//DO NOT ADD TRANSIENT SCENES INTO THIS LIST, INSTEAD LET'S DO IT MANUALLY
	std::vector<std::shared_ptr<GameScene>> m_ScenesList = std::vector<std::shared_ptr<GameScene>>(
		{
			std::shared_ptr<GameScene>(new MainSplashScreenScene()),
			std::shared_ptr<GameScene>(new MainMenuScene()),
			std::shared_ptr<GameScene>(new SydeCoastLevel()),
			std::shared_ptr<GameScene>(new CharacterSelectScene()),
			std::shared_ptr<GameScene>(new PostBattleScene()),
			std::shared_ptr<GameScene>(new PlayerStateScene()),
			std::shared_ptr<GameScene>(new LevelSelectScene()),
			std::shared_ptr<GameScene>(new MeowCoastLevel()),
			std::shared_ptr<GameScene>(new ChallengeSelectScene()),
			std::shared_ptr<GameScene>(new ChallengeMap001())
		});

	std::shared_ptr<GameScene> mainScene;
};