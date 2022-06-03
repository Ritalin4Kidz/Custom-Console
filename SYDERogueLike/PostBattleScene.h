#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include <SYDEClickableButton.h>

class PostBattleScene : public GameScene
{
public:
	PostBattleScene() { m_SceneTag = "Post Battle Scene"; }
	virtual ~PostBattleScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;
private:
	vector<SYDEUI*> m_UIControl = vector<SYDEUI*>();
};