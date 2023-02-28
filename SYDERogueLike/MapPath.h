#pragma once
#include "MapSpace.h"
#include <vector>

class MapPath
{
public:
	MapPath() {}
	MapPath(int id) { m_PathID = id; }

	void addSpace(MapSpace a_Space) { m_Spaces.push_back(a_Space); }
	
	int getID() { return m_PathID; }

	int getSize() { return m_Spaces.size(); }

	MapSpace getElement(int i) { return m_Spaces[i]; }

	void orderSpaceArray();
private:
	std::vector<MapSpace> m_Spaces = std::vector<MapSpace>();
	int m_PathID;
};