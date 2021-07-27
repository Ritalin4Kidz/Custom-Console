#include "SRLPlayer.h"

SRLPlayer::SRLPlayer()
{
}

SRLPlayer::SRLPlayer(string name, string country, int speed, int attack, int defence,int kicking, int goalKicking, int handling)
{
	m_PlayerName = name;
	m_CountryOfOrigin = country;
	m_BaseSpeed = speed;
	m_BaseAttack = attack;
	m_BaseDefence = defence;
	m_BaseKicking = kicking;
	m_GoalKicking = goalKicking;
	m_BaseHandling = handling;
	generateFeatures();
}

SRLPlayer::SRLPlayer(string name, string country, int speed, int attack, int defence, int kicking, int goalKicking, int handling, ColourClass prim, ColourClass seco, ColourClass tert, int playerStyle)
{
	m_PlayerName = name;
	m_CountryOfOrigin = country;
	m_BaseSpeed = speed;
	m_BaseAttack = attack;
	m_BaseDefence = defence;
	m_BaseKicking = kicking;
	m_GoalKicking = goalKicking;
	m_BaseHandling = handling;
	primaryColour = prim;
	secondaryColour = seco;
	tertiaryColour = tert;
	playerTypeInt = playerStyle;
}

SRLPlayer::~SRLPlayer()
{
}

void SRLPlayer::addAttack(int atk)
{
	m_BaseAttack += atk; 
	if (m_BaseAttack > 99) 
	{
		m_BaseAttack = 99; 
	}
}

void SRLPlayer::affectAllStats(float mul)
{
	float mf_BaseAttack = (float)m_BaseAttack; 
	float mf_BaseDefence = (float)m_BaseDefence;
	float mf_BaseHandling = (float)m_BaseHandling;
	float mf_BaseSpeed = (float)m_BaseSpeed;
	float mf_BaseKicking = (float)m_BaseKicking;
	mf_BaseAttack *= mul;
	mf_BaseDefence *= mul;
	mf_BaseHandling *= mul;
	mf_BaseSpeed *= mul;
	mf_BaseKicking *= mul;
	m_BaseAttack = mf_BaseAttack;
	m_BaseDefence = mf_BaseDefence;
	m_BaseHandling = mf_BaseHandling;
	m_BaseSpeed = mf_BaseSpeed;
	m_BaseKicking = mf_BaseKicking;
}

void SRLPlayer::loadPlayer(string path)
{
	std::ifstream ifs{ path };
	json save_file = json::parse(ifs);
	this->m_BaseAttack = (save_file["atk"]);
	setName(save_file["name"]);
	setOrigin(save_file["origin"]);
	this->m_BaseDefence = (save_file["def"]);
	this->m_BaseSpeed = (save_file["spd"]);
	this->id = (save_file["id"]);
	this->m_GoalKicking = (save_file["goalkick"]);
	this->m_BaseKicking = (save_file["kick"]);
	this->m_BaseHandling = (save_file["hand"]);
	this->primaryColour = static_cast<ColourClass>(save_file["primary"]);
	this->secondaryColour = static_cast<ColourClass>(save_file["secondary"]);
	this->tertiaryColour = static_cast<ColourClass>(save_file["tertiary"]);
	this->playerTypeInt = save_file["playertype"];
}

void SRLPlayer::savePlayer()
{
	json save_file;
	//PlayerStats
	save_file["name"] = m_PlayerName;
	save_file["origin"] = m_CountryOfOrigin;
	save_file["atk"] = m_BaseAttack;
	save_file["def"] = m_BaseDefence;
	save_file["spd"] = m_BaseSpeed;
	save_file["kick"] = m_BaseKicking;
	save_file["goalkick"] = m_GoalKicking;
	save_file["hand"] = m_BaseHandling;
	save_file["playertype"] = playerTypeInt;
	save_file["primary"] = static_cast<int>(primaryColour);
	save_file["secondary"] = static_cast<int>(secondaryColour);
	save_file["tertiary"] = static_cast<int>(tertiaryColour);
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

void SRLPlayer::generateFeatures()
{
	int noPlayers = SYDEFileDefaults::getFileCount("EngineFiles\\PlayerFeatures", ".bmp");
	playerTypeInt = rand() % noPlayers;

	primaryColour = getRandomColour();
	secondaryColour = getRandomColour();
	while (primaryColour == secondaryColour)
	{
		secondaryColour = getRandomColour();
	}
	tertiaryColour = getRandomColour();
	while (tertiaryColour == primaryColour || tertiaryColour == secondaryColour)
	{
		tertiaryColour = getRandomColour();
	}
}

void SRLPlayer::addTimeOnField(int time)
{
	if (m_Sent)
	{
		return;
	}
	if (m_Sinbin)
	{
		sinBinTime += time;
		if (sinBinTime > 600)
		{
			sinBinTime = 0;
			m_Sinbin = false;
			m_ComingBack = true;
		}
		return;
	}
	timeOnField += time;
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
	weight = weight / (m_Errors + m_RuckInfringements +m_PenaltiesConceded + 1 + (m_SinBins*2));
	weight = weight / 10;

	if (m_SendOffs > 0)
	{
		weight = 0;
	}

	return weight;
}

float SRLPlayer::getFantasyPointsCalc()
{
		float weight = 0;
		weight = (m_RunMetres/2) + (m_Tackles * 2) + (m_KickMetres/3) + (m_4020 * 10) + (m_Tries * 8) + (m_Goals) + (m_FieldGoals *3);
		weight += (m_Strips * 3) + (m_Intercepts * 3);
		weight = weight / (m_Errors + m_RuckInfringements + m_PenaltiesConceded + 1 + (m_SinBins * 2));
		weight = weight / 6;

		if (m_SendOffs > 0)
		{
			weight = 0;
		}
		return weight;
}

ColourClass SRLPlayer::getRandomColour()
{
	int colour = rand() % 13;
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
			return LIGHTPURPLE_LIGHTPURPLE_BG;
		case 12:
			return BRIGHTYELLOW_BRIGHTYELLOW_BG;
		}
	}
}
