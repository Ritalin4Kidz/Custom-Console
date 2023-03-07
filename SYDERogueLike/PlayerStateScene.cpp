#include "pch.h"
#include "PlayerStateScene.h"
PlayerStateScene_State PlayerStateScene::m_SceneState = PSS_PlayerViewState;
void returnToMap()
{
	SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
}

void selectPV()
{
	PlayerStateScene::m_SceneState = PSS_PlayerViewState;
}

void selectIV()
{
	PlayerStateScene::m_SceneState = PSS_InventoryViewState;
}

ConsoleWindow PlayerStateScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTGREY_LIGHTGREY_BG);
		}
	}

	if (m_SceneState == PSS_PlayerViewState)
	{
		window = drawPV(window, windowWidth, windowHeight);
	}
	else if (m_SceneState == PSS_InventoryViewState)
	{
		window = drawIV(window, windowWidth, windowHeight);
	}
	return window;
}

ConsoleWindow PlayerStateScene::drawPV(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window.setTextAtPoint(Vector2(2, 1), SydeRogueLikeStatics::getPlayer()->getName(), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 3), "Health: " + to_string(SydeRogueLikeStatics::getPlayer()->getHealth()) + "/" + to_string(SydeRogueLikeStatics::getPlayer()->getMaxHealth()), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 4), "Attack: " + to_string(SydeRogueLikeStatics::getPlayer()->getAttack()), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 5), "Defence: " + to_string(SydeRogueLikeStatics::getPlayer()->getDefence()), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 6), "Speed: " + to_string(SydeRogueLikeStatics::getPlayer()->getSpeed()), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 7), "M Attack: " + to_string(SydeRogueLikeStatics::getPlayer()->getMagicAttack()), BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(2, 8), "M Defence: " + to_string(SydeRogueLikeStatics::getPlayer()->getMagicDefence()), BLACK_LIGHTGREY_BG);

	window.setTextAtPoint(Vector2(2, 10), "Moves: ", BLACK_LIGHTGREY_BG);
	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getMoves().size(); i++)
	{
		window.setTextAtPoint(Vector2(2, (i * 2) + 11), SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getName() + ": " +
			to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getUsagesLeft()) + "/" +
			to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getMaxUsages())
			, BLACK_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(4, (i * 2) + 12), TypeToString(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getType()) + "  P: " +
			to_string((int)SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getPower())
			, BLACK_LIGHTGREY_BG);
	}

	window = playerAsset.draw_asset(window, Vector2(40, 12));

	return window;
}

ConsoleWindow PlayerStateScene::drawIV(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getInventory().size(); i++)
	{
		int x = (20 * (i % 3)) + 4;
		int y = i % 6 >= 3 ? 12 : 2;
		window = SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i)->getItemIcon().draw_asset(window, Vector2(x, y));
	}
	return window;
}

void PlayerStateScene::test()
{
	if (SydeRogueLikeStatics::getPlayer()->getInventory().size() == 0)
	{
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
	}
}

void PlayerStateScene::onNewScene()
{
	test();
	PlayerStateScene::m_SceneState = PSS_PlayerViewState;
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"BACK TO MAP",
		Vector2(0, 19),
		Vector2(11, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		returnToMap
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"PV",
		Vector2(30, 1),
		Vector2(2, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		selectPV
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"IV",
		Vector2(34, 1),
		Vector2(2, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		selectIV
	)));

	string charBmp = "EngineFiles\\CharacterBMPS\\" + SydeRogueLikeStatics::getPlayer()->getName() + ".bmp";
	wstring wCharBmp = wstring(charBmp.begin(), charBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	playerAsset.setAsset(20, 10, AssetsClass::get_bmp_as_direct_colour_class_array((WCHAR*)wCharBmp.c_str(), 10, 10));
}

void PlayerStateScene::destroyScene()
{
}

string PlayerStateScene::TypeToString(_SQType type)
{
	switch (type)
	{
	case Fire:
		return "Fire";
	case Water:
		return "Water";
	case Air:
		return "Air";
	case Grass:
		return "Grass";
	case Metal:
		return "Metal";
	case Melee:
		return "Melee";
	case Snow:
		return "Snow";
	case Electric:
		return "Electric";
	case Telekinetic:
		return "Telekinetic";
	}
	return "Typeless";
}
