#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"

#include "OrcEnemy.h"

class BattleScene : public GameScene
{
public:
	BattleScene() { m_SceneTag = "Battle Scene"; }
	virtual ~BattleScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void test();


	void doMovePreWork();

private:
	Enemy* m_Enemy;
};