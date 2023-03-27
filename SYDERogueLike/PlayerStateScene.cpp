#include "pch.h"
#include "PlayerStateScene.h"
int PlayerStateScene::inventoryStart = 0;
PlayerStateScene_State PlayerStateScene::m_SceneState = PSS_PlayerViewState;

bool PlayerStateScene::useItemCall = false;
bool PlayerStateScene::useDeleteCall = false;
int	 PlayerStateScene::itemIndex = -1;

void returnToMap()
{
	SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
}

void selectPV()
{
	PlayerStateScene::m_SceneState = PSS_PlayerViewState;
}

void selectMV()
{
	PlayerStateScene::m_SceneState = PSS_PlayerMovesState;
}

void selectOV()
{
	PlayerStateScene::m_SceneState = PSS_PlayerOtherState;
}

void selectIV()
{
	PlayerStateScene::m_SceneState = PSS_InventoryViewState;
}

void inventoryStateNextClick()
{
	PlayerStateScene::addInvStart(4);
}

void inventoryStatePrevClick()
{
	PlayerStateScene::addInvStart(-4);
}

void psInventoryItemClick()
{
	PlayerStateScene::useItemCall = true;
	PlayerStateScene::itemIndex = stoi(CustomAsset_Clickable::getLastButtonTag());
}

void psDeleteClick()
{
	PlayerStateScene::useDeleteCall = true;
	PlayerStateScene::itemIndex = stoi(SYDEClickableButton::getLastButtonTag());
}

void psNullClick()
{

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

	if (m_SceneState == PSS_PlayerViewState || m_SceneState == PSS_PlayerMovesState  || m_SceneState == PSS_PlayerOtherState)
	{
		window = drawPV(window, windowWidth, windowHeight);
	}
	else if (m_SceneState == PSS_InventoryViewState)
	{
		window = drawIV(window, windowWidth, windowHeight);
	}
	else if (m_SceneState == PSS_RemoveMoveState)
	{
		window = drawRM(window, windowWidth, windowHeight);
	}
	return window;
}

ConsoleWindow PlayerStateScene::drawPV(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 2; i < 58; i++)
	{
		for (int ii = 2; ii < 12; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(2, 2), SydeRogueLikeStatics::getPlayer()->getName(), BRIGHTWHITE);
	if (m_SceneState == PSS_PlayerViewState)
	{
		window.setTextAtPoint(Vector2(2, 3), "Health: " + to_string(SydeRogueLikeStatics::getPlayer()->getHealth()) + "/" + to_string(SydeRogueLikeStatics::getPlayer()->getMaxHealth()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 4), "Attack: " + to_string(SydeRogueLikeStatics::getPlayer()->getAttack()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 5), "Defence: " + to_string(SydeRogueLikeStatics::getPlayer()->getDefence()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 6), "Speed: " + to_string(SydeRogueLikeStatics::getPlayer()->getSpeed()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 7), "M Attack: " + to_string(SydeRogueLikeStatics::getPlayer()->getMagicAttack()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 8), "M Defence: " + to_string(SydeRogueLikeStatics::getPlayer()->getMagicDefence()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 9), "Money: " + to_string(SydeRogueLikeStatics::getPlayer()->getMoney()), BRIGHTWHITE);
	}
	else if (m_SceneState == PSS_PlayerMovesState)
	{
		window.setTextAtPoint(Vector2(2, 3), "Moves: ", BRIGHTWHITE);
		for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getMoves().size(); i++)
		{
			window.setTextAtPoint(Vector2(2, (i * 2) + 4), SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getName() + ": " +
				to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getUsagesLeft()) + "/" +
				to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getMaxUsages())
				, BRIGHTWHITE);
			window.setTextAtPoint(Vector2(4, (i * 2) + 5), SydeRogueLikeStatics::TypeToString(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getType()) + "  P: " +
				to_string((int)SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getPower())
				, BRIGHTWHITE);
		}
	}
	else if (m_SceneState == PSS_PlayerOtherState)
	{
		window.setTextAtPoint(Vector2(2, 3), "Ability: " + SydeRogueLikeStatics::getPlayer()->getAbility().m_AbilityName, BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 4), SydeRogueLikeStatics::getPlayer()->getAbility().m_Description, BRIGHTWHITE);

		window.setTextAtPoint(Vector2(2, 6), "Level: " + to_string(SydeRogueLikeStatics::getPlayer()->getLevel()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(2, 7), "XP: " + SydeRogueLikeStatics::getPlayer()->getXPStr(), BRIGHTWHITE);
	}

	window = playerAsset.draw_asset(window, Vector2(40, 12));

	return window;
}

