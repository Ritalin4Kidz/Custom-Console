#pragma once
#include <vector>
#include <stdlib.h>
#include "Line.h"
#include <string>

#include "Vector2.h"
/*
	COLOUR CLASS ENUM
	Easier way of calling the colour value
	Black = 0, White = 7
*/
enum  ColourClass
{
	BLACK, 
	BLUE, 
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	LIGHTGREY,
	DARKBLUE,
	BRIGHTGREEN,
	LIGHTBLUE,
	BRIGHTRED,
	LIGHTPURPLE,
	BRIGHTYELLOW,
	BRIGHTWHITE,

	BLACK_BLUE_BG,
	BLUE_BLUE_BG,
	GREEN_BLUE_BG,
	AQUA_BLUE_BG,
	RED_BLUE_BG,
	PURPLE_BLUE_BG,
	YELLOW_BLUE_BG,
	WHITE_BLUE_BG,
	LIGHTGREY_BLUE_BG,
	DARKBLUE_BLUE_BG,
	BRIGHTGREEN_BLUE_BG,
	LIGHTBLUE_BLUE_BG,
	BRIGHTRED_BLUE,BG,
	BRIGHTYELLOW_BLUE_BG,
	BRIGHTWHITE_BLUE_BG,

	BLACK_GREEN_BG,
	BLUE_GREEN_BG,
	GREEN_GREEN_BG,
	AQUA_GREEN_BG,
	RED_GREEN_BG,
	PURPLE_GREEN_BG,
	YELLOW_GREEN_BG,
	WHITE_GREEN_BG,
	LIGHTGREY_GREEN_BG,
	DARKBLUE_GREEN_BG,
	BRIGHTGREEN_GREEN_BG,
	LIGHTBLUE_GREEN_BG,
	BRIGHTRED_GREEN_BG,
	LIGHTPURPLE_BLUE_BG,
	BRIGHTYELLOW_GREEN_BG,
	BRIGHTWHITE_GREEN_BG,

	BLACK_AQUA_BG,
	BLUE_AQUA_BG,
	GREEN_AQUA_BG,
	AQUA_AQUA_BG,
	RED_AQUA_BG,
	PURPLE_AQUA_BG,
	YELLOW_AQUA_BG,
	WHITE_AQUA_BG,
	LIGHTGREY_AQUA_BG,
	DARKBLUE_AQUA_BG,
	BRIGHTGREEN_AQUA_BG,
	LIGHTBLUE_AQUA_BG,
	BRIGHTRED_AQUA_BG,
	LIGHTPURPLE_AQUA_BG,
	BRIGHTYELLOW_AQUA_BG,
	BRIGHTWHITE_AQUA_BG,

	BLACK_RED_BG,
	BLUE_RED_BG,
	GREEN_RED_BG,
	AQUA_RED_BG,
	RED_RED_BG,
	PURPLE_RED_BG,
	YELLOW_RED_BG,
	WHITE_RED_BG,
	LIGHTGREY_RED_BG,
	DARKBLUE_RED_BG,
	BRIGHTGREEN_RED_BG,
	LIGHTBLUE_RED_BG,
	BRIGHTRED_RED_BG,
	LIGHTPURPLE_RED_BG,
	BRIGHTYELLOW_RED_BG,
	BRIGHTWHITE_RED_BG,

	TESTCOLOUR,
};
using namespace std;
class ConsoleWindow {
public:
	ConsoleWindow();
	ConsoleWindow(int size);
	virtual ~ConsoleWindow() {}
	void ClearWindow(bool removeText);
	void addToLine(int index, string a_line, ColourClass colour) { if (index < m_Lines.size()) { m_Lines[index].addLine(a_line, colour); } }
	void addLayerToLine(int index, string a_line, ColourClass colour, char blankSpace, int startPoint);
	void setLine(int index, string a_line, ColourClass colour) { if (index < m_Lines.size()) { m_Lines[index].setLine(a_line, colour); } }
	void clearLine(int index) { if (index < m_Lines.size()) { m_Lines[index].setLine(" ", WHITE); } }

	void setTextAtPoint(Vector2 point, string text, ColourClass colour);

	Line getLine(int index) { return m_Lines[index]; }

	void writeConsole();
private:
	vector<Line> m_Lines;
};