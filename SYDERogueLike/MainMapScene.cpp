#include "MainMapScene.h"
std::string MainMapScene::m_MapToLoad = "";
bool MainMapScene::moveCall = false;
bool MainMapScene::choiceCall = false;
Vector2 MainMapScene::m_SpaceMoveTo = Vector2(0, 0);
void moveSingleSpaceTest()
{
	MainMapScene::triggerMove();
}

void choosePath()
{
	MainMapScene::setSpaceMoveTo(SYDEMathUtils::VectorFromString(CustomAsset_Clickable::getLastButtonTag()));
	MainMapScene::triggerChoice();
}

void MainMapScene::onNewScene()
{
	test();
	showRouteOptions = false;
}

void MainMapScene::destroyScene()
{
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
			ColourClass m_BoardColour = NULLCOLOUR;
			switch (m_MapPaths[i].getElement(ii).getType())
			{
				case MST_SwitchPathsSpace:
					m_BoardColour = BRIGHTWHITE;
					break;
				case MST_BossBattleSpace:
					m_BoardColour = YELLOW_YELLOW_BG;
					break;
				case MST_BattleSpace:
					m_BoardColour = RED_RED_BG;
					break;
				case MST_ShopSpace:
					m_BoardColour = PURPLE_PURPLE_BG;
					break;
				default:
					m_BoardColour = BLUE_BLUE_BG;
					break;
			}
			Vector2 loc = m_MapPaths[i].getElement(ii).getDrawPos();
			m_MapBg.setCharAtPoint(loc, ' ');
			m_MapBg.setColourAtPoint(loc, m_BoardColour);
			loc.addX(1);
			m_MapBg.setCharAtPoint(loc, ' ');
			m_MapBg.setColourAtPoint(loc, m_BoardColour);
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

void MainMapScene::loadBasicBattleScene()
{
	//TODO, WE NEED TO SET UP THE ENEMY HERE
	//GRAB THE POOL FROM MAP CONFIGS OR SOMETHING
	SydeRogueLikeStatics::setSceneTag("Battle Scene");
}

bool MainMapScene::addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data, int pathType)
{
	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		if (path == m_MapPaths[i].getID())
		{
			if (path == 0 && space == 0)
			{
				//START VALUE MUST ALWAYS BE NORMAL
				m_MapPaths[i].addSpace(MapSpace(data, MST_NormalSpace, path, space, pos));
				return true;
			}
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
	if (red == 28)
	{
		return MST_BossBattleSpace;
	}

	//POOLS
	if (red == 105)
	{
		int space = rand() % 100;
		if (space < 50)
		{
			return MST_NormalSpace;
		}
		if (space < 90)
		{
			return MST_BattleSpace;
		}
		else
		{
			return MST_ShopSpace;
		}
	}

	return MST_NormalSpace;
}

ArrowDisplay MainMapScene::returnArrowForPath(Vector2 nextPathPos, Vector2 currentPos, void(*f)(), string a_Tag, int middleWidth, int middleHeight)
{
	if (nextPathPos.getY() < currentPos.getY())
	{
		if (nextPathPos.getX() > currentPos.getX())
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_UpRight.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth, middleHeight - 6));
		}
		else if (nextPathPos.getX() < currentPos.getX())
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_UpLeft.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth -16, middleHeight - 6));
		}
		else
		{
			return ArrowDisplay(CustomAsset_Clickable(
				12,
				8,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_Up.bmp", 6, 8),
				f,
				a_Tag), Vector2(middleWidth - 6, middleHeight - 8));
		}
	}
	else if (nextPathPos.getY() > currentPos.getY())
	{
		if (nextPathPos.getX() > currentPos.getX())
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_DownRight.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth, middleHeight));
		}
		else if (nextPathPos.getX() < currentPos.getX())
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_DownLeft.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth - 16, middleHeight));
		}
		else
		{
			return ArrowDisplay(CustomAsset_Clickable(
				12,
				8,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_Down.bmp", 6, 8),
				f,
				a_Tag), Vector2(middleWidth - 6, middleHeight + 1));
		}
	}
	else
	{
		if (nextPathPos.getX() > currentPos.getX())
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_Right.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth, middleHeight - 2));
		}
		else
		{
			return ArrowDisplay(CustomAsset_Clickable(
				16,
				6,
				AssetsClass::get_bmp_as_array(L"EngineFiles\\Bitmaps\\Arrows\\Arrow_Left.bmp", 8, 6),
				f,
				a_Tag), Vector2(middleWidth - 16, middleHeight - 2));
		}
	}
	return ArrowDisplay(CustomAsset_Clickable(), Vector2());
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
			//TODO: SHOW A POP UP OF ARROWS ASKING WHICH ROUTE WANTED TO BE TAKEN
			showRouteOptions = true;
			//DETERMINE WHICH BUTTONS TO SHOW
			//SWAP BTN
			int nextPath = m_CfgObj.getPathNumberToMoveAtPos(spaceCurrent.getPathNumber(), spaceCurrent.getSpaceNumber());
			Vector2 nextPathPos = getSpace(nextPath, 0).getDrawPos();
			ArrowDisplay aNext = MainMapScene::returnArrowForPath(nextPathPos, cameraPos, 
				choosePath, SYDEMathUtils::VectorToString(Vector2(nextPath, 0)), (windowWidth / 2), (windowHeight / 2));
			m_SwapPathBtn = aNext.click;
			swapBtnPos = aNext.vec;
			ArrowDisplay aCont = MainMapScene::returnArrowForPath(getSpace(m_Space.getX(), m_Space.getY() + 1).getDrawPos(), cameraPos,
				choosePath, SYDEMathUtils::VectorToString(Vector2(spaceCurrent.getPathNumber(), spaceCurrent.getSpaceNumber() + 1)), (windowWidth / 2), (windowHeight / 2));
			m_ContinuePathBtn = aCont.click;
			contBtnPos = aCont.vec;
			return window;
		}
		else if (spaceCurrent.getType() == MST_BattleSpace)
		{
			//TODO: ANIMATION FOR LOADING INTO BATTLE
			loadBasicBattleScene();
			return window;
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
	if (showRouteOptions)
	{
		if (choiceCall)
		{
			choiceCall = false;
			showRouteOptions = false;
			//DO OPTION
			m_Space = m_SpaceMoveTo;
			MapSpace spaceCurrent = getSpace(m_Space.getX(), m_Space.getY());
			cameraPos = spaceCurrent.getDrawPos();
			return window;
		}
		window = m_SwapPathBtn.draw_asset(window, swapBtnPos);
		window = m_ContinuePathBtn.draw_asset(window, contBtnPos);
		return window;
	}
	for (int i = 0; i < m_UIControl.size(); i++)
	{
		window = m_UIControl[i]->draw_ui(window);
	}
	return window;
}