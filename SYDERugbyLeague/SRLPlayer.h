#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "SYDEFileDefaults.h"
#include "ConsoleWindow.h"
using namespace std;
using json = nlohmann::json;
class SRLPlayer {
public:
	SRLPlayer();
	SRLPlayer(string name, string country, int speed, int attack, int defence,int kicking, int goalKicking, int handling);
	SRLPlayer(string name, string country, int speed, int attack, int defence, int kicking, int goalKicking, int handling, ColourClass prim, ColourClass seco, ColourClass tert, int playerStyle);

	virtual ~SRLPlayer();

	bool getPlayerSent() { return m_Sent || m_Sinbin; }
	void setPlayerOff(bool sendOff) { if (sendOff) { m_Sent = true; m_SendOffs++; } else { m_Sinbin = true; m_SinBins++; } }
	string getName() { return m_PlayerName; }
	string getOrigin() { return m_CountryOfOrigin; }
	void setName(string name) { m_PlayerName = name; }
	void setOrigin(string country) { m_CountryOfOrigin = country; }
	int getSpeed() { return m_BaseSpeed; }
	void addSpeed(int spd) { m_BaseSpeed += spd; if (m_BaseSpeed > 99) { m_BaseSpeed = 99; } }

	int getAttack() { return m_BaseAttack; }
	void addAttack(int atk);

	int getDefence() { return m_BaseDefence; }
	void addDefence(int def) { m_BaseDefence += def; if (m_BaseDefence > 99) { m_BaseDefence = 99; } }


	int getKicking() { return m_BaseKicking; }
	void addKicking(int def) { m_BaseKicking += def; if (m_BaseKicking > 99) { m_BaseKicking = 99; } }

	int getRating() { int rating = m_BaseAttack + m_BaseDefence + m_BaseSpeed + m_BaseKicking + m_BaseHandling; return rating / 5; }

	int getHandling() { return m_BaseHandling; }
	void addHandling(int def) { m_BaseHandling += def; if (m_BaseHandling > 99) { m_BaseHandling = 99; } }
	float getStamina() { return m_Stamina / 100; }
	void addStamina(int stamina) { m_Stamina += stamina; }

	int getID() { return id; }
	void setID(int _id) { id = _id; }


	int getGoalKicking() { return m_GoalKicking; }

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

	int getSendOffs() { return m_SendOffs; }
	int getSinBins() { return m_SinBins; }
	int getInjuries() { return m_Injuries; }

	void add4020() { m_4020++; }
	int get4020() { return m_4020; }

	void generateFeatures();

	void addRuckError(){ m_RuckInfringements++; }
	int getRuckErrors() { return m_RuckInfringements; }

	void addPenalty() { m_PenaltiesConceded++; }
	int getPenalty() { return m_PenaltiesConceded; }

	bool comingBack() { return m_ComingBack; }
	void ComingBackOff() { m_ComingBack = false; }

	void setInjured() { m_Injured = true; m_Injuries++; }
	bool getInjured() { return m_Injured; }

	void addNoTry() { m_NoTriesVideoRef++; }
	int getNoTry() { return m_NoTriesVideoRef; }

	ColourClass getPrimary() { return primaryColour; }
	ColourClass getSecondary() { return secondaryColour; }
	ColourClass getTertiary() { return tertiaryColour; }
	int getStyleType() { return playerTypeInt; }

	void addTimeOnField(int time);
	string getTimeOnField();

	void addIntercept() { m_Intercepts++; }
	void addStrip() { m_Strips++; }

	int getSteals() { return m_Intercepts + m_Strips; }

	int getPoints() { return (m_Tries * 4) + (m_Goals * 2) + m_FieldGoals; }

	float getDallyMPointsWorth();
	float getFantasyPointsCalc();
	int getFantasyPoints() { return getFantasyPointsCalc() * 5; }

	string getStatsString() { return "|Time Played: " + getTimeOnField() + " |Metres: " + std::to_string(m_RunMetres) + " |" + "Tackles: " + std::to_string(m_Tackles) + " |" + "Kicks: " + std::to_string(m_Kicks) + " |" + "Kick Metres: " + std::to_string(m_KickMetres) + " |" + "40/20: " + std::to_string(m_4020) + " |" + "Errors: " + std::to_string(m_Errors) + " |" + "Tries: " + std::to_string(m_Tries) + " |" + "Goals: " + std::to_string(m_Goals) + " |" + "Field Goals: " + std::to_string(m_FieldGoals) + " |" + "Total Points: " + std::to_string(getPoints()) + " |" + "Fantasy Points: " + to_string(getFantasyPoints()); }

private:

	string m_PlayerName;
	string m_CountryOfOrigin;
	//HOW FAST THE PLAYER RUNS
	int m_BaseSpeed;
	//GENERAL ATTACKING STAT
	int m_BaseAttack;
	//GENERAL DEFENSIVE STAT
	int m_BaseDefence;
	//GENRRAL GOAL KICKING STAT
	int m_GoalKicking = 0;
	//GENERAL KICKING STAT
	int m_BaseKicking = 0;
	//GENERAL HANDLING STAT
	int m_BaseHandling = 0;

	float m_Stamina = 100;

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
	int m_PenaltiesConceded = 0;
	int m_NoTriesVideoRef = 0;
	int m_RuckInfringements = 0;

	int sinBinTime = 0;

	bool m_Injured = false;
	bool m_Sinbin = false;
	bool m_Sent = false;

	bool m_ComingBack = false;

	int m_Intercepts = 0;
	int m_Strips = 0;

	int m_SinBins = 0;
	int m_SendOffs = 0;
	int m_Injuries = 0;

	int timeOnField = 0;
	ColourClass getRandomColour();
	int playerTypeInt;
	ColourClass primaryColour = WHITE;
	ColourClass secondaryColour = WHITE;
	ColourClass tertiaryColour = WHITE;
};