#include "pch.h"
#include "SYDECheckbox.h"

SYDECheckbox::SYDECheckbox(string a_text, Vector2 a_Pos, ColourClass txtColour, ColourClass checkBoxClr, bool checked)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	TextColour = txtColour;
	CheckBoxColour = checkBoxClr;
	m_Checked = checked;
}

ConsoleWindow SYDECheckbox::draw_ui(ConsoleWindow window)
{
	ColourClass _TXT = TextColour;
	for (int i = 0; i < m_Text.size(); i++)
	{
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + i, m_Pos.getY()), TextColour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + i, m_Pos.getY()), m_Text.substr(i, 1), _TXT);
	}
	if (m_Checked)
	{
		window.setTextAtPoint(Vector2(m_Pos.getX() + m_Text.size() + 1, m_Pos.getY()), "><", CheckBoxColour);
	}
	else
	{
		window.setTextAtPoint(Vector2(m_Pos.getX() + m_Text.size() + 1, m_Pos.getY()), "  ", CheckBoxColour);
	}
	_CheckState();

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()) && canClick)
	{
		canClick = false;
		DoFunc();
		m_Checked = !m_Checked;
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) || SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(NONE))
	{
		canClick = true;
	}
	return window;
}

bool SYDECheckbox::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() + m_Text.size() + 1 && (Point.getX() < m_Pos.getX() + m_Text.size() + 3));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}
