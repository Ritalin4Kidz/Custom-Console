#include "pch.h"
#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow()
{
	// INIT CONSOLE SIZE IN LINES TO 30 AS DEFAULT 
	m_Lines = vector<Line>(30);
	// CLEAR THE SCREEN
	system("CLS");
}

ConsoleWindow::ConsoleWindow(int size)
{
	// INIT CONSOLE SIZE IN LINES TO SIZE VARIABLE
	m_Lines = vector<Line>(size);
	// CLEAR THE SCREEN
	system("CLS");
}

void ConsoleWindow::ClearWindow(bool removeText)
{
	// CLEAR THE SCREEN
	system("CLS");
	// IF WE WANT TO REMOVE TEXT FROM MEMORY
	if (removeText)
	{
		for (int i = 0; i < m_Lines.size(); i++)
		{
			// CHANGE LINE TEXT TO NOTHING
			m_Lines[i].setLine("", WHITE);
		}
	}
}

void ConsoleWindow::addLayerToLine(int index, string a_line, ColourClass colour, char blankSpace, int startPoint)
{
	if (index < m_Lines.size())
	{
		for (int i = 0; i < a_line.size(); i++)
		{
			if (i + startPoint < m_Lines[index].getLine().size())
			{
				if (a_line[i] != ' ' || a_line[i] != blankSpace)
				{
					m_Lines[index].setTextAtLine(i + startPoint, TextItem(a_line[i], colour));
				}
				else if (a_line[i] == blankSpace)
				{
					m_Lines[index].setTextAtLine(i + startPoint, TextItem(' ', colour));
				}
			}
			else
			{
				return;
			}
		}
	}
}

void ConsoleWindow::setTextAtPoint(Vector2 point, string text, ColourClass colour)
{
	if (point.getY() < m_Lines.size() && point.getY() > 0)
	{
		if (point.getX() < m_Lines[(int)point.getY()].getLine().size())
		{
			addLayerToLine((int)point.getY(), text, colour, NULL, (int)point.getX());
		}
	}
}

ColourClass ConsoleWindow::getTextColourAtPoint(Vector2 point)
{
	if (point.getY() < m_Lines.size() && point.getY() > 0)
	{
		if (point.getX() < m_Lines[(int)point.getY()].getLine().size())
		{
			return (ColourClass) m_Lines[point.getY()].getLine()[point.getX()].getColour();
		}
	}
	return BLACK;
}

void ConsoleWindow::eraseConsole()
{
	for (int i = 0; i < m_Lines.size(); i++)
	{
		// CHANGE LINE TEXT TO NOTHING
		m_Lines[i].setLine("", WHITE);
	}
}

void ConsoleWindow::initialize(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < width; ii++)
		{
			addToLine(i, "", WHITE);
		}
	}
}

void ConsoleWindow::writeConsole()
{
	Line blank;
	for (int i = 0; i < offset.getY(); i++)
	{
		blank.writeLine();
	}	
	for (int i = 0; i < m_Lines.size(); i++)
	{
		m_Lines[i].writeLine(offset.getX());
	}
}

void ConsoleWindow::operator=(ConsoleWindow other)
{
	m_Lines = other.m_Lines;
	offset = other.offset;
}