ConsoleWindow PlayerStateScene::drawIV(ConsoleWindow window, int windowWidth, int windowHeight)
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

	if (useItemCall)
	{
		useItemCall = false;
		SydeRogueLikeStatics::validatePlayerJson();
		json player = SydeRogueLikeStatics::getPlayer()->getJSONTag();
		SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(itemIndex)->useItem(&player);
		SydeRogueLikeStatics::validatePlayerFromJson(player);
		SydeRogueLikeStatics::removePlayerInv(itemIndex);
		validateInventory();

		if (SydeRogueLikeStatics::getPlayer()->getMoves().size() > 4)
		{
			//WE GOT TO REMOVE SOME
			PlayerStateScene::m_SceneState = PSS_RemoveMoveState;
			clearUI();
			for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getMoves().size(); i++)
			{
				addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
					"DELETE",
					Vector2(25, (i * 2) + 3),
					Vector2(6, 1),
					BRIGHTWHITE_RED_BG,
					NULLCOLOUR,
					false,
					psDeleteClick,
					to_string(i)
				)));
			}

		}

		return window;
	}

	for (int i = 0; (i + inventoryStart) < SydeRogueLikeStatics::getPlayer()->getInventory().size() && i < 4; i++)
	{
		int x = (20 * (i % 2)) + 24;
		int y = i % 4 >= 2 ? 12 : 2;
		window = SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i + inventoryStart)->getItemIcon().draw_asset(window, Vector2(x, y));
		window.setTextAtPoint(Vector2(x, y + 7), SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i + inventoryStart)->getName(), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(1, 4), "    Inventory    ", BLACK_BRIGHTWHITE_BG);
	window = invNext.draw_ui(window);
	window = invPrev.draw_ui(window);
	return window;
}

ConsoleWindow PlayerStateScene::drawRM(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window.setTextAtPoint(Vector2(2, 1), "DELETE A MOVE: ", BLACK_LIGHTGREY_BG);
	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getMoves().size(); i++)
	{
		window.setTextAtPoint(Vector2(2, (i * 2) + 3), SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getName() + ": " +
			to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getUsagesLeft()) + "/" +
			to_string(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getMaxUsages())
			, BLACK_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(4, (i * 2) + 4), SydeRogueLikeStatics::TypeToString(SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getType()) + "  P: " +
			to_string((int)SydeRogueLikeStatics::getPlayer()->getMoveAtIndex(i)->getPower())
			, BLACK_LIGHTGREY_BG);
	}

	if (useDeleteCall)
	{
		useDeleteCall = false;
		m_SceneState = PSS_PlayerViewState;
		SydeRogueLikeStatics::removePlayerMove(itemIndex);
		clearUI();
		createBaseUI();
	}


	return window;
}

void PlayerStateScene::test()
{
	if (SydeRogueLikeStatics::getPlayer()->getInventory().size() == 0)
	{
		/*SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new RockItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new RockItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new RockItem()));*/
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new MoveItemClass(std::shared_ptr<Move>(new FireballMove()),
			16, 8, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ItemIcons\\FireTM.bmp", 8, 8), 
			"Fireball TM")));
		SydeRogueLikeStatics::getPlayer()->AddInventory(shared_ptr<ItemClass>(new PotionItem()));
	}
}

void PlayerStateScene::onNewScene()
{
	//test();
	inventoryStart = 0;
	useItemCall = false;
	useDeleteCall = false;
	itemIndex = -1;
	PlayerStateScene::m_SceneState = PSS_PlayerViewState;

	createBaseUI();

	invPrev = SYDEClickableButton(
		"<<",
		Vector2(1, 5),
		Vector2(2, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		inventoryStatePrevClick,
		"prevInv",
		"prevInv"
	);
	invPrev.setEnabled(true);
	invNext = SYDEClickableButton(
		">>",
		Vector2(16, 5),
		Vector2(2, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		inventoryStateNextClick,
		"nextInv",
		"nextInv"
	);
	invNext.setEnabled(true);

	validateInventory();

	string charBmp = "EngineFiles\\CharacterBMPS\\" + SydeRogueLikeStatics::getPlayer()->getName() + ".bmp";
	wstring wCharBmp = wstring(charBmp.begin(), charBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	playerAsset.setAsset(20, 10, AssetsClass::get_bmp_as_direct_colour_class_array((WCHAR*)wCharBmp.c_str(), 10, 10));
}

void PlayerStateScene::destroyScene()
{
}

void PlayerStateScene::validateInventory()
{
	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getInventory().size(); i++)
	{
		if (SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i)->isUsableOutBattle())
		{
			SydeRogueLikeStatics::getPlayer()->SetInventoryDetailsAtIndex(i, psInventoryItemClick, to_string(i));
		}
		else
		{
			SydeRogueLikeStatics::getPlayer()->SetInventoryDetailsAtIndex(i, psNullClick, to_string(i));
		}
	}
	inventoryStart = 0;
}

void PlayerStateScene::createBaseUI()
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

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"PV",
		Vector2(22, 1),
		Vector2(2, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		selectPV
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"MV",
		Vector2(26, 1),
		Vector2(2, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		selectMV
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"OV",
		Vector2(30, 1),
		Vector2(2, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		selectOV
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
}

