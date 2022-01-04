#pragma once
#include <string>
#include <deque>
#include "ConsoleWindow.h"
#include "SRLPlayer.h"

using namespace std;


class SRLTeam {
public:
	SRLTeam();
	SRLTeam(string name, string homeground) { m_Name = name; m_HomeGround = homeground; }
	SRLTeam(deque<SRLPlayer> a_TeamList, string name, string homeground);
	virtual ~SRLTeam();

	string Interchange(string& summaryPlay);
	/// <summary>
	/// Don't use for regular interchange as it injures the player
	/// </summary>
	/// <param name="playerName"></param>
	/// <returns></returns>
	string SafeInterchange(string playerName, string& summaryPlay);

	void generateJerseys();
	
	int getJerseryType() { return jerseryTypeInt; }
	void setJerseyInt(int newJersey) { jerseryTypeInt = newJersey; }

	int getLogoType() { return logoTypeInt; }
	void setLogoInt(int newLogo) { logoTypeInt = newLogo; }

	ColourClass getPrimary() { return primaryColour; }
	ColourClass getSecondary() { return secondaryColour; }
	ColourClass getBadge() { return badgeColour; }

	SRLPlayer getRandomPlayer();

	SRLPlayer getRandomPlayerAttacker();
	SRLPlayer getRandomPlayerDefender();

	int getRandomPlayerInt() { return rand() % m_TeamList.size(); }

	void clearTeam();
	void setJersey(ColourClass p, ColourClass s, ColourClass b, int JerseyType) { primaryColour = p; secondaryColour = s; badgeColour = b; jerseryTypeInt = JerseyType; }
	void setLogoCustom(string _Logo) { m_CustomLogo = _Logo; }
	string getLogoCustom() { return m_CustomLogo; }
	string getName() { return m_Name; }
	void setHomeGround(string hg) { m_HomeGround = hg; }
	string getHomeGround() { return m_HomeGround; }
	void setName(string name) { m_Name = name; }
	void loadTeam(string path);
	void loadTeamOffContract(string path);
	void saveTeam();
	void saveTeamOffContract();
	
	void swapStartPositionsAndSave(int pos1, int pos2);

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
	void addPlayerLinebreak(string playerName);

	void addPlayerAtk(string playerName,int val);
	void addPlayerDef(string playerName,int val);
	void addPlayerSpd(string playerName,int val);
	void addPlayerHdl(string playerName,int val);
	void addPlayerKck(string playerName,int val);

	void setPlayerInjured(string playerName);
	void setPlayerSent(string playerName, bool sendOff);

	int getPlayerOffCount();

	void addPlayerPenalty(string playerName);
	void addPlayerRuckInfringment(string playerName);
	void addPlayerNoTry(string playerName);

	deque<string> addTimeOnField(int time);

	void addBestPlayers(deque<string> &vec, int amount);

	deque<SRLPlayer> addBestAttackers(deque<string>& vec, int amount);

	SRLPlayer getGoalKicker();
	SRLPlayer getGoalKickerNoLimit();
	int getInterchanges() { return m_Interchanges; }

	deque<SRLPlayer> getPlayers() { return m_TeamList; }

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

	void sortForRepresentativeTeam();

	void AddPlayer(SRLPlayer player) {
		m_TeamList.push_back(player);
	}

	void cutToSeventeen();

private:
	ColourClass getRandomColour();
	string m_Name;
	string m_HomeGround;
	int jerseryTypeInt;
	int logoTypeInt;

	ColourClass primaryColour = WHITE;
	ColourClass secondaryColour = WHITE;
	ColourClass badgeColour = WHITE;

	string m_CustomLogo = "";

	deque<SRLPlayer> m_TeamList = deque<SRLPlayer>();
	int m_Interchanges = 0;

	int averageAttack = 0;
	int averageDefence = 0;
	int averageSpeed = 0;
	int averageKick = 0;
	int averageHandling = 0;
};