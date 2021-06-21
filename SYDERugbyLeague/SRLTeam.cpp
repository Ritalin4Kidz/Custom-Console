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
	if (interchange1 >= 13)
	{
		return "";
	}
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

void SRLTeam::addPlayerMetres(string playerName, int metres)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addRunMetres(metres);
			return;
		}
	}
}

void SRLTeam::addPlayerKickMetres(string playerName, int metres)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addKickMetres(metres);
			return;
		}
	}
}

void SRLTeam::addPlayerTry(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addTry();
			return;
		}
	}
}

void SRLTeam::addPlayerGoal(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addGoal();
			return;
		}
	}
}

void SRLTeam::addPlayerFieldGoal(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addFieldGoal();
			return;
		}
	}
}

void SRLTeam::addPlayerError(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addError();
			return;
		}
	}
}

void SRLTeam::addPlayer4020(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].add4020();
			return;
		}
	}
}

void SRLTeam::addPlayerKick(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addKick();
			return;
		}
	}
}

void SRLTeam::addPlayerTackle(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addTackle();
			return;
		}
	}
}

void SRLTeam::addPlayerIntercept(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addIntercept();
			return;
		}
	}
}

void SRLTeam::addPlayerStrip(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addStrip();
			return;
		}
	}
}

void SRLTeam::addPlayerStamina(string playerName, int Stamina)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addStamina(Stamina);
			return;
		}
	}
}

void SRLTeam::addPlayerPenalty(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addPenalty();
			return;
		}
	}
}

void SRLTeam::addPlayerRuckInfringment(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addRuckError();
			return;
		}
	}
}

void SRLTeam::addPlayerNoTry(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].addNoTry();
			return;
		}
	}
}

void SRLTeam::addTimeOnField(int time)
{
	for (int i = 0; i < 13; i++)
	{
		m_TeamList[i].addTimeOnField(time);
	}
}

SRLPlayer SRLTeam::getGoalKicker()
{
	int temp = 0;
	int temp1 = 0;
	for (int i = 0; i < 13; i++)
	{
		if (m_TeamList[i].getGoalKicking() > temp)
		{
			temp = m_TeamList[i].getGoalKicking();
			temp1 = i;
		}
	}
	return m_TeamList[temp1];
}

string SRLTeam::getMostTackles()
{
	int temp = 0;
	string player = "";
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getTackles() > temp)
		{
			temp = m_TeamList[i].getTackles();
			player = m_TeamList[i].getName();
		}
	}
	return player + ": " + to_string(temp);
}

string SRLTeam::getMostMetres()
{
	int temp = 0;
	string player = "";
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getMetres() > temp)
		{
			temp = m_TeamList[i].getMetres();
			player = m_TeamList[i].getName();
		}
	}
	return player + ": " + to_string(temp);
}

string SRLTeam::getMostPoints()
{
	int temp = 0;
	string player = "";
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getPoints() > temp)
		{
			temp = m_TeamList[i].getPoints();
			player = m_TeamList[i].getName();
		}
	}
	return player + ": " + to_string(temp);
}

string SRLTeam::getMostErrors()
{
	int temp = 0;
	string player = "";
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getErrors() > temp)
		{
			temp = m_TeamList[i].getErrors();
			player = m_TeamList[i].getName();
		}
	}
	return player + ": " + to_string(temp);
}

int SRLTeam::totalTries()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getTries();
	}
	return temp;
}

int SRLTeam::totalGoals()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getGoals();
	}
	return temp;
}

int SRLTeam::totalFieldGoals()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getFieldGoals();
	}
	return temp;
}

int SRLTeam::totalTackles()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getTackles();
	}
	return temp;
}

int SRLTeam::totalMetres()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getMetres();
	}
	return temp;
}

int SRLTeam::totalErrors()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getErrors();
	}
	return temp;
}

int SRLTeam::totalKickMetres()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		temp += m_TeamList[i].getKickMetres();
	}
	return temp;
}

int SRLTeam::totalAttackStat()
{
	int total = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		total += m_TeamList[i].getAttack();
	}
	return total;
}

int SRLTeam::totalDefenceStat()
{
	int total = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		total += m_TeamList[i].getDefence();
	}
	return total;
}

int SRLTeam::totalSpeedStat()
{
	int total = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		total += m_TeamList[i].getSpeed();
	}
	return total;
}

int SRLTeam::totalKickStat()
{
	int total = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		total += m_TeamList[i].getKicking();
	}
	return total;
}

int SRLTeam::totalHandlingStat()
{
	int total = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		total += m_TeamList[i].getHandling();
	}
	return total;
}

