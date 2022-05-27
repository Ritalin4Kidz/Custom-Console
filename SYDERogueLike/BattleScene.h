#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"

class BattleScene : public GameScene
{
public:
	BattleScene() { m_SceneTag = "Battle Scene"; }
	virtual ~BattleScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
};