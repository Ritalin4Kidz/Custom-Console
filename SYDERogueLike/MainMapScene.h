#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

class MainMapScene : public GameScene
{
public:
	MainMapScene() { m_SceneTag = "Main Map"; }
	virtual ~MainMapScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
};