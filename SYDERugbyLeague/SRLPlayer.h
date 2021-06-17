#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "SYDEFileDefaults.h"
using namespace std;
using json = nlohmann::json;
class SRLPlayer {
public:
	SRLPlayer();
	SRLPlayer(string name, int speed, int attack, int defence);


	virtual ~SRLPlayer();


	string getName() { return m_PlayerName; }
	void setName(string name) { m_PlayerName = name; }
	int getSpeed() { return m_BaseSpeed; }

	int getAttack() { return m_BaseAttack; }

	int getDefence() { return m_BaseDefence; }

	int getID() { return id; }

	void loadPlayer(string path);
	void savePlayer();

	void addRunMetres(int metres) { m_RunMetres += metres; }
	int getMetres() { return m_RunMetres; }

	void addTackle() { m_Tackles++; }
	int getTackles() { return m_Tackles; }

	void addTry() { m_Tries++; }
	int getTries() { return m_Tries; }

	void addGoal() { m_Goals++; }
	int getGoals() { return m_Goals; }

	void addFieldGoal() { m_FieldGoals++; }
	int getFieldGoals() { return m_FieldGoals; }

	void addKick() { m_Kicks++; }
	int getKicks() { return m_Kicks; }

	void addKickMetres(int metres) { m_KickMetres += metres; }
	int getKickMetres() { return m_KickMetres; }

	void addError() { m_Errors++; }
	int getErrors() { return m_Errors; }

	void add4020() { m_4020++; }
	int get4020() { return m_4020; }

	void addTimeOnField(int time) { timeOnField += time; }
	string getTimeOnField();

	void addIntercept() { m_Intercepts++; }
	void addStrip() { m_Strips++; }

	int getPoints() { return (m_Tries * 4) + (m_Goals * 2) + m_FieldGoals; }

	float getDallyMPointsWorth();
	int getFantasyPoints() { return getDallyMPointsWorth() * 5; }

	string getStatsString() { return "|Time Played: " + getTimeOnField() + " |Metres: " + std::to_string(m_RunMetres) + " |" + "Tackles: " + std::to_string(m_Tackles) + " |" + "Kicks: " + std::to_string(m_Kicks) + " |" + "Kick Metres: " + std::to_string(m_KickMetres) + " |" + "40/20: " + std::to_string(m_4020) + " |" + "Errors: " + std::to_string(m_Errors) + " |" + "Tries: " + std::to_string(m_Tries) + " |" + "Goals: " + std::to_string(m_Goals) + " |" + "Field Goals: " + std::to_string(m_FieldGoals) + " |" + "Total Points: " + std::to_string(getPoints()) + " |" + "Fantasy Points: " + to_string(getFantasyPoints()); }

private:

	string m_PlayerName;
	//HOW FAST THE PLAYER RUNS
	int m_BaseSpeed;
	//GENERAL ATTACKING STAT
	int m_BaseAttack;
	//GENERAL DEFENSIVE STAT
	int m_BaseDefence;

	int id = 0;

	///GAME STATS
	int m_RunMetres = 0;
	int m_KickMetres = 0;
	int m_Tries = 0;
	int m_Goals = 0;
	int m_FieldGoals = 0;
	int m_Kicks = 0;
	int m_Errors = 0;
	int m_4020 = 0;
	int m_Tackles = 0;

	int m_Intercepts = 0;
	int m_Strips = 0;

	int timeOnField = 0;
};