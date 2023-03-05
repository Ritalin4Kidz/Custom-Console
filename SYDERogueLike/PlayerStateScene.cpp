#include "pch.h"
#include "PlayerStateScene.h"

void returnToMap()
{
	SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
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
		window.setTextAtPoint(Vector2(2, (i *2) + 11), SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getName() + ": " +
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

void PlayerStateScene::onNewScene()
{
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"BACK TO MAP",
		Vector2(0, 19),
		Vector2(11, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		returnToMap
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
