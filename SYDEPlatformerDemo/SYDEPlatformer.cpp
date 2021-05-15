#include "SYDEPlatformer.h"
AssetsClass SYDEPlatformer::astVars = AssetsClass();

void SYDEPlatformer::init()
{
	m_Levels = SYDEFileDefaults::getAllFileNamesInFolder("EngineFiles\\Bitmaps\\Map", ".bmp",true);
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
	window = m_MainMap.draw_asset(window, Vector2(PlayerPos.getX() - 20, PlayerPos.getY() - 10), windowWidth, windowHeight);
	window.setTextAtPoint(Vector2(20, 10), "*", window.determineColourAtPoint(Vector2(20, 10), BRIGHTWHITE, true));
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
	if (momentumTime > 0.05f)
	{
		ApplyMomentum();
		momentumTime -= 0.05f;
	}
	momentumTime += SYDEDefaults::getDeltaTime();
	//DEBUG
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		PlayerPos = Vector2(994*2, 389);
	}
	if (SYDEKeyCode::get_key(VK_ESCAPE)._CompareState(KEYDOWN))
	{
		m_State = LevelSelect_STATE;
	}

	if (SYDEKeyCode::get_key('W')._CompareState(KEYDOWN) && (checkGrounded() || m_Momentum.getY() == 1))
	{
		m_Momentum = (Vector2(0, -3));
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
		winMap();
		return window;
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
	window.setTextAtPoint(Vector2(0, 1), "SYDE PLATFORMER", BRIGHTWHITE);

	window.setTextAtPoint(Vector2(3, 9), "CONTROLS", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(3, 10), "WASD - Move/Chane Map Selection", BRIGHTWHITE);
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
	}
	else if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		SelectedLevel--;
		if (SelectedLevel < 0)
		{
			SelectedLevel = m_Levels.size() -1;
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_State = MainLevel_STATE;
		string bmpFile = "EngineFiles\\Bitmaps\\Map\\" + m_Levels[SelectedLevel];
		wstring wbmpFile = wstring(bmpFile.begin(), bmpFile.end());
		SYDEBMPDimensions fileSize = SYDEFileDefaults::getBMPDimensions(bmpFile);
		m_MainMap = CustomAsset(fileSize.width * 2, fileSize.height, astVars.get_bmp_as_direct_colour_class_array((WCHAR*)wbmpFile.c_str(), fileSize.width, fileSize.height));
		CheckPoint = m_MainMap.returnPointOfFirstInstance(LIGHTGREY_LIGHTGREY_BG);
		PlayerPos = CheckPoint;
		gameTime = 0.0f;
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
