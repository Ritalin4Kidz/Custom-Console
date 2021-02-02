#pragma once
#include <vector>
#include <string>
#include "TextItem.h"
using namespace std;
/// <summary>
/// Each line of the console window, made of a vector of TextItems
/// </summary>
class Line {
public:
	Line() {}
	Line(vector<TextItem> a_Line) { m_Line = a_Line; }
	Line(Line* a_Line) { *this = a_Line; }
	virtual ~Line() {}

	void writeLine(); 
	void writeLine(int offsetX); 
	void writeLineOptimized(int offsetX);
	void addLine(string a_line, int colour);
	void setLine(string a_line, int colour);
	void setTextAtLine(int index, TextItem other) { m_Line[index] = other; }
	vector<TextItem> getLine() { return m_Line; }


	void operator=(Line other);

private:
	vector<TextItem> m_Line;
	int currentColour = 0;
	string currentTxt = "";
};