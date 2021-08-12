
#include "SYDEOptionCycler.h"

#include "pch.h"


ConsoleWindow SYDEOptionCycler::draw_ui(ConsoleWindow window)
{
	int stringNo = 1;
	ColourClass _TXT = m_Colour;
	string TextDisplay = m_Items[m_SelectedItem].m_Text;
	if (_TRANSPARENT)
	{
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX(), m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX(), m_Pos.getY()), "<", _TXT);
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + 1, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + 1, m_Pos.getY()), "<", _TXT);
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + 2, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + 2, m_Pos.getY()), " ", _TXT);
	}
	else
	{
		window.setTextAtPoint(Vector2(m_Pos.getX(), m_Pos.getY()), "<<", m_Colour);
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + 2, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + 2, m_Pos.getY()), " ", _TXT);
	}
	_TXT = m_Colour;
	for (int i = m_Pos.getX() + 3; i < m_Pos.getX() + size + 3; i++)
	{
		if (_TRANSPARENT)
		{
			_TXT = window.determineColourAtPoint(Vector2(i, m_Pos.getY()), m_Colour, true);
		}
		if (stringNo <= TextDisplay.size())
		{
			window.setTextAtPoint(Vector2(i, m_Pos.getY()), TextDisplay.substr(stringNo - 1, 1), _TXT);
			stringNo++;
		}
		else
		{
			window.setTextAtPoint(Vector2(i, m_Pos.getY()), " ", m_Colour);
		}
	}
	_TXT = m_Colour;
	if (_TRANSPARENT)
	{
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + size + 3, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + size + 3, m_Pos.getY()), " ", _TXT);
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + size + 4, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + size + 4, m_Pos.getY()), ">", _TXT);
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + size + 5, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + size + 5, m_Pos.getY()), ">", _TXT);
	}
	else
	{
		_TXT = window.determineColourAtPoint(Vector2(m_Pos.getX() + size + 3, m_Pos.getY()), m_Colour, true);
		window.setTextAtPoint(Vector2(m_Pos.getX() + size + 3, m_Pos.getY()), " ", _TXT);
		window.setTextAtPoint(Vector2(m_Pos.getX() + size + 4, m_Pos.getY()), ">>", m_Colour);
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && canClick)
	{
		canClick = false;
		if (pointIsInButtonRangeNext(SYDEKeyCode::GetLastClickPosition()))
		{
			DoFunc();
			m_SelectedItem++;
			if (m_SelectedItem >= m_Items.size())
			{
				m_SelectedItem = 0;
			}
		}
		else if(pointIsInButtonRangePrev(SYDEKeyCode::GetLastClickPosition()))
		{
			DoFunc();
			m_SelectedItem--;
			if (m_SelectedItem < 0)
			{
				m_SelectedItem = m_Items.size() - 1;
			}
		}
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP))
	{
		canClick = true;
	}


	return window;
}

bool SYDEOptionCycler::pointIsInButtonRangePrev(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= (m_Pos.getX()) && (Point.getX() < (m_Pos.getX() + 2)));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}

bool SYDEOptionCycler::pointIsInButtonRangeNext(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= (m_Pos.getX() + size + 4) && (Point.getX() < (m_Pos.getX() + size + 6)));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}
