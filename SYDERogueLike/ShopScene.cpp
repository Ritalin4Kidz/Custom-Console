#include "ShopScene.h"

bool ShopScene::doBuy = false;
int ShopScene::lastBoughtItem = -1;

void BackToMapClick()
{
	SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
}

void shopClick()
{
	ShopScene::doBuy = true;
	ShopScene::lastBoughtItem = stoi(SYDEClickableButton::getLastButtonTag());
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

	if (doBuy)
	{
		doBuy = false;
		purchaseItem();
	}

	for (int i = 0; i < m_ShopItems.size(); i++)
	{
		int x = ((i % 3) * 12) + 24;
		int y = i % 6 >= 3 ? 11 : 2;

		window = m_ShopItems[i].getBackIcon().draw_asset(window, Vector2(x,y));
		window = m_ShopItems[i].getIcon().draw_asset(window, Vector2(x, y));

		window.setTextAtPoint(Vector2(x, y + 6), m_ShopItems[i].getName(), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(x, y + 7), to_string(m_ShopItems[i].getPrice()), BRIGHTWHITE);
	}

	window.setTextAtPoint(Vector2(1, 2), "Money: " + to_string(SydeRogueLikeStatics::getPlayer()->getMoney()), BLACK_LIGHTGREY_BG);
	return window;
}

void ShopScene::onNewScene()
{
	//GENERATE SHOP ITEMS
	//6 ITEMS, TOP 3 ALL MOVES
	//BOTTOM 3 ALL ITEMS
	doBuy = false;
	test();

	for (int i = 0; i < m_ShopItems.size(); i++)
	{
		int x = ((i % 3) * 12) + 24;
		int y = i % 6 >= 3 ? 11 : 2;
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			"    Buy   ",
			Vector2(x, y + 5),
			Vector2(10, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			shopClick,
			to_string(i),
			"ShopData-" + to_string(i))));
	}

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Back To Map",
		Vector2(1, 19),
		Vector2(11, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		BackToMapClick
	)));
}

void ShopScene::destroyScene()
{
	m_ShopItems.clear();
}

void ShopScene::test()
{
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\RockIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));


	/*m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_COMMON, "Slash",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(75, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_RARE, "Ember",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(100, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_LEGEND, "Fireball",
		shared_ptr<ItemClass>(new RockItem())));

	m_ShopItems.push_back(ShopItem(12, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_COMMON, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(75, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_RARE, "Rock",
		shared_ptr<ItemClass>(new RockItem())));
	m_ShopItems.push_back(ShopItem(100, CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\FireIcon.bmp", 5, 5)), SIR_LEGEND, "Rock",
		shared_ptr<ItemClass>(new RockItem())));*/
}

void ShopScene::purchaseItem()
{
	if (SydeRogueLikeStatics::spendPlayerMoney(m_ShopItems[lastBoughtItem].getPrice()))
	{
		SydeRogueLikeStatics::addPlayerInv(m_ShopItems[lastBoughtItem].getItem());
		m_ShopItems[lastBoughtItem].setIcon(CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\SoldOut.bmp", 5, 5)));
		m_ShopItems[lastBoughtItem].setName("Sold Out");
		m_ShopItems[lastBoughtItem].setPrice(0);
		setUIEnabled(false, lastBoughtItem);
	}
}
