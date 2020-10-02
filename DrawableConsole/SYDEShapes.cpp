#include "pch.h"
#include "SYDEShapes.h"

SYDESquare::SYDESquare()
{
	m_Size = 1; m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG;
}

SYDESquare::~SYDESquare()
{
}

ConsoleWindow SYDESquare::draw(ConsoleWindow window)
{
	for (int l = m_Pos.getX(); l < m_Pos.getX() + (m_Size.getX() * 2); l++)
	{
		for (int h = m_Pos.getY(); h < m_Pos.getY() + (m_Size.getY()); h++)
		{
			window.setTextAtPoint(Vector2(l,h), " ", m_Colour);
		}
	}
	return window;
}

ConsoleWindow SYDERect::draw(ConsoleWindow window)
{
	for (int l = m_Pos.getX(); l < m_Pos.getX() + (m_Size.getX() * 2); l++)
	{
		for (int h = m_Pos.getY(); h < m_Pos.getY() + (m_Size.getY()); h++)
		{
			window.setTextAtPoint(Vector2(l, h), " ", m_Colour);
		}
	}
	return window;
}

