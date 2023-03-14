#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include "ShopItem.h"
#include <SYDEClickableButton.h>
#include <memory>
#include "ItemsHeader.h"
/*
TODO:
BUY BUTTON BUYS MOVE WHEN GOLD SHOWING
ADD OPTION TO HEAL
PLAN INVENTORY ITEMS
MOVE SWAPPING
SHOW DETAILS IN SHOP
ITEM GENERATION
*/

/*
SHOP MOVE GENERATION:
The moves that can be generated in a shop can only be moves that are learnable by a character
every character has a movepool so we can use that value to determine a list of moves to generate from
*/

class ShopScene : public GameScene
{
public:
	ShopScene() { m_SceneTag = "Shop Scene"; m_isTransient = true;}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;

	void test();

	void generateItems();

	static bool doBuy;
	static int lastBoughtItem;
	void purchaseItem();

private:
	vector<ShopItem> m_ShopItems;
	vector<SYDEClickableButton> m_BuyButtons;
};