#include "PostBattleScene.h"

void successClick()
{
	SydeRogueLikeStatics::setSceneTag("Main Map Scene");
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
	for (int i = 0; i < m_UIControl.size(); i++)
	{
		window = m_UIControl[i]->draw_ui(window);
	}
	//SHOW STATS


	return window;
}

void PostBattleScene::onNewScene()
{
	//IF SUCCESS
	if (SydeRogueLikeStatics::getFightSuccess())
	{
		m_UIControl.push_back(new SYDEClickableButton(
			"Continue",
			Vector2(44, 16),
			Vector2(8, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			successClick
		));
		m_UIControl.push_back(new SYDELabel(
			"Battle Won",
			Vector2(6, 4 ),
			Vector2(10, 1),
			BLACK,
			true));
	}
	else
	{
		m_UIControl.push_back(new SYDEClickableButton(
			"Back To Menu",
			Vector2(40, 16),
			Vector2(12, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			failureClick

		));
		m_UIControl.push_back(new SYDELabel(
			"Battle Lost",
			Vector2(6, 4),
			Vector2(11, 1),
			BLACK,
			true));
	}
}

void PostBattleScene::destroyScene()
{
	m_UIControl.clear();
}
