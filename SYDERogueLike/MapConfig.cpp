#include "MapConfig.h"

PathDataObject::PathDataObject(int path, int space, int moveTo)
{
	pathNumber = path;
	spaceNumber = space;
	pathMoveTo = moveTo;
}

MapConfigObject::MapConfigObject(std::string filename)
{
	std::ifstream File(filename, std::ios::binary | std::ios::in);
	if (File.is_open())
	{
		std::string line;
		std::vector<std::string> FileData;
		while (getline(File, line, '\r'))
		{
			line = std::regex_replace(line,
				std::regex("\\r\\n|\\r|\\n"),
				"");
			FileData = Split(line, '=');
			if (FileData.size() <= 0) {
				break;
			}
			if (FileData[0] == "PathData")
			{
				std::vector<std::string> PathDataValues = Split(FileData[1], ',');
				m_PathData.push_back(PathDataObject(std::stoi(PathDataValues[0]), std::stoi(PathDataValues[1]), std::stoi(PathDataValues[2])));
			}
		}
	}
}

int MapConfigObject::getPathNumberToMoveAtPos(int path, int space)
{
	for (int i = 0; i < m_PathData.size(); i++)
	{
		if (m_PathData[i].getPathNo() == path && m_PathData[i].getSpaceNo() == space)
		{
			return m_PathData[i].getMoveTo();
		}
	}
	return 0;
}

std::vector<std::string> MapConfigObject::Split(std::string str, char split)
{
	int arraySize = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == split)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == split)
			{
				splitString[arrayNo] = str.substr(0, i);
				str = str.substr(i + 1, str.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = str;
	return splitString;
}
