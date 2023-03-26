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
			else if (FileData[0] == "BossData")
			{
				std::vector<std::string> PathDataValues = Split(FileData[1], ',');
				m_BossData.push_back(BossDataObject(std::stoi(PathDataValues[0]), std::stoi(PathDataValues[1]), std::stoi(PathDataValues[2])));
			}
			else if (FileData[0] == "ForcedChangePathData")
			{
				std::vector<std::string> PathDataValues = Split(FileData[1], ',');
				m_ForcedPathData.push_back(ForcedPathDataObject(Vector2(std::stoi(PathDataValues[0]), std::stoi(PathDataValues[1])), Vector2(std::stoi(PathDataValues[2]), std::stoi(PathDataValues[3]))));
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

Vector2 MapConfigObject::getForcedPathNumberToMoveAtPos(int path, int space)
{
	for (int i = 0; i < m_ForcedPathData.size(); i++)
	{
		if (m_ForcedPathData[i].getSpaceNo().getX() == path && m_ForcedPathData[i].getSpaceNo().getY() == space)
		{
			return m_ForcedPathData[i].getMoveTo();
		}
	}
	return 0;
}

int MapConfigObject::getBossTagAtPos(int path, int space)
{
	for (int i = 0; i < m_BossData.size(); i++)
	{
		if (m_BossData[i].getPathNo() == path && m_BossData[i].getSpaceNo() == space)
		{
			return m_BossData[i].getbossTagNo();
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

BossDataObject::BossDataObject(int path, int space, int bossTag)
{
	pathNumber = path;
	spaceNumber = space;
	bossTagNumber = bossTag;
}

ForcedPathDataObject::ForcedPathDataObject(Vector2 space, Vector2 moveTo)
{
	spacePos = space;
	spacePosMoveTo = moveTo;
}
