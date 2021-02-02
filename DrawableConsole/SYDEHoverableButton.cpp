#include "pch.h"
#include "SYDEHoverableButton.h"

SYDEHoverableButton::SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	_TRANSPARENT = _TRANSPARENTBG;
}

SYDEHoverableButton::SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	HiLightColour = a_hiLightColour;
	_TRANSPARENT = _TRANSPARENTBG;
}

SYDEHoverableButton::SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, bool _Clickable)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	HiLightColour = a_hiLightColour;
	_TRANSPARENT = _TRANSPARENTBG;
	m_Clickable = _Clickable;
}

SYDEHoverableButton::SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)())
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	HiLightColour = a_hiLightColour;
	_TRANSPARENT = _TRANSPARENTBG;
	m_Function = f;
}

ConsoleWindow SYDEHoverableButton::draw_ui(ConsoleWindow window)
{
	if (pointIsInButtonRange(SYDEKeyCode::getMousePosition()))
	{
		_HIGHLIGHTED = true;
		if (m_Clickable)
		{
			if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()))
			{
				DoFunc();
			}
		}
	}
	else
	{
		_HIGHLIGHTED = false;
	}


	int stringNo = 1;
	ColourClass _TXT = TextColour;
	if (_HIGHLIGHTED)
	{
		_TXT = HiLightColour;
	}
	if (_WRAPTEXT) {
		int y = m_Size.getY();
		int x = m_Size.getX();
		int TotalSize = y * x;
		while (m_Text.size() > TotalSize) {
			y++;
			TotalSize = x * y;
		}
		m_Size = Vector2(x, y);
	}
	for (int ii = m_Pos.getY(); ii < m_Pos.getY() + m_Size.getY(); ii++)
	{
		for (int i = m_Pos.getX(); i < m_Pos.getX() + m_Size.getX(); i++)
		{
			if (_TRANSPARENT)
			{
				if (_HIGHLIGHTED) {
					_TXT = window.determineColourAtPoint(Vector2(i, ii), HiLightColour, true);
				}
				else {
					_TXT = window.determineColourAtPoint(Vector2(i, ii), TextColour, true);
				}
			}
			if (stringNo <= m_Text.size())
			{
				window.setTextAtPoint(Vector2(i, ii), m_Text.substr(stringNo - 1, 1), _TXT);
				stringNo++;
			}
			else
			{
				window.setTextAtPoint(Vector2(i, ii), " ", _TXT);
			}
		}
	}
	_CheckState();

	return window;
}

bool SYDEHoverableButton::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + m_Size.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + m_Size.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}
