#include "SRLTeam.h"

SRLTeam::SRLTeam()
{
}

SRLTeam::SRLTeam(vector<SRLPlayer> a_TeamList, string name)
{
	m_TeamList = a_TeamList;
	m_Name = name;
}

SRLTeam::~SRLTeam()
{
}

string SRLTeam::Interchange()
{
	if (m_Interchanges >= 8)
	{
		return "";
	}
	int interchange1 = rand() % m_TeamList.size();
	int interchange2 = (rand() % 4) + 13;
	if (interchange1 >= 17 || interchange2 >= 17)
	{
		return "";
	}
	if (interchange1 == interchange2)
	{
		return "";
	}
	string swap = getName() + " Interchanged Players " + m_TeamList[interchange1].getName() + " & " + m_TeamList[interchange2].getName();
	iter_swap(m_TeamList.begin() + interchange1,m_TeamList.begin() + interchange2);
	m_Interchanges++;
	return swap;
}

SRLPlayer SRLTeam::getRandomPlayer()
{
	int player = rand() % 13;
	return m_TeamList[player];
}
