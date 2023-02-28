#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
#include "MapConfig.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"


class PlayerStateScene : public GameScene
{
public:
	PlayerStateScene() { m_SceneTag = "Player State Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void destroyScene() override;

	string TypeToString(_SQType type);

private:

	CustomAsset playerAsset = CustomAsset();
};