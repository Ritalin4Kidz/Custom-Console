#include "LevelSelectScene.h"
AssetsClass LevelSelectScene::astVars = AssetsClass();
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
	window.setTextAtPoint(Vector2(2, 18), m_LevelList[m_SelectedLevel].m_MapTag, BRIGHTWHITE);
	window = m_MapPreview.draw_asset(window, Vector2(6, 3));
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		m_SelectedLevel++;
		if (m_SelectedLevel >= m_LevelList.size())
		{
			m_SelectedLevel = 0;
		}
		changePreviewMap();
	}
	else if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		m_SelectedLevel--;
		if (m_SelectedLevel < 0)
		{
			m_SelectedLevel = m_LevelList.size() - 1;
		}
		changePreviewMap();
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		SydeRogueLikeStatics::toggleInitMap(true);
		SydeRogueLikeStatics::setSceneTag(m_LevelList[m_SelectedLevel].m_SceneTag);
		return window;
	}

	//ON SELECTED LEVEL
	//SydeRogueLikeStatics::toggleInitMap(true);

	return window;
}

void LevelSelectScene::onNewScene()
{
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
