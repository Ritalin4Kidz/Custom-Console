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
