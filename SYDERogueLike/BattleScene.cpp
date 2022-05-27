#include "BattleScene.h"
ConsoleWindow BattleScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	/*
	FOR TEST, WE JUST NEED TO DRAW A SIMPLE FIGHT WITH AN ORC
	*/
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

	window = m_Enemy->drawAnimationAsset(window, Vector2(40, 1));
	return window;
}

void BattleScene::onNewScene()
{
	test();
}

void BattleScene::test()
{
	m_Enemy = new OrcEnemy(5);
}

void BattleScene::doMovePreWork()
{
	//GENERATE ENEMY MOVE

	//DETERMINE THE ORDER OF THE MOVES

	//ANY OTHER LOADING
}
