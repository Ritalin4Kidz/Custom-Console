#include "ShopScene.h"

void BackToMapClick()
{
	SydeRogueLikeStatics::setSceneTag("Main Map Scene");
}

ConsoleWindow ShopScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTGREY_LIGHTGREY_BG);
		}
	}
	return window;
}

void ShopScene::onNewScene()
{
	//GENERATE SHOP ITEMS
	//6 ITEMS, TOP 3 ALL MOVES
	//BOTTOM 3 ALL ITEMS
	addToUIControl(new SYDEClickableButton(
		"Back To Map",
		Vector2(21, 18),
		Vector2(11, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		BackToMapClick
	));
}

void ShopScene::destroyScene()
{
}
