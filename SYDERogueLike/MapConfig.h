#pragma once
#include <vector>
#include "json.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Vector2.h"
#include <regex>
using json = nlohmann::json;
class ForcedPathDataObject
{
public:
	ForcedPathDataObject() {}
	ForcedPathDataObject(Vector2 space, Vector2 moveTo);

	Vector2 getSpaceNo() { return spacePos; }
	Vector2 getMoveTo() { return spacePosMoveTo; }

private:
	Vector2 spacePos;
	Vector2 spacePosMoveTo;
};

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

class FinalSpaceDataObject
{
public:
	FinalSpaceDataObject() {}
	FinalSpaceDataObject(int path, int space);

	int getPathNo() { return pathNumber; }
	int getSpaceNo() { return spaceNumber; }

private:
	int pathNumber;
	int	spaceNumber;
};

class MapConfigObject
{
public:
	MapConfigObject() {}
	MapConfigObject(std::string filename);

	std::vector<PathDataObject> getPathData() { return m_PathData; }

	int getPathNumberToMoveAtPos(int path, int space);

	Vector2 getForcedPathNumberToMoveAtPos(int path, int space);

	int getBossTagAtPos(int path, int space);

	std::vector<std::string> Split(std::string str, char split);
private:
	std::vector<PathDataObject> m_PathData = std::vector<PathDataObject>();
	std::vector<BossDataObject> m_BossData = std::vector<BossDataObject>();
	std::vector<ForcedPathDataObject> m_ForcedPathData = std::vector<ForcedPathDataObject>();
	std::vector<FinalSpaceDataObject> m_FinalSpaceData = std::vector<FinalSpaceDataObject>();
};