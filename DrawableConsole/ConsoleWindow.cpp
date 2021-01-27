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
			if (colour != NULLCOLOUR)
			{
				addLayerToLine((int)point.getY(), text, colour, NULL, (int)point.getX());
			}
		}
	}
}

ColourClass ConsoleWindow::_intToColour(int colour_int)
{
	return (ColourClass)colour_int;
}

ColourClass ConsoleWindow::getTextColourAtPoint(Vector2 point)
{
	if (point.getY() < m_Lines.size() && point.getY() > 0)
	{
		if (point.getX() < m_Lines[(int)point.getY()].getLine().size())
		{
			return static_cast<ColourClass>(m_Lines[point.getY()].getLine()[point.getX()].getColour());
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
	for (int i = 0; i < offset.getY() + _StartingLine; i++)
	{
		blank.writeLine();
	}	
	for (int i = _StartingLine; i < m_Lines.size(); i++)
	{
		m_Lines[i].writeLine(offset.getX());
	}
}

void ConsoleWindow::writeConsoleOptimized()
{
	Line blank;
	for (int i = 0; i < offset.getY() + _StartingLine; i++)
	{
		blank.writeLine();
	}
	for (int i = _StartingLine; i < m_Lines.size(); i++)
	{
		m_Lines[i].writeLineOptimized(offset.getX());
	}
}

ColourClass ConsoleWindow::determineColourAtPoint(Vector2 point, ColourClass main, bool onlyFG)
{
	ColourClass bg = getTextColourAtPoint(point);
	if (onlyFG)
	{
		int colour = (int)main % 16;
		//CHANGE MAIN TO ORIGINAL 16 COLOURS
		switch (colour)
		{
		case 0:
			main = BLACK;
			break;
		case 1:
			main = BLUE;
			break;
		case 2:
			main = GREEN;
			break;
		case 3:
			main = AQUA;
			break;
		case 4:
			main = RED;
			break;
		case 5:
			main = PURPLE;
			break;
		case 6:
			main = YELLOW;
			break;
		case 7:
			main = WHITE;
			break;
		case 8:
			main = LIGHTGREY;
			break;
		case 9:
			main = DARKBLUE;
			break;
		case 10:
			main = BRIGHTGREEN;
			break;
		case 11:
			main = LIGHTBLUE;
			break;
		case 12:
			main = BRIGHTRED;
			break;
		case 13:
			main = LIGHTPURPLE;
			break;
		case 14:
			main = BRIGHTYELLOW;
			break;
		case 15:
			main = BRIGHTWHITE;
			break;
		default:
			main = BLACK;
		}
	}
	if (bg >= BLACK_BLUE_BG && bg < BLACK_GREEN_BG)
	{
		return (ColourClass)(main + BLACK_BLUE_BG);
	}

	if (bg >= BLACK_GREEN_BG && bg < BLACK_AQUA_BG)
	{
		return (ColourClass)(main + BLACK_GREEN_BG);
	}

	if (bg >= BLACK_AQUA_BG && bg < BLACK_RED_BG)
	{
		return (ColourClass)(main + BLACK_AQUA_BG);
	}

	if (bg >= BLACK_RED_BG && bg < BLACK_PURPLE_BG)
	{
		return (ColourClass)(main + BLACK_RED_BG);
	}

	if (bg >= BLACK_PURPLE_BG && bg < BLACK_YELLOW_BG)
	{
		return (ColourClass)(main + BLACK_PURPLE_BG);
	}

	if (bg >= BLACK_YELLOW_BG && bg < BLACK_WHITE_BG)
	{
		return (ColourClass)(main + BLACK_YELLOW_BG);
	}

	if (bg >= BLACK_WHITE_BG && bg < BLACK_LIGHTGREY_BG)
	{
		return (ColourClass)(main + BLACK_WHITE_BG);
	}

	if (bg >= BLACK_LIGHTGREY_BG && bg < BLACK_DARKBLUE_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTGREY_BG);
	}

	if (bg >= BLACK_DARKBLUE_BG && bg < BLACK_BRIGHTGREEN_BG)
	{
		return (ColourClass)(main + BLACK_DARKBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTGREEN_BG && bg < BLACK_LIGHTBLUE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTGREEN_BG);
	}

	if (bg >= BLACK_LIGHTBLUE_BG && bg < BLACK_BRIGHTRED_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTRED_BG && bg < BLACK_LIGHTPURPLE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTRED_BG);
	}

	if (bg >= BLACK_LIGHTPURPLE_BG && bg < BLACK_BRIGHTYELLOW_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTPURPLE_BG);
	}

	if (bg >= BLACK_BRIGHTYELLOW_BG && bg < BLACK_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTYELLOW_BG);
	}

	if (bg >= BLACK_BRIGHTWHITE_BG && bg <= BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTWHITE_BG);
	}
	return main;
}

