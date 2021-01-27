#pragma once
#include <vector>
#include <string>
#include "TextItem.h"
using namespace std;
class Line {
public:
	Line() {}
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