#include "pch.h"
#include "SYDERadialMenu.h"

SYDERadialOption::SYDERadialOption(string a_text, ColourClass txtColour, ColourClass a_hoverColour, string a_Symbol, Vector2 displayPos)
{
	m_Text = a_text;
	TextColour = txtColour;
	HoverColour = a_hoverColour;
	m_Symbol = a_Symbol;
	textDisplayPos = displayPos;
}

ConsoleWindow SYDERadialOption::draw_ui_at_vector(ConsoleWindow window, Vector2 point)
{
	isHighlighted = false;
	ColourClass _TXT = TextColour;
	if (pointIsInCheckRange(SYDEKeyCode::getMousePosition(), point))
	{
		window.setTextAtPoint(textDisplayPos, m_Text, _TXT);
		_TXT = HoverColour;
		isHighlighted = true;
	}
	optionClicked = false;
	window.setTextAtPoint(Vector2(point.getX() - 1, point.getY()), " ", _TXT);
	window.setTextAtPoint(Vector2(point.getX(), point.getY()), m_Symbol, _TXT);
	window.setTextAtPoint(Vector2(point.getX() + 1, point.getY()), " ", _TXT);
	_CheckState();
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInCheckRange(SYDEKeyCode::GetLastClickPosition(), point) && canClick)
	{
		canClick = false;
		DoFunc();
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) || SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(NONE))
	{
		canClick = true;
	}
	return window;
}

bool SYDERadialOption::pointIsInCheckRange(Vector2 Point, Vector2 m_Pos)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() - 1 && (Point.getX() < m_Pos.getX() + 1));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}

SYDERadialMenu_Basic::SYDERadialMenu_Basic(Vector2 a_Pos, SYDERadialOption northBtn, SYDERadialOption westBtn, SYDERadialOption southBtn, SYDERadialOption eastBtn)
{
	m_Pos = a_Pos;
	m_North = northBtn;
	m_South = southBtn;
	m_West = westBtn;
	m_East = eastBtn;
}

ConsoleWindow SYDERadialMenu_Basic::draw_ui(ConsoleWindow window)
{
	ColourClass _TXT = window.determineColourAtPoint(Vector2(m_Pos.getX(), m_Pos.getY()), BLACK, true);
	window.setTextAtPoint(Vector2(m_Pos.getX(), m_Pos.getY()), ".", _TXT);


	window = m_North.draw_ui_at_vector(window, Vector2(m_Pos.getX(), (m_Pos.getY() - 4) - m_Spacing));
	window = m_South.draw_ui_at_vector(window, Vector2(m_Pos.getX(), (m_Pos.getY() + 4) + m_Spacing));
	window = m_West.draw_ui_at_vector(window, Vector2((m_Pos.getX() - 8) - (m_Spacing * 2), m_Pos.getY()));
	window = m_East.draw_ui_at_vector(window, Vector2((m_Pos.getX() + 8) + (m_Spacing * 2), m_Pos.getY()));
	return window;
}

int SYDERadialMenu_Basic::getHighlightedIndex()
{
	if (m_North.getIsHighlighted()) return 0;
	if (m_West.getIsHighlighted()) return 1;
	if (m_South.getIsHighlighted()) return 2;
	if (m_East.getIsHighlighted()) return 3;
	return -1;
}