ColourClass ConsoleWindow::get_BG_Colour_At_Point_Only(Vector2 point)
{
	ColourClass bg = getTextColourAtPoint(point);

	//if (bg < BLACK_BLUE_BG)
	//{
	//	return BLACK;
	//}
	if (bg >= BLACK_BLUE_BG && bg < BLACK_GREEN_BG)
	{
		return BLUE_BLUE_BG;
	}

	if (bg >= BLACK_GREEN_BG && bg < BLACK_AQUA_BG)
	{
		return GREEN_GREEN_BG;
	}

	if (bg >= BLACK_AQUA_BG && bg < BLACK_RED_BG)
	{
		return AQUA_AQUA_BG;
	}

	if (bg >= BLACK_RED_BG && bg < BLACK_PURPLE_BG)
	{
		return RED_RED_BG;
	}

	if (bg >= BLACK_PURPLE_BG && bg < BLACK_YELLOW_BG)
	{
		return PURPLE_PURPLE_BG;
	}

	if (bg >= BLACK_YELLOW_BG && bg < BLACK_WHITE_BG)
	{
		return YELLOW_YELLOW_BG;
	}

	if (bg >= BLACK_WHITE_BG && bg < BLACK_LIGHTGREY_BG)
	{
		return WHITE_WHITE_BG;
	}

	if (bg >= BLACK_LIGHTGREY_BG && bg < BLACK_DARKBLUE_BG)
	{
		return LIGHTGREY_LIGHTGREY_BG;
	}

	if (bg >= BLACK_DARKBLUE_BG && bg < BLACK_BRIGHTGREEN_BG)
	{
		return DARKBLUE_DARKBLUE_BG;
	}

	if (bg >= BLACK_BRIGHTGREEN_BG && bg < BLACK_LIGHTBLUE_BG)
	{
		return BRIGHTGREEN_BRIGHTGREEN_BG;
	}

	if (bg >= BLACK_LIGHTBLUE_BG && bg < BLACK_BRIGHTRED_BG)
	{
		return LIGHTBLUE_LIGHTBLUE_BG;
	}

	if (bg >= BLACK_BRIGHTRED_BG && bg < BLACK_LIGHTPURPLE_BG)
	{
		return BRIGHTRED_BRIGHTRED_BG;
	}

	if (bg >= BLACK_LIGHTPURPLE_BG && bg < BLACK_BRIGHTYELLOW_BG)
	{
		return LIGHTPURPLE_LIGHTPURPLE_BG;
	}

	if (bg >= BLACK_BRIGHTYELLOW_BG && bg < BLACK_BRIGHTWHITE_BG)
	{
		return BRIGHTYELLOW_BRIGHTYELLOW_BG;
	}

	if (bg >= BLACK_BRIGHTWHITE_BG && bg <= BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return BRIGHTWHITE_BRIGHTWHITE_BG;
	}
	return BLACK;
}

void ConsoleWindow::operator=(ConsoleWindow other)
{
	m_Lines = other.m_Lines;
	offset = other.offset;
}
