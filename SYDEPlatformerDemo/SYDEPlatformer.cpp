#include "SYDEPlatformer.h"
AssetsClass SYDEPlatformer::astVars = AssetsClass();

void SYDEPlatformer::init()
{
}

ConsoleWindow SYDEPlatformer::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
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
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEY) && checkGrounded())
	{
		PlayerPos = Vector2(855*2, 150);
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
	if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
	{
		CheckPoint = PlayerPos;
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


void SYDEPlatformer::AddPositionX(Vector2 add)
{
	if (m_MainMap.getColourAtPoint(PlayerPos + add) != BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		PlayerPos += add;
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
