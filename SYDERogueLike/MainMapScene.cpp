#include "MainMapScene.h"
std::string MainMapScene::m_MapToLoad = "";
void MainMapScene::onNewScene()
{
	test();
}

void MainMapScene::test()
{
	m_MapToLoad = "SydeCoast";
	setUpMap();
	cameraPos = Vector2(20, 50);
}

void MainMapScene::setUpMap()
{
	string IslandBmp = "EngineFiles\\Levels\\Map\\" + m_MapToLoad + ".bmp";
	string IslandPathData = "EngineFiles\\Levels\\PathData\\" + m_MapToLoad + "_WildSpawns.bmp";
	wstring wIslandBmp = wstring(IslandBmp.begin(), IslandBmp.end());
	wstring wIslandPathData = wstring(IslandPathData.begin(), IslandPathData.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_MapBg = CustomAsset(200, 100, AssetsClass::get_bmp_as_direct_colour_class_array((WCHAR*)wIslandBmp.c_str(), 100, 100));
	Bitmap* SpawnData = new Bitmap((WCHAR*)wIslandPathData.c_str(), FALSE);
	for (int i = 0; i < 100; i++)
	{
		for (int ii = 0; ii < 100; ii++)
		{
			Gdiplus::Color* pixelColor = new Gdiplus::Color();
			SpawnData->GetPixel(ii + 1, i, pixelColor);
			//GET BASED OFF pixelColour.GetRed() == 243 && pixelColour.GetGreen() == 21 && pixelColour.GetBlue() == 246
			addSpace(Vector2(ii * 2, i), *pixelColor);
			delete[] pixelColor;
		}
	}
	delete[] SpawnData;
}

void MainMapScene::addSpace(Vector2 location, Color pix)
{
/*
* R - Pool of the spawn
	200 = Split path
	105 = Random Space
	28 = Boss
	etc
  G - Path Number
	0 = Initial path, when split it will change number
		(IN CONFIG FILE, WE WILL SET WHAT OPTIONS ARE AVAILABLE AT EACH SPLIT, eg 200,0,25 = {2} as paths to split onto)
  B - Position of the path
	0 = start of path, when/if we split we can move to this starting point
*/

	//WE NEED TO USE THE CONFIG FILE TO SORT OUT SPLIT PATHS
	//WE ALSO NEED TO SORT THE PATHS HERE
}

ConsoleWindow MainMapScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_MapBg.draw_asset(window, Vector2(cameraPos.getX() + (windowWidth/2), cameraPos.getY() + (windowHeight/2)), windowWidth, windowHeight);
	return window;
}