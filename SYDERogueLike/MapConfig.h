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
	virtual ~PathDataObject() {}

	int getPathNo() { return pathNumber; }
	int getSpaceNo() { return spaceNumber; }
	int getMoveTo() { return pathMoveTo; }

private:
	int pathNumber;
	int	spaceNumber;
	int	pathMoveTo;
};

class MapConfigObject
{
public:
	MapConfigObject() {}
	MapConfigObject(std::string filename);
	virtual ~MapConfigObject() {}

	std::vector<PathDataObject> getPathData() { return m_PathData; }

	std::vector<std::string> Split(std::string str, char split);
private:
	std::vector<PathDataObject> m_PathData = std::vector<PathDataObject>();
};