#include "PostBattleScene.h"

void successClick()
{
	SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
}

void failureClick()
{
	SydeRogueLikeStatics::setSceneTag("Character Select Scene");
}

ConsoleWindow PostBattleScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	for (int i = 6; i < windowWidth-6; i++)
	{
		for (int ii = 3; ii < windowHeight - 2; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK_BRIGHTRED_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 3), "POST BATTLE STATS:", BLACK_BRIGHTRED_BG);

	//TODO: IF FAILURE, ADD OPTION TO GO BACK TO MENU
	//IF SUCCESS, GO BACK TO MAP
	//SHOW STATS


	return window;
}

void PostBattleScene::onNewScene()
{
	//IF SUCCESS
	string bossTag = SydeRogueLikeStatics::getEnemy()->getEnemyTag();
	int xpGain = SydeRogueLikeStatics::getEnemy()->getXpGain();
	int moneyGain = SydeRogueLikeStatics::getEnemy()->getMoney();
	SydeRogueLikeStatics::addPlayerXP(xpGain);
	SydeRogueLikeStatics::addPlayerMoney(moneyGain);
	SydeRogueLikeStatics::setEnemy(nullptr);
	if (SydeRogueLikeStatics::getFightSuccess())
	{
		if (bossTag == "Boss")
		{
			SydeRogueLikeStatics::setSceneTag(SydeRogueLikeStatics::getLevelSceneTag());
			SydeRogueLikeStatics::setBattleTag("Boss Defeated");
			return;
		}
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			"Continue",
			Vector2(44, 16),
			Vector2(8, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			successClick
		)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			"Battle Won",
			Vector2(6, 4 ),
			Vector2(10, 1),
			BLACK,
			true)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			"XP Gained: " + std::to_string(xpGain),
			Vector2(6, 5),
			Vector2(20, 1),
			BLACK,
			true)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			"Level: " + to_string(SydeRogueLikeStatics::getPlayer()->getLevel()),
			Vector2(6, 6),
			Vector2(10, 1),
			BLACK,
			true)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			SydeRogueLikeStatics::getPlayer()->getXPStr(),
			Vector2(6, 7),
			Vector2(20, 1),
			BLACK,
			true)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			"Money Gained: " + std::to_string(moneyGain),
			Vector2(6, 8),
			Vector2(20, 1),
			BLACK,
			true)));
	}
	else
	{
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			"Back To Menu",
			Vector2(40, 16),
			Vector2(12, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			failureClick

		)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			"Battle Lost",
			Vector2(6, 4),
			Vector2(11, 1),
			BLACK,
			true)));
	}
}

void PostBattleScene::destroyScene()
{
	
}
