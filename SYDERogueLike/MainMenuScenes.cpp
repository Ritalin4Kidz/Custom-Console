#include "MainMenuScenes.h"

void characterSelectClick()
{
	SydeRogueLikeStatics::setSceneTag("Character Select Scene");
}

void challengeModeClick()
{
	SydeRogueLikeStatics::toggleInitMap(true);
	SydeRogueLikeStatics::setSceneTag("Challenge Map 001 Scene");
	SydeRogueLikeStatics::setLevelSceneTag("Challenge Map 001 Scene");
	SydeRogueLikeStatics::setPlayer(std::shared_ptr<Player>(new PlayerFuri(99)));
}

void exitGameClick()
{
	SydeRogueLikeStatics::setSceneTag("Exit Game");
}

ConsoleWindow MainMenuScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	//TEMP
	window.setTextAtPoint(Vector2(0, 1), "MAIN MENU", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(36, 19), "Version: 0.0.1.0-alpha", BRIGHTWHITE);
	return window;
}

void MainMenuScene::onNewScene()
{
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"New Game",
		Vector2(2, 3),
		Vector2(8, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		characterSelectClick,
		"SwapViewLBL",
		"SwapViewLBL"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Challenges",
		Vector2(2, 5),
		Vector2(10, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		challengeModeClick,
		"challengeModeClick",
		"challengeModeClick"
	)));


	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Exit Game",
		Vector2(2, 18),
		Vector2(9, 1),
		BRIGHTWHITE_BRIGHTRED_BG,
		NULLCOLOUR,
		false,
		exitGameClick,
		"SwapViewLBL",
		"SwapViewLBL"
	)));
}

void MainSplashScreenScene::test()
{
	SydeRogueLikeStatics::setPlayer(std::shared_ptr<Player>(new PlayerFuri(5)));
}

/// <summary>
/// This scene just needs to display a splashscreen really
/// </summary>
/// <param name="window"></param>
/// <param name="windowWidth"></param>
/// <param name="windowHeight"></param>
/// <returns></returns>
ConsoleWindow MainSplashScreenScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	//TEMP
	window = m_BGImage.draw_asset(window, Vector2(1,0));
	window.setTextAtPoint(Vector2(0, 1), "SYDE ROGUELIKE", BRIGHTWHITE);
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		SydeRogueLikeStatics::setSceneTag("Main Menu");
		return window;
	}
	window.setTextAtPoint(Vector2(20, 19), "PRESS SPACE TO START!", BRIGHTWHITE);
	return window;
}

void MainSplashScreenScene::onNewScene()
{
}
