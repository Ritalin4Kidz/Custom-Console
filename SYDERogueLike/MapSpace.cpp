#include "MapSpace.h"

MapSpace::MapSpace(std::string data, MapSpaceTypes spaceType, int path, int space, Vector2 pos)
{
	m_Data = data;
	m_MapSpaceType = spaceType;
	m_PathNumber = path;
	m_SpaceNumber = space;
	m_DrawPosition = pos;
}
