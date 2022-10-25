#include "SYDEPlatformer.h"
AssetsClass SYDEPlatformer::astVars = AssetsClass();

void SYDEPlatformer::init()
{
	m_Levels = SYDEFileDefaults::getAllFileNamesInFolder("EngineFiles\\Bitmaps\\Map", ".bmp",true);
	changePreviewMap();
}

ConsoleWindow SYDEPlatformer::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	switch (m_State)
	{
	case MainLevel_STATE:
		return draw_game(window, windowWidth, windowHeight);
	case MainMenu_STATE:
		return draw_title(window, windowWidth, windowHeight);
	case LevelSelect_STATE:
		return draw_levelSelect(window, windowWidth, windowHeight);
	case Win_STATE:
		return draw_WinState(window, windowWidth, windowHeight);
	}
	return draw_title(window, windowWidth, windowHeight);
}

ConsoleWindow SYDEPlatformer::draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}

	bool inGravityFreeArea = (m_MainMap.getColourAtPoint(PlayerPos) == BRIGHTGREEN_BRIGHTGREEN_BG);

	window = m_MainMap.draw_asset(window, Vector2(PlayerPos.getX() - (windowWidth/2), PlayerPos.getY() - (windowHeight/2)), windowWidth, windowHeight);
	window.setTextAtPoint(Vector2((windowWidth / 2), (windowHeight/2)), "*", window.determineColourAtPoint(Vector2((windowWidth / 2), (windowHeight / 2)), BRIGHTWHITE, true));
	if (dead)
	{
		deadTime+= SYDEDefaults::getDeltaTime();
		if (deadTime >= 0.5f)
		{
			dead = false;
			//START
			PlayerPos = CheckPoint;
			deadTime = 0;
		}
		return window;
	}

	gameTime += SYDEDefaults::getDeltaTime();
	if (!inGravityFreeArea)
	{
		if (momentumTime > 0.05f)
		{
			ApplyMomentum();
			momentumTime -= 0.05f;
		}
		momentumTime += SYDEDefaults::getDeltaTime();
	}
	//DEBUG
	if (SYDEKeyCode::get_key('E')._CompareState(KEYDOWN))
	{
		PlayerPos = cheatPos;
	}
	if (SYDEKeyCode::get_key('Q')._CompareState(KEYDOWN))
	{
		cheatPos = PlayerPos;
	}
	if (SYDEKeyCode::get_key('T')._CompareState(KEY))
	{
		window.setTextAtPoint(Vector2(0, 1), timeStringConvert(), BRIGHTGREEN);
	}
	if (coinsOnMap > 0)
	{
		coinCounter.setText("Coins Collected: " + to_string(coinsCollected) + "/" + to_string(coinsOnMap));
		window = coinCounter.draw_ui(window);
	}
	if (SYDEKeyCode::get_key(VK_ESCAPE)._CompareState(KEYDOWN))
	{
		m_State = LevelSelect_STATE;
	}

	if (SYDEKeyCode::get_key('W')._CompareState(KEYDOWN) && (checkGrounded() || m_Momentum.getY() == 1) && !inGravityFreeArea)
	{
		m_Momentum = (Vector2(0, -3));
	}

	if (inGravityFreeArea)
	{
		if (SYDEKeyCode::get_key('S')._CompareState(KEY))
		{
			if (movementTimeVertical > 0.1f)
			{
				AddPositionX(Vector2(0, 1));
				movementTimeVertical -= 0.1f;
			}
			movementTimeVertical += SYDEDefaults::getDeltaTime();
		}
		else if (SYDEKeyCode::get_key('W')._CompareState(KEY))
		{
			if (movementTimeVertical > 0.1f)
			{
				AddPositionX(Vector2(0, -1));
				movementTimeVertical -= 0.1f;
			}
			movementTimeVertical += SYDEDefaults::getDeltaTime();
		}
		else
		{
			movementTimeVertical = 0.1f;
		}
	}


	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		if (movementTime > 0.05f)
		{
			AddPositionX(Vector2(1, 0));
			movementTime -= 0.05f;
		}
		movementTime += SYDEDefaults::getDeltaTime();
	}
	else if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		if (movementTime > 0.05f)
		{
			AddPositionX(Vector2(-1, 0));
			movementTime -= 0.05f;
		}
		movementTime += SYDEDefaults::getDeltaTime();
	}
	else
	{
		movementTime = 0.05f;
	}

	if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
	{
		dead = true;
		return window;
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
	{
		CheckPoint = PlayerPos;
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == AQUA_AQUA_BG)
	{
		bool canWin = true;
		if (coinsOnMap > 0)
		{
			if (coinsCollected < coinsOnMap)
			{
				canWin = false;
			}
		}
		if (canWin)
		{
			winMap();
			return window;
		}
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == BRIGHTYELLOW && m_MainMap.getCharAtPoint(PlayerPos) == 'O')
	{
		m_MainMap.setCharAtPoint(PlayerPos,' ');
		m_MainMap.setColourAtPoint(PlayerPos, BLACK);
		coinsCollected++;
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == YELLOW_YELLOW_BG)
	{
		AddPositionX(Vector2(-5, 0));
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == PURPLE_PURPLE_BG)
	{
		AddPositionX(Vector2(5, 0));
	}
	if (m_MainMap.getColourAtPoint(PlayerPos) == GREEN_GREEN_BG)
	{
		m_Momentum = (Vector2(0, -5));
	}

	return window;
}
ConsoleWindow SYDEPlatformer::draw_title(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_State = LevelSelect_STATE;
	}
	if (SYDEKeyCode::get_key(VK_ESCAPE)._CompareState(KEYDOWN))
	{
		exit(NULL);
	}
	window.setTextAtPoint(Vector2(0, 1), "ASTERIX MAN", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 2), "v1.0.0.0-Prerelease", BRIGHTWHITE);

	window.setTextAtPoint(Vector2(3, 9), "CONTROLS", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 10), "WASD - Move/Change Map Selection", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 11), "ESC - Quit", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 12), "Space - Start/Select", BRIGHTWHITE);

	return window;
}
ConsoleWindow SYDEPlatformer::draw_levelSelect(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "SELECT LEVEL", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 5), m_Levels[SelectedLevel], BRIGHTWHITE);
	window = m_MapPreview.draw_asset(window, Vector2(0, 7));
	if (SYDEKeyCode::get_key(VK_ESCAPE)._CompareState(KEYDOWN))
	{
		m_State = MainMenu_STATE;
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		SelectedLevel++;
		if (SelectedLevel >= m_Levels.size())
		{
			SelectedLevel = 0;
		}
		changePreviewMap();
	}
	else if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		SelectedLevel--;
		if (SelectedLevel < 0)
		{
			SelectedLevel = m_Levels.size() -1;
		}
		changePreviewMap();
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_State = MainLevel_STATE;
		string bmpFile = "EngineFiles\\Bitmaps\\Map\\" + m_Levels[SelectedLevel];
		wstring wbmpFile = wstring(bmpFile.begin(), bmpFile.end());
		SYDEBMPDimensions fileSize = SYDEFileDefaults::getBMPDimensions(bmpFile);
		m_MainMap = CustomAsset(fileSize.width * 2, fileSize.height, astVars.get_bmp_as_array((WCHAR*)wbmpFile.c_str(), fileSize.width, fileSize.height));
		CheckPoint = m_MainMap.returnPointOfFirstInstance(LIGHTGREY_LIGHTGREY_BG);
		PlayerPos = CheckPoint;
		gameTime = 0.0f;
		sortOutCoins();
	}
	return window;
}
ConsoleWindow SYDEPlatformer::draw_WinState(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_State = LevelSelect_STATE;
	}
	window.setTextAtPoint(Vector2(0, 1), "CONGRATS", BRIGHTWHITE);

	window.setTextAtPoint(Vector2(3, 9), "LEVEL BEATEN", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 10), "Time Taken: " + timeString, BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 11), "Press Space To Return To Menu", BRIGHTWHITE);
	return window;
}
void SYDEPlatformer::changePreviewMap()
{
	string bmpFile = "EngineFiles\\Bitmaps\\Preview\\" + m_Levels[SelectedLevel];
	if (SYDEFileDefaults::exists(bmpFile.c_str()))
	{
		wstring wbmpFile = wstring(bmpFile.begin(), bmpFile.end());
		m_MapPreview = CustomAsset(50, 15, astVars.get_bmp_as_direct_colour_class_array((WCHAR*)wbmpFile.c_str(), 25, 15));
	}
	else
	{
		m_MapPreview = CustomAsset(50, 15, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Preview\\DefaultPreview.bmp", 25, 15));
	}
}
void SYDEPlatformer::sortOutCoins()
{
	coinsCollected = 0;
	coinsOnMap = m_MainMap.changeAllInstancesOfColour(BRIGHTYELLOW_BRIGHTYELLOW_BG, BRIGHTYELLOW, 'O');
}
void SYDEPlatformer::AddPositionX(Vector2 add)
{
	if (m_MainMap.getColourAtPoint(PlayerPos + add) != BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		PlayerPos += add;
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			CheckPoint = PlayerPos;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			dead = true;
			return;
		}
	}
}
void SYDEPlatformer::winMap()
{
	m_State = Win_STATE;
	m_hours = 0;
	m_minutes = 0;
	while (gameTime >= 60)
	{
		m_minutes++;
		gameTime -= 60;
		if (m_minutes == 60)
		{
			m_hours++;
			m_minutes = 0;
		}
	}
	timeString = timeStringConvert();
}
void SYDEPlatformer::ApplyMomentum()
{
	if (checkGrounded() && m_Momentum.getY() > 0)
	{
		m_Momentum.setY(0);
		return;
	}
	else
	{
		m_Momentum.addY(0.5f);
	}
	int momY = m_Momentum.getY();
	if (momY < 0)
	{
		while (momY != 0)
		{
			if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0,-1)) != BRIGHTWHITE_BRIGHTWHITE_BG)
			{
				PlayerPos += Vector2(0, -1);
				momY += 1;
				if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
				{
					CheckPoint = PlayerPos;
				}
				if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
				{
					dead = true;
					return;
				}
				if (m_MainMap.getColourAtPoint(PlayerPos) == BRIGHTYELLOW && m_MainMap.getCharAtPoint(PlayerPos) == 'O')
				{
					m_MainMap.setCharAtPoint(PlayerPos, ' ');
					m_MainMap.setColourAtPoint(PlayerPos, BLACK);
					coinsCollected++;
				}
			}
			else
			{
				momY = 0;
			}
		}
	}
	else
	{
		while (momY != 0)
		{
			if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, 1)) != BRIGHTWHITE_BRIGHTWHITE_BG)
			{
				PlayerPos += Vector2(0, 1);
				momY -= 1;
				if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
				{
					CheckPoint = PlayerPos;
				}
				if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
				{
					dead = true;
					return;
				}
				if (m_MainMap.getColourAtPoint(PlayerPos) == BRIGHTYELLOW && m_MainMap.getCharAtPoint(PlayerPos) == 'O')
				{
					m_MainMap.setCharAtPoint(PlayerPos, ' ');
					m_MainMap.setColourAtPoint(PlayerPos, BLACK);
					coinsCollected++;
				}
			}
			else
			{
				momY = 0;
			}
		}
	}
}
std::string SYDEPlatformer::timeStringConvert()
{
	std::string temp = "";
	if (m_hours > 0)
	{
		temp += to_string(m_hours) + "h " + to_string(m_minutes) + "m ";
	}
	else if (m_minutes > 0)
	{
		temp += to_string(m_minutes) + "m ";
	}
	temp += std::to_string(gameTime) + "s";
	return temp;
}
bool SYDEPlatformer::checkGrounded()
{
	if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, 1)) == BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return true;
	}
}
bool SYDEPlatformer::checkGrounded(ConsoleWindow window)
{
	if (window.getTextColourAtPoint(Vector2(20,11)) == BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return true;
	}
}
