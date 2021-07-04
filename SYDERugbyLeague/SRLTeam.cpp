#include "SRLTeam.h"

SRLTeam::SRLTeam()
{
}

SRLTeam::SRLTeam(vector<SRLPlayer> a_TeamList, string name)
{
	m_TeamList = a_TeamList;
	m_Name = name;
	generateJerseys();
}

SRLTeam::~SRLTeam()
{
}

string SRLTeam::Interchange(string& summaryPlay)
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
	if (m_TeamList[interchange1].getPlayerSent())
	{
		return "";
	}
	if (m_TeamList[interchange2].getInjured())
	{
		return "";
	}
	string swap = getName() + " Interchanged Players " + m_TeamList[interchange1].getName() + " & " + m_TeamList[interchange2].getName();
	summaryPlay = m_TeamList[interchange1].getName() + "#INTERCHANGE#" + m_TeamList[interchange2].getName();
	iter_swap(m_TeamList.begin() + interchange1,m_TeamList.begin() + interchange2);
	m_Interchanges++;
	return swap;
}

string SRLTeam::SafeInterchange(string playerName, string& summaryPlay)
{
	if (m_Interchanges >= 8)
	{
		return "";
	}
	int Interchange1 = -1;
	for (int i = 0; i < 13; i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			Interchange1 = i;
		}
	}
	if (m_TeamList[Interchange1].getPlayerSent())
	{
		return "";
	}
	if (Interchange1 == -1)
	{
		return "";
	}
	for (int i = 13; i < m_TeamList.size(); i++)
	{
		if (!m_TeamList[i].getInjured())
		{
			m_TeamList[i].setInjured();
			string swap = getName() + " Interchanged Players " + m_TeamList[Interchange1].getName() + " & " + m_TeamList[i].getName();
			summaryPlay = m_TeamList[Interchange1].getName() + "#INTERCHANGE#" + m_TeamList[i].getName();
			iter_swap(m_TeamList.begin() + Interchange1, m_TeamList.begin() + i);
			m_Interchanges++;
			return swap;
		}
	}
	return "";
}

void SRLTeam::generateJerseys()
{
	int noJerseys = SYDEFileDefaults::getFileCount("EngineFiles\\JerseyFeatures", ".bmp");
	jerseryTypeInt = rand() % noJerseys;

	primaryColour = getRandomColour();
	secondaryColour = getRandomColour();
	while (primaryColour == secondaryColour)
	{
		secondaryColour = getRandomColour();
	}
	badgeColour = getRandomColour();
	while (badgeColour == primaryColour || badgeColour == secondaryColour)
	{
		badgeColour = getRandomColour();
	}
}

SRLPlayer SRLTeam::getRandomPlayer()
{
	int player = rand() % 13;
	return m_TeamList[player];
}

void SRLTeam::clearTeam()
{
	m_TeamList.clear();
	m_Name = "";
}

void SRLTeam::loadTeam(string path)
{
	std::ifstream ifs{ path };
	json save_file = json::parse(ifs);
	setName(save_file["name"]);
	primaryColour = static_cast<ColourClass>(save_file["primary"]);
	secondaryColour = static_cast<ColourClass>(save_file["secondary"]);
	badgeColour = static_cast<ColourClass>(save_file["badge"]);
	jerseryTypeInt = save_file["jerseytype"];
	int numberOfPlayers = save_file["playeramt"];
	for (int i = 0; i < numberOfPlayers; i++)
	{
		int playerID = save_file["players"][to_string(i)];
		SRLPlayer newPlayer = SRLPlayer();
		string filePath = string("EngineFiles\\GameResults\\Players\\" + to_string(playerID) + ".json");
		newPlayer.loadPlayer(filePath);
		m_TeamList.push_back(newPlayer);
	}
}

void SRLTeam::loadTeamOffContract(string path)
{
	std::ifstream ifs{ path };
	json save_file = json::parse(ifs);
	setName(save_file["name"]);
	int numberOfPlayers = save_file["playeramt"];
	for (int i = 0; i < numberOfPlayers; i++)
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
	save_file["jerseytype"] = jerseryTypeInt;
	save_file["primary"] = static_cast<int>(primaryColour);
	save_file["secondary"] = static_cast<int>(secondaryColour);
	save_file["badge"] = static_cast<int>(badgeColour);
	save_file["playeramt"] = m_TeamList.size();
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		m_TeamList[i].savePlayer();
		save_file["players"][to_string(i)] = m_TeamList[i].getID();
	}
	string filePath = string("EngineFiles\\GameResults\\Teams\\" + m_Name + ".json");
	std::ofstream ofs(filePath);
	ofs << save_file;
	//return save_file;
}

void SRLTeam::saveTeamOffContract()
{
	json save_file;
	//PlayerStats
	save_file["name"] = m_Name;
	save_file["playeramt"] = m_TeamList.size();
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		m_TeamList[i].savePlayer();
		save_file["players"][to_string(i)] = m_TeamList[i].getID();
	}
	string filePath = string("EngineFiles\\GameResults\\OffContract\\" + m_Name + ".json");
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

