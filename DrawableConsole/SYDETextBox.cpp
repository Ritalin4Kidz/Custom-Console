#include "pch.h"
#include "SYDETextBox.h"

SYDETextBox::SYDETextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass a_TextColour)
{
	m_Pos = a_Pos;
	m_Size = a_Size;
	TextColour = a_TextColour;
}

ConsoleWindow SYDETextBox::draw_textbox(ConsoleWindow window)
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
