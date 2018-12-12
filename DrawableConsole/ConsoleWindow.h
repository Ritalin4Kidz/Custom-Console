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
	BRIGHTGREEN_BLUE_BG,
	RED_BLUE_BG,
	BRIGHTRED_BLUE_BG,
	TESTCOLOUR
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