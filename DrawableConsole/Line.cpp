#include "pch.h"
#include "Line.h"
#include <iostream>
#include <windows.h>
using namespace std;
void Line::writeLine()
{
	for (int i = 0; i < m_Line.size(); i++)
	{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_Line[i].getColour());
			cout << m_Line[i].getChar();
	}
	cout << endl;
}

string Line::getCurrentText()
{
	string curText = "";
	for (int i = 0; i < m_Line.size(); i++)
	{
		curText += m_Line[i].getChar();
	}
	return curText;
}


void Line::writeLine(int offsetX)
{
	for (int ii = 0; ii < offsetX; ii++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		cout << " ";
	}
	for (int i = 0; i < m_Line.size(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_Line[i].getColour());
		cout << m_Line[i].getChar();
	}
	cout << endl;
}

void Line::writeLineOptimized(int offsetX)
{
	int LineSize = m_Line.size();
	currentColour = m_Line[0].getColour();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	for (int ii = 0; ii < offsetX; ii++)
	{
		cout << " ";
	}
	int position = 0;
	for (auto& i : m_Line)
	{
		if (position == LineSize - 1)
		{
			currentTxt += i.getChar();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), currentColour);
			cout << currentTxt << endl;
			currentTxt = "";
			return;
		}
		else if (i.getColour() == currentColour)
		{
			currentTxt += i.getChar();
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), currentColour);
			cout << currentTxt;
			currentColour = i.getColour();
			currentTxt = i.getChar();
		}
		position++;
	}

}

void Line::addLine(string a_line, int colour)
{
	vector<TextItem> newLine(m_Line.size() +  a_line.size());
	for (int i = 0; i < m_Line.size(); i++)
	{
		newLine[i] = TextItem(m_Line[i].getChar(), m_Line[i].getColour());
	}
	for (int i = 0; i < a_line.size(); i++)
	{
		newLine[i + m_Line.size()] = TextItem(a_line[i], colour);
	}
	m_Line = newLine;
}

void Line::setLine(string a_line, int colour)
{
	vector<TextItem> newLine(a_line.size());
	for (int i = 0; i < a_line.size(); i++)
	{
		newLine[i] = TextItem(a_line[i], colour);
	}
	m_Line = newLine;
}

void Line::operator=(Line other)
{
	this->m_Line = other.m_Line;
}
