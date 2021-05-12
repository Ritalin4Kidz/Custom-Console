#include "pch.h"
#include "SYDEMenu.h"

ConsoleWindow SYDEMenu::draw_menu(ConsoleWindow window)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		window = m_Items[i].draw_ui(window);
	}
	return window;
}

void SYDEMenu::RemoveOptionAtIndex(int i)
{
	m_Items.erase(m_Items.begin() + i);
}

void SYDEMenu::prevSelect()
{
	selectionNumber--;
	if (selectionNumber < 0)
	{
		selectionNumber = m_Items.size() - 1;
	}
	hiLight();
}

void SYDEMenu::nextSelect()
{
	selectionNumber++; 
	if (selectionNumber >= m_Items.size()) 
	{ 
		selectionNumber = 0; 
	} 
	hiLight();
}

void SYDEMenu::hiLight()
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i]._HIGHLIGHT(false); 
	} 
	m_Items[selectionNumber]._HIGHLIGHT(true);
}

void SYDEMenu::shiftMenu(Vector2 pos)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i].setPos(m_Items[i].getPos() + pos);
	}
}

ConsoleWindow SYDEAdaptiveMenu::draw_menu(ConsoleWindow window)
{
	if (!m_Active) return window;

	for (int i = 0; i < m_Items.size(); i++)
	{
		if (selectedOffCurrentHighlight)
		{
			if (m_Items[i].getButton().getCurrentlyHighlighted())
			{
				selectionNumber = i;
			}
		}
		m_Items[i].draw_ui(window);
	}
	if (m_Items[selectionNumber].getDisplay())
	{
		m_Items[selectionNumber].drawDisplay(window);
	}
	return window;
}

void SYDEAdaptiveMenu::RemoveOptionAtIndex(int i)
{
	m_Items.erase(m_Items.begin() + i);
}

void SYDEAdaptiveMenu::prevSelect()
{
	selectionNumber--;
	if (selectionNumber < 0)
	{
		selectionNumber = m_Items.size() - 1;
	}
	hiLight();
}

void SYDEAdaptiveMenu::nextSelect()
{
	selectionNumber++;
	if (selectionNumber >= m_Items.size())
	{
		selectionNumber = 0;
	}
	hiLight();
}

void SYDEAdaptiveMenu::hiLight()
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i].setButtonHighlight(false);
	}
	m_Items[selectionNumber].setButtonHighlight(true);
}

void SYDEAdaptiveMenu::shiftMenu(Vector2 pos)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i].getButton().setPos(m_Items[i].getButton().getPos() + pos);
	}
}
