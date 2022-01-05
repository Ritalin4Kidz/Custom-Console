#include "pch.h"
#include "SYDERadioButtonMenu.h"

SYDERadioButtonMenu::SYDERadioButtonMenu(Vector2 a_Pos, vector<SYDERadioOption> options)
{
	m_Pos = a_Pos;
	m_Options = options;
}

ConsoleWindow SYDERadioButtonMenu::draw_ui(ConsoleWindow window)
{
	for (int i = 0, yPos = m_Pos.getY(); i < m_Options.size(); i++,yPos += 1 + m_Spacing)
	{
		window = m_Options[i].draw_ui_at_vector(window, Vector2(m_Pos.getX(), yPos));
		if (m_Options[i].getOptionClicked())
		{
			for (int ii = 0; ii < m_Options.size(); ii++)
			{
				m_Options[ii].setIsChecked(false);
			}
			m_Options[i].setIsChecked(true);
		}
	}
	return window;
}

int SYDERadioButtonMenu::getChecked()
{
	for (int i = 0; i < m_Options.size(); i++)
	{
		if (m_Options[i].isChecked())
		{
			return i;
		}
	}
	return -1;
}

SYDERadioOption::SYDERadioOption(string a_text, ColourClass txtColour, ColourClass checkBoxClr)
{
	m_Text = a_text;
	TextColour = txtColour;
	CheckBoxColour = checkBoxClr;
}

ConsoleWindow SYDERadioOption::draw_ui_at_vector(ConsoleWindow window, Vector2 point)
{
	ColourClass _TXT = TextColour;
	optionClicked = false;
	for (int i = 0; i < m_Text.size(); i++)
	{
		_TXT = window.determineColourAtPoint(Vector2(point.getX() + i, point.getY()), TextColour, true);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY()), m_Text.substr(i, 1), _TXT);
	}
	if (m_Checked)
	{
		window.setTextAtPoint(Vector2(point.getX() + m_Text.size() + 1, point.getY()), "><", CheckBoxColour);
	}
	else
	{
		window.setTextAtPoint(Vector2(point.getX() + m_Text.size() + 1, point.getY()), "  ", CheckBoxColour);
	}
	_CheckState();
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInCheckRange(SYDEKeyCode::GetLastClickPosition(), Vector2(point.getX() + m_Text.size() + 1, point.getY())) && canClick)
	{
		canClick = false;
		if (m_Checked)
		{
			m_Checked = false;
		}
		else
		{
			optionClicked = true;
		}
		DoFunc();
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) || SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(NONE))
	{
		canClick = true;
	}
	return window;
}

bool SYDERadioOption::pointIsInCheckRange(Vector2 Point, Vector2 m_Pos)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX()&& (Point.getX() < m_Pos.getX() + 3));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}
