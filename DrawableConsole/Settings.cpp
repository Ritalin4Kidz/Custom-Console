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
		if (FileLines.size() < 5)
		{
			ofstream FileOut(settingsFile);
			FileOut << "OffSetX:" + to_string(xOffset) << endl;
			FileOut << "OffSetY:" + to_string(yOffset) << endl;
			FileOut << "ConsoleSizeHeight:" + to_string(ConsoleSizeHeight) << endl;
			FileOut << "ConsoleSizeWidth:" + to_string(ConsoleSizeWidth);
			FileOut << "Cheats:" + cheats;
		}
		else
		{
			xOffset = stoi(FileLines[0]);
			yOffset = stoi(FileLines[1]);
			ConsoleSizeHeight = stoi(FileLines[2]);
			ConsoleSizeWidth = stoi(FileLines[3]);
			cheats = FileLines[4];
		}
	}
}

vector<string> Settings::ReturnCheats()
{
	return SettingsSplitter(cheats,';');
}

void Settings::volumeControl(int volume)
{
	switch (volume)
	{
	case 0:
		waveOutSetVolume(0, VOLUME_OFF);
		break;
	case 1:
		waveOutSetVolume(0, VOLUME_LOW);
		break;
	case 2:
		waveOutSetVolume(0, VOLUME_NML);
		break;
	case 3:
		waveOutSetVolume(0, VOLUME_MED);
		break;
	case 4:
		waveOutSetVolume(0, VOLUME_HIG);
		break;
	default:
		waveOutSetVolume(0, VOLUME_NML);
		volume = 2;
		break;
	}
}

void Settings::ColourPalette(HANDLE hOut)
{
	CONSOLE_SCREEN_BUFFER_INFOEX pInfo;
	pInfo.cbSize = sizeof(pInfo);
	GetConsoleScreenBufferInfoEx(hOut, &pInfo);
	pInfo.ColorTable[0] = COLORREF(_BLACK.toRGB());
	pInfo.ColorTable[1] = COLORREF(_BLUE.toRGB());
	pInfo.ColorTable[2] = COLORREF(_GREEN.toRGB());
	pInfo.ColorTable[3] = COLORREF(_AQUA.toRGB());
	pInfo.ColorTable[4] = COLORREF(_RED.toRGB());
	pInfo.ColorTable[5] = COLORREF(_PURPLE.toRGB());
	pInfo.ColorTable[6] = COLORREF(_YELLOW.toRGB());
	pInfo.ColorTable[7] = COLORREF(_WHITE.toRGB());
	pInfo.ColorTable[8] = COLORREF(_LIGHTGREY.toRGB());
	pInfo.ColorTable[9] = COLORREF(_DARKBLUE.toRGB());
	pInfo.ColorTable[10] = COLORREF(_BRIGHTGREEN.toRGB());
	pInfo.ColorTable[11] = COLORREF(_LIGHTBLUE.toRGB());
	pInfo.ColorTable[12] = COLORREF(_BRIGHTRED.toRGB());
	pInfo.ColorTable[13] = COLORREF(_LIGHTPURPLE.toRGB());
	pInfo.ColorTable[14] = COLORREF(_BRIGHTYELLOW.toRGB());
	pInfo.ColorTable[15] = COLORREF(_BRIGHTWHITE.toRGB());
	SetConsoleScreenBufferInfoEx(hOut, &pInfo);
}

AdvancedSettings::AdvancedSettings(string settingsFile)
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
		if (FileLines.size() < 5)
		{
			ofstream FileOut(settingsFile);
			FileOut << "OffSetX:" + to_string(xOffset) << endl;
			FileOut << "OffSetY:" + to_string(yOffset) << endl;
			FileOut << "ConsoleSizeHeight:" + to_string(ConsoleSizeHeight) << endl;
			FileOut << "ConsoleSizeWidth:" + to_string(ConsoleSizeWidth);
			FileOut << "Cheats:" + cheats;
		}
		else
		{
			xOffset = stoi(FileLines[0]);
			yOffset = stoi(FileLines[1]);
			ConsoleSizeHeight = stoi(FileLines[2]);
			ConsoleSizeWidth = stoi(FileLines[3]);
			cheats = FileLines[4];
		}
	}
}
