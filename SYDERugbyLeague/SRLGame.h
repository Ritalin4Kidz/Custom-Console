#pragma once
#include <string>
#include <vector>
#include "SRLTeam.h"

#include "Vector2.h"

using namespace std;

enum SRLGameWeather
{
	Weather_Clear,
	Weather_Cloudy,
	Weather_Humid,
	Weather_Rain,
	Weather_Windy,
	Weather_Hail,
	Weather_Storm,
	Weather_Sunny,
	Weather_Heatwave,
	Weather_Snow,
};

class SRLGameManager {
public:
	SRLGameManager();

	virtual ~SRLGameManager();

	void addPlay(string a_Play);
	void addPlayNoMinutes(string a_Play);
	void addPlay(string a_Play, SRLPlayer player);
	void addSumary(string a_Play);
	void addSumaryNoMinutes(string a_Play);
	void addSummary(string a_Play, SRLPlayer player);

	void addMinute();

	void generateWeather();

	SRLTeam getHomeTeam() { return m_HomeTeam; }
	SRLTeam getAwayTeam() { return m_AwayTeam; }
	void setTeams(SRLTeam team1, SRLTeam team2) { m_HomeTeam = team1; m_AwayTeam = team2; }

	bool isTied() { return homeTeamScore == awayTeamScore; }

	int getHomeScore() { return homeTeamScore; }
	int getAwayScore() { return awayTeamScore; }

	int fromRand(int range);

	void addTeamLineupsPlayByPlay();

	void addStartTimePlay();
	void addFullTimePlay();

	void endStats();

	void play();

	void teamHaveMainGoalKickers(bool isOn) { m_MainGoalKickers = isOn; }
	void weatherEffects(bool isOn) { m_Weather = isOn; }
	void staminaEffect(bool isOn) { m_Stamina = isOn; }
	void injuriesEffect(bool isOn) { m_Injuries = isOn; }
	void sinBinsEffect(bool isOn) { m_sendOffs = isOn; }

	void extraTimeEffect(bool isOn) { m_ExtraTime = isOn; }

	SRLPlayer getRandomSafe(SRLTeam team);

	bool checkError(SRLPlayer defender, SRLPlayer attacker);
	int checkKick(SRLPlayer defender, SRLPlayer attacker);
	int doKick(SRLPlayer defender, SRLPlayer attacker);
	bool doRegularMovement(SRLPlayer defender, SRLPlayer attacker);
	bool checkIntercept(SRLPlayer defender, SRLPlayer attacker);
	int checkStrip(SRLPlayer defender, SRLPlayer attacker);
	bool doFieldGoal(SRLPlayer defender, SRLPlayer attacker);
	bool doTry(SRLPlayer defender, SRLPlayer attacker);

	bool doInjury(SRLPlayer defender, SRLPlayer attacker, bool homeTeam);

	bool doSendOff(SRLPlayer defender, SRLPlayer attacker, bool homeTeam, bool sendOff);

	void addAttackerErrorStats(string PlayerName, int StaminaLoss);

	void doPenalty(SRLPlayer defender, SRLPlayer attacker);

	void changeOver(bool error);

	int getMinutesPassed() { return m_MinutesPassed; }

	vector<string> getPlayByPlay() { return m_PlayByPlay; }
	vector<string> getSummary() { return m_Summary; }

private:
	//CONSTANTS
	const int defaultAttackErrorChance = 90;
	const int defaultDefenceErrorChance = 90;
	const int defaultStealChance = 160;
	const int defaultGoalChance = 90;
	const int secondaryErrorChance = 19;
	const int conversionErrorChance = 3;
	const int secondaryStripChance = 10;
	const int defaultEarlyKickChance = 15;
	const int fortytwentyChance = 18;
	const int tryVideoRefChance = 4;
	const int tryErrorChance = 18;
	const int incorrectPlayTheBallChance = 1000;
	const int tryInfringementChance = 200;
	const int minTimeSecondSkip = 11;
	const int maxTimeSecondSkip = 19;
	const int outOnFullErrorChance = 35;
	const int injuryChance = 1000;
	const int professionalFoulChance = 3;
	//SCORE
	SRLTeam m_HomeTeam;
	SRLTeam m_AwayTeam;
	int homeTeamScore;
	int awayTeamScore;
	//TIME
	int m_SecondsPassed;
	int m_MinutesPassed;
	//PLAYS
	vector<string> m_PlayByPlay;
	vector<string> m_Summary;
	//GAMEPLAY
	int m_BallPosition = 100;
	int m_Tackle = 0;
	bool m_HomeTeamHasBall = true;
	bool halfTimeHasPassed = false;
	bool fullTimeHasPassed = false;

	bool m_MainGoalKickers = true;
	bool m_Weather = true;
	bool m_Stamina = true;
	bool m_Injuries = false;
	bool m_sendOffs = true;

	bool m_ExtraTime = false;

	//WEATHER BONUSES
	SRLGameWeather weather = Weather_Clear;
	float weatherAtkErrorBonus = 1;
	float weatherDefErrorBonus = 1;
	float weatherGoalErrorBonus = 1;
};