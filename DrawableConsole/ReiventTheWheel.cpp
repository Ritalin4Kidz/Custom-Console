#include "pch.h"
#include "ReiventTheWheel.h"

void GAME_RTW::generalConstructor()
{
	m_CursorPoint = Vector2(10,5);
	m_scene = "Draw_Wheel";
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
	if (m_scene == "Draw_Wheel")
	{
		inputVoids(windowWidth, windowHeight);
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
		window.setTextAtPoint(Vector2(2, windowHeight - 1), "P:Paint,C:Colour,WASD:Move,T:Test", BLACK_BRIGHTWHITE_BG);
	}
	else if (m_scene == "Test_Wheel")
	{
		inputVoidsWheelTest(windowWidth, windowHeight);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_LIGHTBLUE_BG);
			}
		}
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, windowHeight - 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
		window.setTextAtPoint(Vector2(0, windowHeight - 1), "T:Draw", BLACK_BRIGHTWHITE_BG);
		// TODO: ADD Rigidbody array = all nullcolours
		//		 TEST RIGIDBODYS
	}
	return window;

}

void GAME_RTW::inputVoids(int windowWidth, int windowHeight)
{
	if (GetKey('W')) {
		m_CursorPoint.addYSafe(-1,1, windowHeight - 2);
	}
	if (GetKey('A')) {
		m_CursorPoint.addXSafe(-2,0, windowWidth - 2);
	}
	if (GetKey('S')) {
		m_CursorPoint.addYSafe(1,1, windowHeight - 2);
	}
	if (GetKey('D')) {
		m_CursorPoint.addXSafe(2,0, windowWidth - 2);
	}
	if (GetKey('P')) {
		setPaintArrayAtPoint(m_CursorPoint,m_PaintColour);
		setPaintArrayAtPoint(Vector2(m_CursorPoint.getX() + 1, m_CursorPoint.getY()), m_PaintColour);
	}
	if (GetKey('C')) {
		nextColour();
	}
	if (GetKey(KeyCode_T)) {
		if (!KeyCode_T.getIsPressed()) {
			setUpTest();
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_T.setPressed(false);
	}
}

void GAME_RTW::inputVoidsWheelTest(int windowWidth, int windowHeight)
{
	if (GetKey(KeyCode_T)) {
		if (!KeyCode_T.getIsPressed()) {
			m_scene = "Draw_Wheel";
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_T.setPressed(false);
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

void GAME_RTW::setUpTest()
{
	m_scene = "Test_Wheel";
}

bool GAME_RTW::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}
bool GAME_RTW::GetKey(GAME_RTW_KEYCODE key)
{
	return GetAsyncKeyState(key.getKeyCode()) && 0x8000;
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
