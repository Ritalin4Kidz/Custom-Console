#include "pch.h"
#include "Settings.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
vector<string> SettingsSplitter(string a_String, char splitter)
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
Settings::Settings(string settingsFile)
{
	ifstream File(settingsFile, ios::binary | ios::in);
	if (File.is_open())
	{
		string line;
		vector<string> FileLines;
		while (getline(File, line, '\r'))
		{
			FileLines.push_back(SettingsSplitter(line, ':')[1]);
		}
		if (FileLines.size() != 2)
		{
			ofstream FileOut(settingsFile);
			FileOut << "OffSetX:" + to_string(xOffset) << endl;
			FileOut << "OffSetY:" + to_string(yOffset);
		}
		else
		{
			xOffset = stoi(FileLines[0]);
			yOffset = stoi(FileLines[1]);
		}
	}
}
