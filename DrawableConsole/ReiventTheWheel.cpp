#include "pch.h"
#include "ReiventTheWheel.h"

void GAME_RTW::generalConstructor()
{
	m_CursorPoint = Vector2(10,5);
}

void GAME_RTW::setUpPaintArray(int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			m_PaintingArray.push_back(GAME_RTW_PIXEL(Vector2(l,m)));
		}
	}
}

void GAME_RTW::setPaintArrayAtPoint(Vector2 aPoint, ColourClass colour)
{
	for (int i = 0; i < m_PaintingArray.size(); i++)
	{
		if (m_PaintingArray[i].getPoint() == aPoint) {
			m_PaintingArray[i].setColour(colour);
			return;
		}
	}
}

ConsoleWindow GAME_RTW::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	inputVoids();
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	for (int i = 0; i < m_PaintingArray.size(); i++)
	{
		window.setTextAtPoint(m_PaintingArray[i].getPoint(), " ", m_PaintingArray[i].getColour());
	}
	// CURSOR
	window.setTextAtPoint(m_CursorPoint, " ", DARKBLUE_DARKBLUE_BG);
	window.setTextAtPoint(Vector2(m_CursorPoint.getX() + 1, m_CursorPoint.getY()), " ", DARKBLUE_DARKBLUE_BG);
	// UI
	for (int i = 0; i < windowWidth; i++)
	{
		window.setTextAtPoint(Vector2(i, windowHeight - 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	if (m_PaintColour == NULLCOLOUR)
	{
		window.setTextAtPoint(Vector2(0, windowHeight - 1), "-", BLACK_BRIGHTWHITE_BG);
		window.setTextAtPoint(Vector2(1, windowHeight - 1), "-", BLACK_BRIGHTWHITE_BG);
	}
	else {
		window.setTextAtPoint(Vector2(0, windowHeight - 1), " ", m_PaintColour);
		window.setTextAtPoint(Vector2(1, windowHeight - 1), " ", m_PaintColour);
	}
	window.setTextAtPoint(Vector2( 2, windowHeight - 1), "P", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 3, windowHeight - 1), ":", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 4, windowHeight - 1), "P", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 5, windowHeight - 1), "a", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 6, windowHeight - 1), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 7, windowHeight - 1), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 8, windowHeight - 1), "t", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2( 9, windowHeight - 1), ",", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(10, windowHeight - 1), "C", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(11, windowHeight - 1), ":", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(12, windowHeight - 1), "C", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(13, windowHeight - 1), "o", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(14, windowHeight - 1), "l", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(15, windowHeight - 1), "o", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(16, windowHeight - 1), "u", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(17, windowHeight - 1), "r", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(18, windowHeight - 1), ",", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(19, windowHeight - 1), "W", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(20, windowHeight - 1), "A", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(21, windowHeight - 1), "S", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(22, windowHeight - 1), "D", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(23, windowHeight - 1), ":", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(24, windowHeight - 1), "M", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(25, windowHeight - 1), "o", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(26, windowHeight - 1), "v", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(27, windowHeight - 1), "e", BLACK_BRIGHTWHITE_BG);
	return window;
}

void GAME_RTW::inputVoids()
{
	if (GetKey('W')) {
		m_CursorPoint.addY(-1);
	}
	if (GetKey('A')) {
		m_CursorPoint.addX(-2);
	}
	if (GetKey('S')) {
		m_CursorPoint.addY(1);
	}
	if (GetKey('D')) {
		m_CursorPoint.addX(2);
	}
	if (GetKey('P')) {
		setPaintArrayAtPoint(m_CursorPoint,m_PaintColour);
		setPaintArrayAtPoint(Vector2(m_CursorPoint.getX() + 1, m_CursorPoint.getY()), m_PaintColour);
	}
	if (GetKey('C')) {
		nextColour();
	}
}

void GAME_RTW::nextColour()
{
	colourcode++;
	if (colourcode >= m_paintColours.size()) {
		colourcode = 0;
	}
	m_PaintColour = m_paintColours[colourcode];
}

bool GAME_RTW::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}

GAME_RTW_PIXEL::GAME_RTW_PIXEL()
{
	m_color = NULLCOLOUR;
	m_point = Vector2(0, 0);
}

GAME_RTW_PIXEL::GAME_RTW_PIXEL(Vector2 a_Point)
{
	m_color = NULLCOLOUR;
	m_point = a_Point;
}
