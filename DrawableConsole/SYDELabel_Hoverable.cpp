#include "pch.h"
#include "SYDELabel_Hoverable.h"

SYDELabel_Hoverable::SYDELabel_Hoverable(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG)
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	_TRANSPARENT = _TRANSPARENTBG;
	TextColour = txtColour;
}

SYDELabel_Hoverable::SYDELabel_Hoverable(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG, void(*f)())
{
	m_Text = a_text;
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = txtColour;
	_TRANSPARENT = _TRANSPARENTBG;
	m_Function = f;
}

ConsoleWindow SYDELabel_Hoverable::draw_ui(ConsoleWindow window)
{
	if (pointIsInButtonRange(SYDEKeyCode::getMousePosition()))
	{
		if (hovering == false)
		{
			hovering = true;
			DoFunc();
		}
	}
	else
	{
		hovering = false;
	}
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

bool SYDELabel_Hoverable::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + m_Size.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + m_Size.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}