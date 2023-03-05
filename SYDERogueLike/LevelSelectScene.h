#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include "SYDEFileDefaults.h"
#include "SYDEEngineUI.h"
struct LevelSelectObject
{
public:
	LevelSelectObject(string s, string t, string d) { m_SceneTag = s; m_MapTag = t; m_DisplayTag = d; }
	string m_SceneTag;
	string m_MapTag;
	string m_DisplayTag;
};

class LevelSelectScene : public GameScene
{
public:
	LevelSelectScene() { m_SceneTag = "Level Select Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void changePreviewMap();

	static bool nextClickCall;
	static bool prevClickCall;
	static bool backClickCall;
	static bool startClickCall;

private:
	int m_SelectedLevel = 0;
	static AssetsClass astVars;

	std::vector<LevelSelectObject> m_LevelList = std::vector<LevelSelectObject>( {
		LevelSelectObject("SYDE Coast Map Scene", "SydeCoast", "Syde Coast"),
		LevelSelectObject("Meow Coast Map Scene", "MeowCoast", "Meowscia Isles")
	});
	CustomAsset m_MapPreview = CustomAsset(50, 15, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Preview\\DefaultPreview.bmp", 25, 15));

};