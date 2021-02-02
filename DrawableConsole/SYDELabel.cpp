#include "pch.h"
#include "SYDELabel.h"

SYDELabel::SYDELabel(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	_TRANSPARENT = _TRANSPARENTBG;
	TextColour = txtColour;
}

ConsoleWindow SYDELabel::draw_ui(ConsoleWindow window)
{
	switch (_Anchor)
	{
		case SLA_Center:
			window = draw_center_anchored(window);
			break;
		case SLA_Right:
			window = draw_right_anchored(window);
			break;
		case SLA_Normal:
		default:
			window = draw_normal(window);
			break;
	}
	_CheckState();
	return window;
}

ConsoleWindow SYDELabel::draw_normal(ConsoleWindow window)
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
				_TXT = window.determineColourAtPoint(Vector2(i, ii), TextColour, true);
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
	return window;
}

ConsoleWindow SYDELabel::draw_center_anchored(ConsoleWindow window)
{
	//TODO: IMPLEMENT
	throw std::exception("Not Implemented");
	return window;
}

ConsoleWindow SYDELabel::draw_right_anchored(ConsoleWindow window)
{
	int stringNo = m_Text.size();
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
		for (int i = (m_Pos.getX() + m_Size.getX()) - 1; i >= m_Pos.getX(); i--)
		{
			if (_TRANSPARENT)
			{
				_TXT = window.determineColourAtPoint(Vector2(i, ii), TextColour, true);
			}
			if (stringNo >= 1)
			{
				window.setTextAtPoint(Vector2(i, ii), m_Text.substr(stringNo - 1, 1), _TXT);
				stringNo--;
			}
			else
			{
				window.setTextAtPoint(Vector2(i, ii), " ", _TXT);
			}
		}
	}
	return window;
}

