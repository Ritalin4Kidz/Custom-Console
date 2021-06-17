#pragma once
#include <string>
#include <vector>

#include "SRLPlayer.h"

using namespace std;


class SRLTeam {
public:
	SRLTeam();
	SRLTeam(string name) {m_Name= name;}
	SRLTeam(vector<SRLPlayer> a_TeamList, string name);
	virtual ~SRLTeam();

	string Interchange();

	SRLPlayer getRandomPlayer();

	string getName() { return m_Name; }
	void setName(string name) { m_Name = name; }
	void loadTeam(string path);
	void saveTeam();

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

	void addTimeOnField(int time);

	int getInterchanges() { return m_Interchanges; }

	vector<SRLPlayer> getPlayers() { return m_TeamList; }

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

private:

	string m_Name;

	vector<SRLPlayer> m_TeamList = vector<SRLPlayer>();
	int m_Interchanges = 0;
};