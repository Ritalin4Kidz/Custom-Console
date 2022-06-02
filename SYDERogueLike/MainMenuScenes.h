#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include "PlayerFuri.h"
/*
THIS CLASS ONLY NEEDS TO HANDLE SCENES WE CONSIDER UNDER THE MAIN MENU FOR SAKE OF KEEPING THINGS UNDER CONTROL
*/
class MainSplashScreenScene : public GameScene
{
public:
	MainSplashScreenScene() { m_SceneTag = "Main Splashscreen"; }
	virtual ~MainSplashScreenScene() {}

	void test();

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
};


class MainMenuScene : public GameScene
{
public:
	MainMenuScene() { m_SceneTag = "Main Menu"; }
	virtual ~MainMenuScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
};