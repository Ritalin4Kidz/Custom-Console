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

void SRLTeam::loadTeam(string path)
{
	std::ifstream ifs{ path };
	json save_file = json::parse(ifs);
	setName(save_file["name"]);
	for (int i = 0; i < 17; i++)
	{
		int playerID = save_file["players"][to_string(i)];
		SRLPlayer newPlayer = SRLPlayer();
		string filePath = string("EngineFiles\\GameResults\\Players\\" + to_string(playerID) + ".json");
		newPlayer.loadPlayer(filePath);
		m_TeamList.push_back(newPlayer);
	}
}

void SRLTeam::saveTeam()
{
	json save_file;
	//PlayerStats
	save_file["name"] = m_Name;
	for (int i = 0; i < 17; i++)
	{
		m_TeamList[i].savePlayer();
		save_file["players"][to_string(i)] = m_TeamList[i].getID();
	}
	string filePath = string("EngineFiles\\GameResults\\Teams\\" + m_Name + ".json");
	std::ofstream ofs(filePath);
	ofs << save_file;
	//return save_file;
}
