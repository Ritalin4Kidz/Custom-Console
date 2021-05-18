#include "pch.h"
#include "SYDEOldCodeAI.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "ConsoleWindow.h"

using namespace std;
vector<string> Splitter(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	vector<string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

Vector2 SYDEOldCodeAI::bestMove(string board)
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	Vector2 returnVector = Vector2(rand() % 3, rand() % 3);
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line,'\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	bool foundBoardPiece = false;
	for (int i = 0; i < lines.size(); i++)
	{
		vector<string> lineArr = Splitter(lines[i], ';');
		if (board == lineArr[0] + ';' || '\r' + board == lineArr[0] + ';' || '\n' + board == lineArr[0] + ';')
		{
			foundBoardPiece = true;
			string move = lineArr[1];
			if (move != "")
			{
				vector<string> moveArr = Splitter(move, ',');
				returnVector = Vector2( stoi(moveArr[0]) , stoi(moveArr[1]) );
				break;
			}
		}
	}
	if (!foundBoardPiece)
	{
		lines.push_back(board + "\n");
	}
	ofstream moveFile(m_filename);
	for (int i = 0; i < lines.size(); i++)
	{
		moveFile << lines[i];
	}
	return returnVector;
}

bool SYDEOldCodeAI::existingMove(string board, Vector2 move)
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	Vector2 returnVector = Vector2(rand() % 3, rand() % 3);
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line, '\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	bool foundBoardPiece = false;
	for (int i = 0; i < lines.size(); i++)
	{
		vector<string> lineArr = Splitter(lines[i], ';');
		if (board == lineArr[0] + ';' || '\r' + board == lineArr[0] + ';' || '\n' + board == lineArr[0] + ';')
		{
			foundBoardPiece = true;
			if (lineArr[1] != "")
			{
				return true;
			}
		}
	}
	return false;
}

void SYDEOldCodeAI::addWinMove(string board, Vector2 move)
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	Vector2 returnVector = Vector2(rand() % 3, rand() % 3);
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line, '\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	bool foundBoardPiece = false;
	for (int i = 0; i < lines.size(); i++)
	{
		vector<string> lineArr = Splitter(lines[i], ';');
		if (board == lineArr[0] + ';' || '\r' + board == lineArr[0] + ';' || '\n' + board == lineArr[0] + ';')
		{
			foundBoardPiece = true;
			if (lineArr[1] == "")
			{
				lines[i] += to_string(move.getX()) + "," + to_string(move.getY());
			}
		}
	}
	ofstream moveFile(m_filename);
	for (int i = 0; i < lines.size(); i++)
	{
		moveFile << lines[i];
	}
}

vector<string> SYDEOldCodeAI::returnBoard(int index)
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line, '\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	if (index < lines.size())
	{
		vector<string> storage = Splitter(lines[index], ';');
		return Splitter(storage[0], ',');
	}
	else
	{
		return vector<string> {};
	}

}

vector<string> SYDEOldCodeAI::returnWinningMove(int index)
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line, '\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	if (index < lines.size())
	{
		vector<string> storage = Splitter(lines[index], ';');
		if (storage[1] != "")
		{
			return Splitter(storage[1], ',');
		}
		else
		{
			return vector<string> {};
		}
	}
	else
	{
		return vector<string> {};
	}
}

int SYDEOldCodeAI::getBrainSize()
{
	ifstream newFile(m_filename, ios::binary | ios::in);
	string line;
	vector<string> lines;
	int lineNo = 0;
	if (newFile.is_open())
	{
		while (getline(newFile, line, '\r'))
		{
			lineNo++;
			vector<string> temp(lineNo);
			for (int i = 0; i < temp.size() - 1; i++)
			{
				temp[i] = lines[i];
			}
			temp[temp.size() - 1] = line;
			lines = temp;
		}
	}
	return lines.size();
}
