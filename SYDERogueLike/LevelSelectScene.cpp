#include "LevelSelectScene.h"
AssetsClass LevelSelectScene::astVars = AssetsClass();
bool LevelSelectScene::nextClickCall = false;
bool LevelSelectScene::prevClickCall = false;
bool LevelSelectScene::backClickCall = false;
bool LevelSelectScene::startClickCall = false;
void backClick()
{
	LevelSelectScene::backClickCall = true;
}

void prevClick()
{
	LevelSelectScene::prevClickCall = true;
}

void nextClick()
{
	LevelSelectScene::nextClickCall = true;
}

void startClick()
{
	LevelSelectScene::startClickCall = true;
}

ConsoleWindow LevelSelectScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	//TEMP
	window.setTextAtPoint(Vector2(0, 1), "LEVEL SELECT", BRIGHTWHITE);
	for (int i = 0; i < windowWidth; i++)
	{
		window.setTextAtPoint(Vector2(i, 18), " ", YELLOW_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 19), " ", WHITE_WHITE_BG);
	}
	int textStart = 30 - (m_LevelList[m_SelectedLevel].m_DisplayTag.length()/2);
	window.setTextAtPoint(Vector2(textStart, 18), m_LevelList[m_SelectedLevel].m_DisplayTag, BLACK_YELLOW_BG);
	window = m_MapPreview.draw_asset(window, Vector2(6, 3));
	if (nextClickCall)
	{
		nextClickCall = false;
		m_SelectedLevel++;
		if (m_SelectedLevel >= m_LevelList.size())
		{
			m_SelectedLevel = 0;
		}
		changePreviewMap();
	}
	else if (prevClickCall)
	{
		prevClickCall = false;
		m_SelectedLevel--;
		if (m_SelectedLevel < 0)
		{
			m_SelectedLevel = m_LevelList.size() - 1;
		}
		changePreviewMap();
	}
	if (startClickCall)
	{
		startClickCall = false;
		SydeRogueLikeStatics::toggleInitMap(true);
		SydeRogueLikeStatics::setSceneTag(m_LevelList[m_SelectedLevel].m_SceneTag);
		SydeRogueLikeStatics::setLevelSceneTag(m_LevelList[m_SelectedLevel].m_SceneTag);
		return window;
	}
	if (backClickCall)
	{
		backClickCall = false;
		SydeRogueLikeStatics::setSceneTag("Character Select Scene");
		return window;
	}

	//ON SELECTED LEVEL
	//SydeRogueLikeStatics::toggleInitMap(true);

	return window;
}

void LevelSelectScene::onNewScene()
{
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"<<",
		Vector2(3, 19),
		Vector2(2, 1),
		BLACK_BRIGHTRED_BG,
		NULLCOLOUR,
		false,
		prevClick,
		"prevClick",
		"prevClick"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		">>",
		Vector2(55, 19),
		Vector2(2, 1),
		BLACK_BRIGHTRED_BG,
		NULLCOLOUR,
		false,
		nextClick,
		"nextClick",
		"nextClick"
	)));


	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Char Select",
		Vector2(10, 19),
		Vector2(11, 1),
		WHITE_AQUA_BG,
		NULLCOLOUR,
		false,
		backClick,
		"backClick",
		"backClick"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Start Game",
		Vector2(40, 19),
		Vector2(10, 1),
		BRIGHTWHITE_BRIGHTGREEN_BG,
		NULLCOLOUR,
		false,
		startClick,
		"startClick",
		"startClick"
	)));

	LevelSelectScene::nextClickCall = false;
	LevelSelectScene::prevClickCall = false;
	LevelSelectScene::backClickCall = false;
	LevelSelectScene::startClickCall = false;

	m_SelectedLevel = 0;
	changePreviewMap();
}

void LevelSelectScene::changePreviewMap()
{
	string bmpFile = "EngineFiles\\Levels\\MapPreviews\\" + m_LevelList[m_SelectedLevel].m_MapTag + ".bmp";
	if (SYDEFileDefaults::exists(bmpFile.c_str()))
	{
		wstring wbmpFile = wstring(bmpFile.begin(), bmpFile.end());
		m_MapPreview = CustomAsset(50, 15, astVars.get_bmp_as_direct_colour_class_array((WCHAR*)wbmpFile.c_str(), 25, 15));
	}
	else
	{
		m_MapPreview = CustomAsset(50, 15, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Levels\\MapPreviews\\unknown.bmp", 25, 15));
	}
}
