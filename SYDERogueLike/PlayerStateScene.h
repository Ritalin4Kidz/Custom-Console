#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
#include "MapConfig.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"
#include "ItemsHeader.h"

enum PlayerStateScene_State
{
	PSS_PlayerViewState = 0,
	PSS_InventoryViewState = 1
};

class PlayerStateScene : public GameScene
{
public:
	PlayerStateScene() { m_SceneTag = "Player State Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow drawPV(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drawIV(ConsoleWindow window, int windowWidth, int windowHeight);

	void test();

	void onNewScene() override;

	void destroyScene() override;

	string TypeToString(_SQType type);

	static PlayerStateScene_State m_SceneState;

private:
	CustomAsset playerAsset = CustomAsset();
};