void SRLTeam::setPlayerInjured(string playerName)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].setInjured();
			return;
		}
	}
}

void SRLTeam::setPlayerSent(string playerName, bool sendOff)
{
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getName() == playerName)
		{
			m_TeamList[i].setPlayerOff(sendOff);
			return;
		}
	}
}

int SRLTeam::getPlayerOffCount()
{
	int temp = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
	{
		if (m_TeamList[i].getPlayerSent())
		{
			temp++;
		}
	}
	return temp;
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

vector<string> SRLTeam::addTimeOnField(int time)
{
	vector<string> temp;
	for (int i = 0; i < 13; i++)
	{
		m_TeamList[i].addTimeOnField(time);
		if (m_TeamList[i].comingBack())
		{
			temp.push_back("SIN BIN RETURN - " + m_TeamList[i].getName());
			m_TeamList[i].ComingBackOff();
		}
	}
	return temp;
}

void SRLTeam::addBestPlayers(vector<string>& vec, int amount)
{
	vector<SRLPlayer> temp = getPlayers();
	for (int i = 0; i < temp.size(); i++)
	{
		for (int ii = i + 1; ii < temp.size(); ii++)
		{
			if (temp[ii].getRating() > temp[i].getRating())
			{
				SRLPlayer temp2 = temp[ii];
				temp[ii] = temp[i];
				temp[i] = temp2;
				i = 0;
				break;
			}
		}
	}
	for (int i = 0; i < amount; i++)
	{
		vec.push_back(temp[i].getName());
	}
}

vector<SRLPlayer> SRLTeam::addBestAttackers(vector<string>& vec, int amount)
{
	vector<SRLPlayer> temp = getPlayers();
	for (int i = 0; i < temp.size(); i++)
	{
		for (int ii = i + 1; ii < temp.size(); ii++)
		{
			if (temp[ii].getAttack() > temp[i].getAttack())
			{
				SRLPlayer temp2 = temp[ii];
				temp[ii] = temp[i];
				temp[i] = temp2;
				i = 0;
				break;
			}
		}
	}
	for (int i = 0; i < amount; i++)
	{
		vec.push_back(temp[i].getName());
	}
	return temp;
}

SRLPlayer SRLTeam::getGoalKicker()
{
	int temp = 0;
	int temp1 = 0;
	for (int i = 0; i < 13; i++)
	{
		if (m_TeamList[i].getGoalKicking() > temp && m_TeamList[i].getPlayerSent() == false)
		{
			temp = m_TeamList[i].getGoalKicking();
			temp1 = i;
		}
	}
	return m_TeamList[temp1];
}

SRLPlayer SRLTeam::getGoalKickerNoLimit()
{
	int temp = 0;
	int temp1 = 0;
	for (int i = 0; i < m_TeamList.size(); i++)
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

void SRLTeam::CalculateAverages()
{
	CalculateAverageAttackStat();
	CalculateAverageDefenceStat();
	CalculateAverageSpeedStat();
	CalculateAverageKickStat();
	CalculateAverageHandlingStat();
}

void SRLTeam::CalculateAverageAttackStat()
{
	averageAttack = totalAttackStat() / m_TeamList.size();
}

void SRLTeam::CalculateAverageDefenceStat()
{
	averageDefence = totalDefenceStat() / m_TeamList.size();
}

void SRLTeam::CalculateAverageSpeedStat()
{
	averageSpeed = totalSpeedStat() / m_TeamList.size();
}

void SRLTeam::CalculateAverageKickStat()
{
	averageKick = totalKickStat() / m_TeamList.size();
}

void SRLTeam::CalculateAverageHandlingStat()
{
	averageHandling = totalHandlingStat() / m_TeamList.size();
}

int SRLTeam::TeamRating()
{
	int rating = averageAttackStat() + averageDefenceStat() + averageSpeedStat() + averageKickStat() + averageHandlingStat();
	return rating/5;
}

ColourClass SRLTeam::getRandomColour()
{
	int colour = rand() % 15;
	{
		switch (colour)
		{
		case 0:
			return BLUE_BLUE_BG;
		case 1:
			return GREEN_GREEN_BG;
		case 2:
			return AQUA_AQUA_BG;
		case 3:
			return RED_RED_BG;
		case 4:
			return PURPLE_PURPLE_BG;
		case 5:
			return YELLOW_YELLOW_BG;
		case 6:
			return WHITE_WHITE_BG;
		case 7:
			return LIGHTGREY_LIGHTGREY_BG;
		case 8:
			return DARKBLUE_DARKBLUE_BG;
		case 9:
			return BRIGHTGREEN_BRIGHTGREEN_BG;
		case 10:
			return LIGHTBLUE_LIGHTBLUE_BG;
		case 11:
			return BRIGHTRED_BRIGHTRED_BG;
		case 12:
			return LIGHTPURPLE_LIGHTPURPLE_BG;
		case 13:
			return BRIGHTYELLOW_BRIGHTYELLOW_BG;
		case 14:
			return BRIGHTWHITE_BRIGHTWHITE_BG;
		}
	}
}

