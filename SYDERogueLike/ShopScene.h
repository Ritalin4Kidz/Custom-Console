#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include <SYDEClickableButton.h>

class ShopScene : public GameScene
{
public:
	ShopScene() { m_SceneTag = "Shop Scene"; }
	virtual ~ShopScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;
private:
	vector<SYDEUI*> m_UIControl = vector<SYDEUI*>();
};