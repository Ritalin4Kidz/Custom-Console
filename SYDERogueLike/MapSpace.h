#pragma once
#include "MainMapEnums.h"
#include <string>
#include "Vector2.h"
class MapSpace
{
public:
	MapSpace() {}

	/// <summary>
	/// Create an instance of a mapspace
	/// </summary>
	/// <param name="data"></param>
	/// <param name="spaceType"></param>
	/// <param name="path">route on the map</param>
	/// <param name="space">position in the path</param>
	/// <param name=""></param>
	MapSpace(std::string data, MapSpaceTypes spaceType, int path, int space, Vector2 pos);

	virtual ~MapSpace() {}

	int getPathNumber() { return m_PathNumber; }
	int getSpaceNumber() { return m_SpaceNumber; }

	Vector2 getDrawPos() { return m_DrawPosition; }

	MapSpaceTypes getType() { return m_MapSpaceType; }

private:
	MapSpaceTypes m_MapSpaceType = MST_NormalSpace;
	std::string m_Data = "";

	int m_PathNumber;
	int m_SpaceNumber;
	Vector2 m_DrawPosition;

};