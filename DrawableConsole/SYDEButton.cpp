#include "pch.h"
#include "SYDEButton.h"

SYDEButton::SYDEButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	_TRANSPARENT = _TRANSPARENTBG;
}

ConsoleWindow SYDEButton::draw_Button(ConsoleWindow window)
{
	int stringNo = 1;
	ColourClass _TXT = TextColour;
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
				if (_HIGHLIGHTED){
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
	if (m_BtnState != BUTTONNONE)
	{
		m_BtnState = BUTTONNONE;
	}
	return window;
}



