#pragma once
#include "MapSpace.h"
#include <vector>

class MapPath
{
public:
	MapPath() {}
	MapPath(int id) { m_PathID = id; }
	virtual ~MapPath() {}

	void addSpace(MapSpace a_Space) { m_Spaces.push_back(a_Space); }

	void orderSpaceArray();
private:
	std::vector<MapSpace> m_Spaces = std::vector<MapSpace>();
	int m_PathID;
};