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
	if (momentumTime > 0.05f)
	{
		ApplyMomentum();
		momentumTime -= 0.05f;
	}
	momentumTime += SYDEDefaults::getDeltaTime();
	//DEBUG
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		PlayerPos = Vector2(22*2, 155);
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
		//START
		PlayerPos = CheckPoint;
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
	window.setTextAtPoint(Vector2(0, 1), "SYDE PLATFORMER", BRIGHTWHITE);
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
		m_MainMap = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array((WCHAR*)wbmpFile.c_str(), 1000, 1000));
	}
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
	}
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
			}
			else
			{
				momY = 0;
			}
		}
	}
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
