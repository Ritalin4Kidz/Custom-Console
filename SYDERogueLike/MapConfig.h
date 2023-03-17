#pragma once
#include <vector>
#include "json.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
using json = nlohmann::json;
class PathDataObject
{
public:
	PathDataObject() {}
	PathDataObject(int path, int space, int moveTo);

	int getPathNo() { return pathNumber; }
	int getSpaceNo() { return spaceNumber; }
	int getMoveTo() { return pathMoveTo; }

private:
	int pathNumber;
	int	spaceNumber;
	int	pathMoveTo;
};

class BossDataObject
{
public:
	BossDataObject() {}
	BossDataObject(int path, int space, int bossTag);

	int getPathNo() { return pathNumber; }
	int getSpaceNo() { return spaceNumber; }
	int getbossTagNo() { return bossTagNumber; }

private:
	int pathNumber;
	int	spaceNumber;
	int	bossTagNumber;
};

class MapConfigObject
{
public:
	MapConfigObject() {}
	MapConfigObject(std::string filename);

	std::vector<PathDataObject> getPathData() { return m_PathData; }

	int getPathNumberToMoveAtPos(int path, int space);

	int getBossTagAtPos(int path, int space);

	std::vector<std::string> Split(std::string str, char split);
private:
	std::vector<PathDataObject> m_PathData = std::vector<PathDataObject>();
	std::vector<BossDataObject> m_BossData = std::vector<BossDataObject>();
};