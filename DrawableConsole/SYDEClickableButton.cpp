#include "pch.h"
#include "SYDEClickableButton.h"

string SYDEClickableButton::lastTag = "";

SYDEClickableButton::SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	_TRANSPARENT = _TRANSPARENTBG;
}

SYDEClickableButton::SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	HiLightColour = a_hiLightColour;
	_TRANSPARENT = _TRANSPARENTBG;
}

SYDEClickableButton::SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)())
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	HiLightColour = a_hiLightColour;
	_TRANSPARENT = _TRANSPARENTBG;
	m_Function = f;
}

ConsoleWindow SYDEClickableButton::draw_ui(ConsoleWindow window)
{
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
	
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()) &&canClick)
	{
		lastTag = tag;
		canClick = false;
		DoFunc();
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) || SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(NONE))
	{
		canClick = true;
	}
	return window;
}

ConsoleWindow SYDEClickableButton::draw_ui(ConsoleWindow window, Vector2 point)
{
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
	for (int ii = point.getY(); ii < point.getY() + m_Size.getY(); ii++)
	{
		for (int i = point.getX(); i < point.getX() + m_Size.getX(); i++)
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

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(point, SYDEKeyCode::GetLastClickPosition()))
	{
		lastTag = tag;
		DoFunc();
	}

	return window;
}

string SYDEClickableButton::getLastButtonTag()
{
	return lastTag;
}

bool SYDEClickableButton::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + m_Size.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + m_Size.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}

bool SYDEClickableButton::pointIsInButtonRange(Vector2 Point, Vector2 mousePos)
{
	bool withinLengthBoundaries = (mousePos.getX() >= Point.getX() && (mousePos.getX() < Point.getX() + m_Size.getX()));
	bool withinHeightBoundaries = (mousePos.getY() >= Point.getY() && (mousePos.getY() < Point.getY() + m_Size.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}