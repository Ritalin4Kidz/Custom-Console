#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include "PlayerFuri.h"
#include "SYDEEngineUI.h"
/*
THIS CLASS ONLY NEEDS TO HANDLE SCENES WE CONSIDER UNDER THE MAIN MENU FOR SAKE OF KEEPING THINGS UNDER CONTROL
*/
class MainSplashScreenScene : public GameScene
{
public:
	MainSplashScreenScene() { m_SceneTag = "Main Splashscreen"; }

	void test();

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
	CustomAsset m_BGImage = CustomAsset(60, 20, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\MainScreenImage.bmp", 30, 20));
};


class MainMenuScene : public GameScene
{
public:
	MainMenuScene() { m_SceneTag = "Main Menu"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
private:
};