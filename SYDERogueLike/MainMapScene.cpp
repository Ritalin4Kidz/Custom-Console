#include "MainMapScene.h"
bool MainMapScene::moveCall = false;
bool MainMapScene::choiceCall = false;
bool MainMapScene::optionsCall = false;
bool MainMapScene::nukeCall = false;
bool MainMapScene::tickCall = false;
Vector2 MainMapScene::m_SpaceMoveTo = Vector2(0, 0);
void moveSingleSpaceTest()
{
	MainMapScene::triggerMove();
}

void TickFunc()
{
	MainMapScene::triggerTick();
}

void options()
{
	/*
	TODO: OPTIONS MENU TO QUIT TO MENU, RESUME OR EXIT GAME
		OTHER SETTINGS LATER
	*/
	MainMapScene::triggerOptions();
}

void playerStats()
{
	/*
	PLAYER STATS STATE
		SEE CURRENT MOVES + STATS + HEALTH
	*/
	SydeRogueLikeStatics::setSceneTag("Player State Scene");
}

void mainMenu()
{
	SydeRogueLikeStatics::setSceneTag("Main Splashscreen");
	MainMapScene::triggerNuke();
	GameScene::ShowUI();
}

void choosePath()
{
	MainMapScene::setSpaceMoveTo(SYDEMathUtils::VectorFromString(CustomAsset_Clickable::getLastButtonTag()));
	MainMapScene::triggerChoice();
}

void MainMapScene::onNewScene()
{
	test();

	setUpMap();
	showRouteOptions = false;
	m_SceneState = MMS_Normal;
	m_MovementState = MoveState_STANDING;
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"OP",
		Vector2(3, 1),
		Vector2(2, 1),
		BLACK_WHITE_BG,
		NULLCOLOUR,
		false,
		options
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"PS",
		Vector2(6, 1),
		Vector2(2, 1),
		BLACK_WHITE_BG,
		NULLCOLOUR,
		false,
		playerStats
	)));

	m_OptionsMenu = std::vector<std::shared_ptr<SYDEClickableButton>>({});
	m_OptionsMenu.push_back(std::shared_ptr<SYDEClickableButton>(new SYDEClickableButton(
		"     Resume Game     ",
		Vector2(20, 5),
		Vector2(20, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		options)));

	m_OptionsMenu.push_back(std::shared_ptr<SYDEClickableButton>(new SYDEClickableButton(
			"     Back To Menu     ",
			Vector2(20, 15),
			Vector2(20, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			mainMenu))
		);

	if (SydeRogueLikeStatics::getBattleTag() == "Boss Defeated")
	{
		doBossDefeatedAction();

	}
	SydeRogueLikeStatics::setBattleTag("");

}

void MainMapScene::destroyScene()
{
	m_OptionsMenu.clear();

	if (nukeCall)
	{
		nukeCall = false;
		nukeMap();
	}
}

void MainMapScene::test()
{
	//m_MapToLoad = "SydeCoast";
	//cameraPos = Vector2(20, 50);
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Test Move",
		Vector2(3, 19),
		Vector2(9, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		moveSingleSpaceTest
	)));

}

void MainMapScene::setUpMap()
{
	if (!SydeRogueLikeStatics::getInitMap())
	{
		return;
	}
	nukeMap();
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
			case 201:
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
	m_Space = Vector2(0, 0);
	SydeRogueLikeStatics::toggleInitMap(false);
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
				case MST_ForceSwitchPathsSpace:
					m_BoardColour = NULLCOLOUR;
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
			if (m_BoardColour != NULLCOLOUR)
			{
				Vector2 loc = m_MapPaths[i].getElement(ii).getDrawPos();
				m_MapBg.setCharAtPoint(loc, ' ');
				m_MapBg.setColourAtPoint(loc, m_BoardColour);
				loc.addX(1);
				m_MapBg.setCharAtPoint(loc, ' ');
				m_MapBg.setColourAtPoint(loc, m_BoardColour);
			}
		}
	}
	cameraPos = getSpace(0, 0).getDrawPos();
}

void MainMapScene::nukeMap()
{
	m_MapPaths.clear();
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
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\FightInitAnimation.bmp", 300, 100, 30, 20, 0, 50));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "Battle Scene";
	//HideUI();
	//TODO:
	/*
	WE NEED TO GENERATE THE BATTLE HERE
	THIS IS NOT FOR BOSS FIGHTS, WHICH WILL HAVE AN ENTIRELY DIFFERENT START ANIMATION REGARDLESS
	*/
	generateEnemy(getSpace(m_Space.getX(), m_Space.getY()));
}

