#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
#include "MapConfig.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"
#include "ItemsHeader.h"
#include "MovesHeader.h"

enum PlayerStateScene_State
{
	PSS_PlayerViewState = 0,
	PSS_InventoryViewState = 1,
	PSS_RemoveMoveState = 2,
	PSS_PlayerMovesState = 3,
	PSS_PlayerOtherState = 4,
	PSS_InventoryDetailsViewState = 5
};

class PlayerStateScene : public GameScene
{
public:
	PlayerStateScene() { m_SceneTag = "Player State Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow drawPV(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drawIV(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drawIVDetails(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow drawRM(ConsoleWindow window, int windowWidth, int windowHeight);

	void test();

	void onNewScene() override;

	void destroyScene() override;

	void validateInventory();

	void createBaseUI();

	static PlayerStateScene_State m_SceneState;

	static void addInvStart(int amt) {
		if ((inventoryStart + amt) >= SydeRogueLikeStatics::getPlayer()->getInventory().size())
		{
			return;
		}
		inventoryStart += amt;
		if (inventoryStart < 0)
		{
			inventoryStart = 0;
		}
	}

	static bool useItemCall;
	static bool useDeleteCall;
	static int itemIndex;

private:
	static int inventoryStart;
	
	SYDEClickableButton invPrev;
	SYDEClickableButton invNext;
	CustomAsset playerAsset = CustomAsset();

	SYDEClickableButton confirmItemButton;
	SYDEClickableButton backItemButton;
};