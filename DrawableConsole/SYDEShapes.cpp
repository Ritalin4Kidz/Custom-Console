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
			window.setTextAtPoint(Vector2(l,h), std::string(1, m_Char), m_Colour);
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
			window.setTextAtPoint(Vector2(l, h), std::string(1, m_Char), m_Colour);
		}
	}
	return window;
}

ConsoleWindow SYDEShape::draw_at_point(ConsoleWindow window, Vector2 a_Pos)
{
	Vector2 temp = m_Pos;
	m_Pos = a_Pos;
	window = draw(window);
	m_Pos = temp;
	return window;
}

ConsoleWindow SYDECircle::draw(ConsoleWindow window)
{
	for (int i = -(m_Size.getX() * 2); i <= m_Size.getX() * 2; i+= 2)
	{
		int j = i;
		if (j < 0)
		{
			j = -j;
		}
		j /= 2;
		int k = m_Size.getX() - j;
		for (int m = -k; m <= k; m++)
		{
			window.setTextAtPoint(Vector2(m_Pos.getX() + i, m_Pos.getY() + m), std::string(1, m_Char), m_Colour);
			window.setTextAtPoint(Vector2(m_Pos.getX() + i + 1, m_Pos.getY() + m), std::string(1, m_Char), m_Colour);
		}
	}
	return window;
}
