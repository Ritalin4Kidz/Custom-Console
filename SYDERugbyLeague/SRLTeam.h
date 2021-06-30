#pragma once
#include <string>
#include <vector>
#include "ConsoleWindow.h"
#include "SRLPlayer.h"

using namespace std;


class SRLTeam {
public:
	SRLTeam();
	SRLTeam(string name) {m_Name= name;}
	SRLTeam(vector<SRLPlayer> a_TeamList, string name);
	virtual ~SRLTeam();

	string Interchange();
	/// <summary>
	/// Don't use for regular interchange as it injures the player
	/// </summary>
	/// <param name="playerName"></param>
	/// <returns></returns>
	string SafeInterchange(string playerName);

	void generateJerseys();
	
	int getJerseryType() { return jerseryTypeInt; }

	ColourClass getPrimary() { return primaryColour; }
	ColourClass getSecondary() { return secondaryColour; }
	ColourClass getBadge() { return badgeColour; }

	SRLPlayer getRandomPlayer();
	int getRandomPlayerInt() { return rand() % m_TeamList.size(); }

	void clearTeam();
	void setJersey(ColourClass p, ColourClass s, ColourClass b, int JerseyType) { primaryColour = p; secondaryColour = s; badgeColour = b; jerseryTypeInt = JerseyType; }
	string getName() { return m_Name; }
	void setName(string name) { m_Name = name; }
	void loadTeam(string path);
	void loadTeamOffContract(string path);
	void saveTeam();
	void saveTeamOffContract();

	void addPlayerMetres(string playerName, int metres);
	void addPlayerKickMetres(string playerName, int metres);

	void addPlayerTry(string playerName);
	void addPlayerGoal(string playerName);
	void addPlayerFieldGoal(string playerName);
	void addPlayerError(string playerName);
	void addPlayer4020(string playerName);
	void addPlayerKick(string playerName);
	void addPlayerTackle(string playerName);
	void addPlayerIntercept(string playerName);
	void addPlayerStrip(string playerName);
	void addPlayerStamina(string playerName, int Stamina);

	void setPlayerInjured(string playerName);
	void setPlayerSent(string playerName, bool sendOff);

	int getPlayerOffCount();

	void addPlayerPenalty(string playerName);
	void addPlayerRuckInfringment(string playerName);
	void addPlayerNoTry(string playerName);

	vector<string> addTimeOnField(int time);

	SRLPlayer getGoalKicker();
	SRLPlayer getGoalKickerNoLimit();
	int getInterchanges() { return m_Interchanges; }

	vector<SRLPlayer> getPlayers() { return m_TeamList; }

	void setPlayer(int index, SRLPlayer p) { m_TeamList[index] = p; }

	string getMostTackles();
	string getMostMetres();
	string getMostPoints();
	string getMostErrors();

	int totalTries();
	int totalGoals();
	int totalFieldGoals();
	int totalTackles();
	int totalMetres();
	int totalErrors();
	int totalKickMetres();


	int totalAttackStat();
	int totalDefenceStat();
	int totalSpeedStat();
	int totalKickStat();
	int totalHandlingStat();

	void CalculateAverages();

	void CalculateAverageAttackStat();
	void CalculateAverageDefenceStat();
	void CalculateAverageSpeedStat();
	void CalculateAverageKickStat();
	void CalculateAverageHandlingStat();

	int averageAttackStat() { return averageAttack; }
	int averageDefenceStat() { return averageDefence; }
	int averageSpeedStat() { return averageSpeed; }
	int averageKickStat() { return averageKick; }
	int averageHandlingStat() { return averageHandling; }

	int TeamRating();

private:
	ColourClass getRandomColour();
	string m_Name;

	int jerseryTypeInt;

	ColourClass primaryColour = WHITE;
	ColourClass secondaryColour = WHITE;
	ColourClass badgeColour = WHITE;

	vector<SRLPlayer> m_TeamList = vector<SRLPlayer>();
	int m_Interchanges = 0;

	int averageAttack = 0;
	int averageDefence = 0;
	int averageSpeed = 0;
	int averageKick = 0;
	int averageHandling = 0;
};