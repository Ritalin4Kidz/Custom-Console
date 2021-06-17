#include "SRLPlayer.h"

SRLPlayer::SRLPlayer()
{
}

SRLPlayer::SRLPlayer(string name, int speed, int attack, int defence)
{
	m_PlayerName = name;
	m_BaseSpeed = speed;
	m_BaseAttack = attack;
	m_BaseDefence = defence;
}

SRLPlayer::~SRLPlayer()
{
}

void SRLPlayer::loadPlayer(string path)
{
	std::ifstream ifs{ path };
	json save_file = json::parse(ifs);
	this->m_BaseAttack = (save_file["atk"]);
	setName(save_file["name"]);
	this->m_BaseDefence = (save_file["def"]);
	this->m_BaseSpeed = (save_file["spd"]);
	this->id = (save_file["id"]);
}

void SRLPlayer::savePlayer()
{
	json save_file;
	//PlayerStats
	save_file["name"] = m_PlayerName;
	save_file["spd"] = m_BaseAttack;
	save_file["def"] = m_BaseDefence;
	save_file["atk"] = m_BaseSpeed;

	if (id == 0)
	{
		id++;
		while (true)
		{
			string filePath = string("EngineFiles\\GameResults\\Players\\" + to_string(id) + ".json");
			if (!SYDEFileDefaults::exists(filePath.c_str()))
			{
				save_file["id"] = id;
				std::ofstream ofs(filePath.c_str());
				ofs << save_file;
				return;
				//return save_file;
			}
			id++;
		}
	}
	save_file["id"] = id;
	string filePath = string("EngineFiles\\GameResults\\Players\\" + to_string(id) + ".json");
	std::ofstream ofs(filePath);
	ofs << save_file;
	//return save_file;
	//std::ofstream ofs("EngineFiles\\Settings\\MOTS_SaveFile.sc");
	//ofs << save_file;
}

string SRLPlayer::getTimeOnField()
{
	int minutes = 0;
	int timePassed = timeOnField;
	while (timePassed > 59)
	{
		minutes++;
		timePassed -= 60;
	}
	string minutesStr = to_string(minutes);
	if (minutesStr.length() == 1)
	{
		minutesStr = "0" + minutesStr;
	}
	string secondsStr = to_string(timePassed);
	if (secondsStr.length() == 1)
	{
		secondsStr = "0" + secondsStr;
	}
	return minutesStr + ":" + secondsStr;
}

float SRLPlayer::getDallyMPointsWorth()
{
	float weight = 0;
	weight = m_RunMetres + (m_Tackles * 2) + m_KickMetres + (m_4020*10) + (getPoints() * 10);
	weight += (m_Strips * 3) + (m_Intercepts * 3);
	weight = weight / (m_Errors + 1);
	weight = weight / 10;

	return weight;
}
