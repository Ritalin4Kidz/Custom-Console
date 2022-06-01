#include "MainMapScene.h"
std::string MainMapScene::m_MapToLoad = "";
bool MainMapScene::moveCall = false;

void moveSingleSpaceTest()
{
	MainMapScene::triggerMove();
}

void MainMapScene::onNewScene()
{
	test();
}

void MainMapScene::test()
{
	m_MapToLoad = "SydeCoast";
	setUpMap();
	//cameraPos = Vector2(20, 50);
	m_UIControl.push_back(new SYDEClickableButton(
		"Test Move",
		Vector2(3, 19),
		Vector2(9, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		moveSingleSpaceTest
	));

}

void MainMapScene::setUpMap()
{
	string IslandBmp = "EngineFiles\\Levels\\Map\\" + m_MapToLoad + ".bmp";
	string IslandPathData = "EngineFiles\\Levels\\PathData\\" + m_MapToLoad + ".bmp";
	wstring wIslandBmp = wstring(IslandBmp.begin(), IslandBmp.end());
	wstring wIslandPathData = wstring(IslandPathData.begin(), IslandPathData.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_MapBg = CustomAsset(200, 100, AssetsClass::get_bmp_as_direct_colour_class_array((WCHAR*)wIslandBmp.c_str(), 100, 100));
	m_CfgObj = MapConfigObject("EngineFiles\\Levels\\Configs\\" + m_MapToLoad + ".sc");
	Bitmap* SpawnData = new Bitmap((WCHAR*)wIslandPathData.c_str(), FALSE);
	for (int i = 0; i < 100; i++)
	{
		for (int ii = 0; ii < 100; ii++)
		{
			Gdiplus::Color* pixelColor = new Gdiplus::Color();
			SpawnData->GetPixel(ii + 1, i, pixelColor);
			int spawnType = pixelColor->GetRed();
			switch (spawnType)
			{
			case 200:
			case 105:
			case 28:
				addSpace(Vector2(ii * 2, i), *pixelColor);
				break;
			default:
				break;
			}
			delete[] pixelColor;
		}
	}
	delete[] SpawnData;
	sortSpaces();
}

void MainMapScene::sortSpaces()
{
	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		m_MapPaths[i].orderSpaceArray();
	}

	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		for (int ii = 0; ii < m_MapPaths[i].getSize(); ii++)
		{
			//TODO: DETERMINE COLOUR BASED OFF BOARD PIECE
			Vector2 loc = m_MapPaths[i].getElement(ii).getDrawPos();
			m_MapBg.setCharAtPoint(loc, '[');
			m_MapBg.setColourAtPoint(loc, BRIGHTWHITE);
			loc.addX(1);
			m_MapBg.setCharAtPoint(loc, ']');
			m_MapBg.setColourAtPoint(loc, BRIGHTWHITE);
		}
	}
	cameraPos = getSpace(0, 0).getDrawPos();
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
	if (!addSpaceToExistingPath(pix.GetGreen(), pix.GetBlue(), location, "",pix.GetRed()))
	{
		m_MapPaths.push_back(MapPath(pix.GetGreen()));
		addSpaceToExistingPath(pix.GetGreen(), pix.GetBlue(), location, "", pix.GetRed());
	}
}

bool MainMapScene::addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data, int pathType)
{
	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		if (path == m_MapPaths[i].getID())
		{
			m_MapPaths[i].addSpace(MapSpace(data, getPixRedToType(pathType), path, space, pos));
			return true;
		}
	}
	return false;
}

MapSpace MainMapScene::getSpace(int path, int space)
{
	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		if (path == m_MapPaths[i].getID())
		{
			return m_MapPaths[i].getElement(space);
		}
	}
	return MapSpace();
}

MapSpaceTypes MainMapScene::getPixRedToType(int red)
{
	if (red == 200)
	{
		return MST_SwitchPathsSpace;
	}
	return MST_NormalSpace;
}

ConsoleWindow MainMapScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (moveCall)
	{
		//TODO:
		//DETERMINE DICE ROLL
		//RUN LOOP FOR EACH SPACE TO MOVE
		//ON SOME SQUARES THEY CAN ONLY BE ACTIVE WHEN SPACES = 0
		moveCall = false;
		m_Space.addY(1);
		MapSpace spaceCurrent = getSpace(m_Space.getX(), m_Space.getY());
		cameraPos = spaceCurrent.getDrawPos();
		if (spaceCurrent.getType() == MST_SwitchPathsSpace)
		{
			//TODO: SHOW A POP UP ASKING WHICH ROUTE WANTED TO BE TAKEN
			window = window;
		}
	}

	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLUE_BLUE_BG);
		}
	}
	window = m_MapBg.draw_asset(window, Vector2(cameraPos.getX() - (windowWidth/2), cameraPos.getY() - (windowHeight/2)), windowWidth, windowHeight);
	window.setTextAtPoint(Vector2((windowWidth / 2), (windowHeight / 2)), "><", window.determineColourAtPoint(Vector2((windowWidth / 2), (windowHeight / 2)), BRIGHTWHITE, true));
	for (int i = 0; i < m_UIControl.size(); i++)
	{
		window = m_UIControl[i]->draw_ui(window);
	}
	return window;
}