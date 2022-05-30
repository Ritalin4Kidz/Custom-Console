#include "MapPath.h"

void MapPath::orderSpaceArray()
{
	//TODO:
	//ORDER THE ARRAY BY POSITION OF THE MAP SPACE
	for (int i = 0; i < m_Spaces.size(); i++)
	{
		for (int ii = 0; ii < i; ii++)
		{
			if (m_Spaces[i].getSpaceNumber() < m_Spaces[ii].getSpaceNumber())
			{
				std::iter_swap(m_Spaces.begin() + i, m_Spaces.begin() + ii);
				i = 0;
			}
		}
	}
}