void MainMapScene::loadShopScene()
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\ShoppingAnimation.bmp", 150, 160, 30, 20, 0, 40));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "Shop Scene";
	HideUI();
}

void MainMapScene::rollDice()
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\D20Anim\\DiceAnimation002.bmp", 90, 180, 30, 20, 0, 25));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "DiceRollingAnim";
	HideUI();
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

void MainMapScene::setUpEndMapUI()
{
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"     Back To Menu     ",
		Vector2(20, 15),
		Vector2(20, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		mainMenu)));
}

void MainMapScene::refreshStepsUI(int width, int height)
{
	DiceDisplay diceRoll = MainMapScene::returnSteps(spacesToMove, width, height);
	m_StepsAmountAsset = diceRoll.spaces;
	m_StepsAmountAsset_Pos = diceRoll.vec;
	stepTimer = 0.0f;
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

bool MainMapScene::isLastSpace(int path, int space)
{
	for (int i = 0; i < m_MapPaths.size(); i++)
	{
		if (path == m_MapPaths[i].getID())
		{
			return m_MapPaths[i].getSize() - 1 == space;
		}
	}
	return false;
}

MapSpaceTypes MainMapScene::getPixRedToType(int red)
{
	if (red == 200)
	{
		return MST_SwitchPathsSpace;
	}
	if (red == 201)
	{
		return MST_ForceSwitchPathsSpace;
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

DiceDisplay MainMapScene::returnSteps(int steps, int middleWidth, int middleHeight)
{
	string numberBmp = "EngineFiles\\Bitmaps\\Numbers\\" + to_string(steps) + ".bmp";
	wstring wNumberBmp = wstring(numberBmp.begin(), numberBmp.end());

	return DiceDisplay(CustomAsset(10,5,AssetsClass::get_bmp_as_array((WCHAR*)wNumberBmp.c_str(), 5, 5)), Vector2(middleWidth- 4, middleHeight - 6));
}

void MainMapScene::doBossAction(MapSpace currentSpace)
{
}

void MainMapScene::doBossDefeatedAction()
{
}

void MainMapScene::generateEnemy(MapSpace currentSpace)
{
}

ConsoleWindow MainMapScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (tickCall)
	{
		if (m_GameOverFireworks.isDead())
		{
			float _x = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40 - 0)));
			float _y = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (19 - 0)));
			m_GameOverFireworks.setPos(Vector2(_x, _y));
			m_GameOverFireworks.burst();
		}
		tickCall = false;
	}
	if (optionsCall)
	{
		optionsCall = false;
		if (m_SceneState == MMS_Normal)
		{
			m_SceneState = MMS_Options;
			GameScene::HideUI();
		}
		else if (m_SceneState == MMS_Options)
		{
			m_SceneState = MMS_Normal;
			GameScene::ShowUI();
		}
		return window;
	}
	if (moveCall)
	{
		moveCall = false;
		if (!showRouteOptions)
		{
			rollDice();
		}
		return window;
	}
	if (m_MovementState == MoveState_ROLLING)
	{
		//TODO:
		//DETERMINE DICE ROLL
		//RUN LOOP FOR EACH SPACE TO MOVE
		//ON SOME SQUARES THEY CAN ONLY BE ACTIVE WHEN SPACES = 0
		if (m_SceneState == MMS_Normal)
		{
			m_MovementState = MoveState_MOVEMENT;
			spacesToMove = (rand() % SydeRogueLikeStatics::getPlayer()->getRollSize()) + SydeRogueLikeStatics::getPlayer()->getMinRoll();
			refreshStepsUI(windowWidth / 2, windowHeight / 2);

		}
	}
	else if (m_MovementState == MoveState_CHECKING)
	{
		m_MovementState = MoveState_STANDING;
		MapSpace spaceCurrent = getSpace(m_Space.getX(), m_Space.getY());
		if (spaceCurrent.getType() == MST_BattleSpace)
		{
			//TODO: ANIMATION FOR LOADING INTO BATTLE
			HideUI();
			loadBasicBattleScene();
			return window;
		}
		else if (spaceCurrent.getType() == MST_ShopSpace)
		{
			//TODO: ANIMATION FOR LOADING INTO BATTLE
			HideUI();
			loadShopScene();
			return window;
		}
		else if (spaceCurrent.getType() == MST_BossBattleSpace)
		{
			//TODO: ANIMATION FOR LOADING INTO BATTLE
			HideUI();
			doBossAction(spaceCurrent);
			return window;
		}
		else
		{
			ShowUI();
			return window;
		}
	}
	else if (m_MovementState == MoveState_MOVEMENT && !showRouteOptions)
	{
		MapSpace spaceCurrent = getSpace(m_Space.getX(), m_Space.getY());
		cameraPos = spaceCurrent.getDrawPos();
		if (spaceCurrent.getType() != MST_SwitchPathsSpace && spaceCurrent.getType() != MST_ForceSwitchPathsSpace)
		{
			if (isLastSpace(m_Space.getX(), m_Space.getY()))
			{
				spacesToMove = 0;
			}
			if (spacesToMove > 0)
			{
				stepTimer += SYDEDefaults::getDeltaTime();
				if (stepTimer >= timeBetweenSteps)
				{
					spacesToMove--;
					m_Space.addY(1);
					refreshStepsUI(windowWidth / 2, windowHeight / 2);
				}
			}
			else if (spacesToMove == 0)
			{
				m_MovementState = MoveState_CHECKING;
			}
		}
		else if (spaceCurrent.getType() == MST_ForceSwitchPathsSpace)
		{
			m_Space = m_CfgObj.getForcedPathNumberToMoveAtPos(spaceCurrent.getPathNumber(), spaceCurrent.getSpaceNumber());
			return window;
		}
		else if (spaceCurrent.getType() == MST_SwitchPathsSpace)
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
	}

	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLUE_BLUE_BG);
		}
	}
	window = m_MapBg.draw_asset(window, Vector2(cameraPos.getX() - (windowWidth / 2), cameraPos.getY() - (windowHeight / 2)), windowWidth, windowHeight);
	window.setTextAtPoint(Vector2((windowWidth / 2), (windowHeight / 2)), "><", window.determineColourAtPoint(Vector2((windowWidth / 2), (windowHeight / 2)), BRIGHTWHITE, true));

	if (m_MovementState == MoveState_MOVEMENT && !showRouteOptions)
	{
		window = m_StepsAmountAsset.draw_asset(window, m_StepsAmountAsset_Pos);
	}

	if (m_SceneState == MMS_Normal)
	{
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
	}
	else if (m_SceneState == MMS_Options)
	{
		for (int i = 0; i < m_OptionsMenu.size(); i++)
		{
			window = m_OptionsMenu[i]->draw_ui(window);
		}
	}
	else if (m_SceneState == MMS_END)
	{
		m_GameOverFireworks.draw(window);
		m_FireworksTimer.Tick();
	}
	else if (m_SceneState == MMS_UIAnimation || m_SceneState == MMS_END_UIAnimation)
	{
		window = m_UIAnimation.draw_asset(window, Vector2(0, 1));
		if (m_UIAnimation.getFrame() >= m_UIAnimation.getFrameSize() - 1)
		{
			if (m_SceneState == MMS_END_UIAnimation)
			{
				//SHOW FIREWORKS
				m_MovementState = MoveState_END;
				m_SceneState = MMS_END;
				//TODO: FIREWORKS + OPTION TO EXIT TO MENU
				m_GameOverFireworks.setColour(YELLOW);
				m_GameOverFireworks.setCharacter("*");
				m_GameOverFireworks.RainbowOn(true);
				m_GameOverFireworks.setMaxParticles(35);
				m_GameOverFireworks.setFinishingColour(WHITE);
				m_FireworksTimer.SetFunc(TickFunc);
				clearUI();
				setUpEndMapUI();
				ShowUI();
			}
			else
			{
				//CHEAT SHEET
				if (sceneLoad == "DiceRollingAnim")
				{
					HideUI();
					m_MovementState = MoveState_ROLLING;
					m_SceneState = MMS_Normal;
				}
				else if (sceneLoad != "")
				{
					SydeRogueLikeStatics::setSceneTag(sceneLoad);
					ShowUI();
				}
				else
				{
					m_SceneState = MMS_Normal;
					ShowUI();
				}
			}
		}
		return window;
	}
	return window;
}