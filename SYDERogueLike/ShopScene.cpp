#include "ShopScene.h"

void BackToMapClick()
{
	SydeRogueLikeStatics::setSceneTag("SYDE Coast Map Scene");
}

void shopClick()
{

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

	for (int i = 0; i < m_ShopItems.size(); i++)
	{
		window = m_ShopItems[i]->getBackIcon().draw_asset(window, Vector2((i * 12) + 24, 4));
		window = m_ShopItems[i]->getIcon().draw_asset(window, Vector2((i * 12) + 24, 4));

		window.setTextAtPoint(Vector2((i * 12) + 24, 12), m_ShopItems[i]->getName(), BRIGHTWHITE);
		window.setTextAtPoint(Vector2((i * 12) + 24, 13), to_string(m_ShopItems[i]->getPrice()), BRIGHTWHITE);
	}


	return window;
}

void ShopScene::onNewScene()
{
	//GENERATE SHOP ITEMS
	//6 ITEMS, TOP 3 ALL MOVES
	//BOTTOM 3 ALL ITEMS
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Back To Map",
		Vector2(21, 18),
		Vector2(11, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		BackToMapClick
	)));
	test();

	for (int i = 0; i < m_ShopItems.size(); i++)
	{
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			"    Buy   ",
			Vector2((i * 12) + 24, 11),
			Vector2(10, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			shopClick,
			to_string(i),
			"ShopData-" + to_string(i))));
	}
}

void ShopScene::destroyScene()
{
	m_ShopItems.clear();
}

void ShopScene::test()
{
	m_ShopItems.push_back(new MoveShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_COMMON, "Flame"));
	m_ShopItems.push_back(new MoveShopItem(75, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_RARE, "Fire"));
	m_ShopItems.push_back(new MoveShopItem(100, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_LEGEND, "Flare"));
}
