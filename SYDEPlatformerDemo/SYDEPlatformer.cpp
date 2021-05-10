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
			window.setTextAtPoint(Vector2(l, m), " ", RED_RED_BG);
		}
	}
	window = m_MainMap.draw_asset(window, Vector2(PlayerPos.getX() - 20, PlayerPos.getY() - 10), windowWidth, windowHeight);

	window.setTextAtPoint(Vector2(20, 10), "*", window.determineColourAtPoint(Vector2(20, 10), BRIGHTWHITE, true));
	if (momentumTime > 0.05f)
	{
		if (SYDEKeyCode::get_key('S')._CompareState(KEY))
		{
			AddMomentum(Vector2(0, 1));
		}
		if (SYDEKeyCode::get_key('W')._CompareState(KEY) && checkGrounded())
		{
			AddMomentum(Vector2(0, -4));
		}
		if (SYDEKeyCode::get_key('D')._CompareState(KEY))
		{
			AddPosition(Vector2(1, 0));
		}
		if (SYDEKeyCode::get_key('A')._CompareState(KEY))
		{
			AddPosition(Vector2(-1, 0));
		}


		//PURPOSEFULLY BROKEN SHIT
		if (SYDEKeyCode::get_key('Q')._CompareState(KEY))
		{
			AddPosition(Vector2(-5, 0));
		}

		if (SYDEKeyCode::get_key('E')._CompareState(KEY))
		{
			AddPosition(Vector2(5, 0));
		}
		ApplyMomentum();
		momentumTime -= 0.05f;
	}
	momentumTime += SYDEDefaults::getDeltaTime();

	return window;
}

void SYDEPlatformer::AddMomentum(Vector2 momentum)
{
	m_Momentum += momentum;
	if (m_Momentum.getX() < -1)
	{
		m_Momentum.setX(-1);
	}
	if (m_Momentum.getX() > 1)
	{
		m_Momentum.setX(1);
	}
	if (m_Momentum.getY() < -8)
	{
		m_Momentum.setY(-8);
	}
	if (m_Momentum.getY() > 8)
	{
		m_Momentum.setY(8);
	}
}

void SYDEPlatformer::AddPosition(Vector2 add)
{
	int PositionY = add.getY();
	while (PositionY > 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, 1)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			PositionY = 0;
		}
		else
		{
			PlayerPos.addY(1);
			PositionY -= 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
	while (PositionY < 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, -1)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			PositionY = 0;
		}
		else
		{
			PlayerPos.addY(-1);
			PositionY += 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
	int PositionX = add.getX();
	while (PositionX > 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(1, 0)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			PositionX = 0;
		}
		else
		{
			PlayerPos.addX(1);
			PositionX -= 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
	while (PositionX < 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(-1, 0)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			PositionX = 0;
		}
		else
		{
			PlayerPos.addX(-1);
			PositionX += 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
}

void SYDEPlatformer::ApplyMomentum()
{
	//DO GRAVITY FIRST
	int MomentumY = m_Momentum.getY();
	while (MomentumY > 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, 1)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			m_Momentum.setY(0);
			MomentumY = 0;
		}
		else
		{
			PlayerPos.addY(1);
			MomentumY -= 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
	while (MomentumY < 0)
	{
		if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(0, -1)) == BRIGHTWHITE_BRIGHTWHITE_BG)
		{
			m_Momentum.setY(-1);
			MomentumY = 0;
		}
		else
		{
			PlayerPos.addY(-1);
			MomentumY += 1;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
		{
			//START
			PlayerPos = CheckPoint;
		}
		if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
		{
			//START
			CheckPoint = PlayerPos;
		}
	}
	m_Momentum.addY(1);

	int MomentumX = m_Momentum.getX();
	while (MomentumX != 0)
	{
		if (MomentumX > 0)
		{
			if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(1, 0)) == BRIGHTWHITE_BRIGHTWHITE_BG)
			{
				m_Momentum.setX(0);
				MomentumX = 0;
			}
			else
			{
				PlayerPos.addX(1);
				MomentumY -= 1;
			}
			if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
			{
				//START
				PlayerPos = CheckPoint;
			}
			if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
			{
				//START
				CheckPoint = PlayerPos;
			}
		}
		else
		{
			if (m_MainMap.getColourAtPoint(PlayerPos + Vector2(-1, 0)) == BRIGHTWHITE_BRIGHTWHITE_BG)
			{
				m_Momentum.setX(0);
				MomentumX = 0;
			}
			else
			{
				PlayerPos.addX(-1);
				MomentumY += 1;
			}
			if (m_MainMap.getColourAtPoint(PlayerPos) == RED_RED_BG)
			{
				//START
				PlayerPos = CheckPoint;
			}
			if (m_MainMap.getColourAtPoint(PlayerPos) == BLUE_BLUE_BG)
			{
				//START
				CheckPoint = PlayerPos;
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