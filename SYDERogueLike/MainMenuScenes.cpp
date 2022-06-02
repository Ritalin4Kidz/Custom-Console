#include "MainMenuScenes.h"

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
	return window;
}

void MainMenuScene::onNewScene()
{
}

void MainSplashScreenScene::test()
{
	SydeRogueLikeStatics::setPlayer(new PlayerFuri(5));
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
	window.setTextAtPoint(Vector2(0, 1), "SYDE ROGUELIKE", BRIGHTWHITE);
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		SydeRogueLikeStatics::setSceneTag("Main Map Scene");
		return window;
	}
	return window;
}

void MainSplashScreenScene::onNewScene()
{
	test();
}
