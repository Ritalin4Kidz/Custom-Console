#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include "ShopItem.h"
#include <SYDEClickableButton.h>

/*
TODO:
BUY BUTTON BUYS MOVE WHEN GOLD SHOWING
ADD OPTION TO HEAL
PLAN INVENTORY ITEMS
MOVE SWAPPING
SHOW DETAILS IN SHOP
ITEM GENERATION
*/
class ShopScene : public GameScene
{
public:
	ShopScene() { m_SceneTag = "Shop Scene"; m_isTransient = true;}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;

	void test();

private:
	vector<ShopItem*> m_ShopItems;
	vector<SYDEClickableButton> m_BuyButtons;
};