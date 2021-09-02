#include "pch.h"
#include "SYDETextBox.h"

SYDETextBox::SYDETextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass a_TextColour)
{
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = a_TextColour;
}

ConsoleWindow SYDETextBox::draw_ui(ConsoleWindow window)
{
	int stringNo = 1;
	for (int ii = m_Pos.getY(); ii < m_Pos.getY() + m_Size.getY(); ii++)
	{
		for (int i = m_Pos.getX(); i < m_Pos.getX() + m_Size.getX(); i++)
		{
			if (stringNo <= m_Text.size())
			{
				window.setTextAtPoint(Vector2(i, ii), m_Text.substr(stringNo - 1, 1) , TextColour);
				stringNo++;
			}
			else
			{
				window.setTextAtPoint(Vector2(i, ii), " ", TextColour);
			}
		}
	}
	_CheckState();
	return window;
}

bool SYDEClickableTextBox::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + m_Size.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + m_Size.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}

SYDEClickableTextBox::SYDEClickableTextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour)
{
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
}

ConsoleWindow SYDEClickableTextBox::draw_ui(ConsoleWindow window)
{
	int stringNo = 1;
	for (int ii = m_Pos.getY(); ii < m_Pos.getY() + m_Size.getY(); ii++)
	{
		for (int i = m_Pos.getX(); i < m_Pos.getX() + m_Size.getX(); i++)
		{
			if (stringNo <= m_Text.size())
			{
				window.setTextAtPoint(Vector2(i, ii), m_Text.substr(stringNo - 1, 1), TextColour);
				stringNo++;
			}
			else
			{
				window.setTextAtPoint(Vector2(i, ii), " ", TextColour);
			}
		}
	}
	_CheckState();
	if (m_Active)
	{
		if (drawFlash)
		{
			if (m_Text.size() < m_Size.getX())
			{
				window.setTextAtPoint(Vector2(m_Text.size(), m_Pos.getY()), " ", HILIGHTCOLOUR);
			}
		}
		timeSpentFlash += SYDEDefaults::getDeltaTime();
		if (timeSpentFlash > flashTime)
		{
			timeSpentFlash = 0;
			drawFlash = !drawFlash;
		}
		if (SYDEKeyCode::getBackSpaceSafe())
		{
			timeSpent += SYDEDefaults::getDeltaTime();
			if (timeSpent >= backspaceTime)
			{
				timeSpent = 0;
				if (m_Text.length() > 0)
				{
					m_Text = m_Text.substr(0, m_Text.size() - 1);
				}
			}
		}
		else
		{
			timeSpent = 0.25f;
			addText(SYDEKeyCode::KeysDownSafe());
		}
	}
	if (m_TxtState = TEXTCHANGED)
	{
		DoFunc();
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()) && canClick)
	{
		m_Active = true;
		canClick = false;
	}
	else if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && canClick)
	{
		m_Active = false;
		canClick = false;
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) || SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(NONE))
	{
		canClick = true;
	}

	return window;
}
