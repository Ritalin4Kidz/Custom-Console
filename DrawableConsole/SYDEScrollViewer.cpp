
#include "SYDEScrollViewer.h"

#include "pch.h"

void SYDEScrollViewer::init()
{
	m_Scrollbar.setPos(Vector2(m_Pos.getX() + m_Size.getX(), m_Pos.getY()));
	m_Scrollbar.setSize(m_Size.getY());

	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i].setPos(Vector2(m_Items[i].getPos().getX() + m_Pos.getX(), m_Items[i].getPos().getY() + m_Pos.getY()));
	}

}

ConsoleWindow SYDEScrollViewer::draw_ui(ConsoleWindow window)
{
	if (m_ViewStartingLine != m_Scrollbar.getValue())
	{
		int diff = m_Scrollbar.getValue() - m_ViewStartingLine;
		for (int i = 0; i < m_Items.size(); i++)
		{
			m_Items[i].setPos(Vector2(m_Items[i].getPos().getX(), m_Items[i].getPos().getY() - diff));
		}
		m_ViewStartingLine = m_Scrollbar.getValue();
	}
	for (int i = 0; i < m_Size.getX(); i++)
	{
		for (int ii = 0; ii < m_Size.getY(); ii++)
		{
			if (BackgroundColour != NULLCOLOUR)
			{
				window.setTextAtPoint(Vector2(i + m_Pos.getX(), ii + m_Pos.getY()), " ", BackgroundColour);
			}
		}
	}
	int m_ViewEndingLine = m_ViewStartingLine + m_Size.getY();
	for (int i = 0; i < m_Items.size(); i++)
	{
		if (m_Items[i].getPos().getY() >= m_Pos.getY() && m_Items[i].getPos().getY() < m_Size.getY())
		{
			window = m_Items[i].draw_ui(window);
		}
	}
	window = m_Scrollbar.draw_ui(window);
	return window;
}
