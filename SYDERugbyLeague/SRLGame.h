#pragma once
#include <string>
#include <vector>
#include "SRLTeam.h"

#include "Vector2.h"

using namespace std;


class SRLGameManager {
public:
	SRLGameManager();

	virtual ~SRLGameManager();

	void addPlay(string a_Play);
	void addPlayNoMinutes(string a_Play);
	void addPlay(string a_Play, SRLPlayer player);

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

	bool checkError(SRLPlayer defender, SRLPlayer attacker);
	int checkKick(SRLPlayer defender, SRLPlayer attacker);
	int doKick(SRLPlayer defender, SRLPlayer attacker);
	void doRegularMovement(SRLPlayer defender, SRLPlayer attacker);
	bool checkIntercept(SRLPlayer defender, SRLPlayer attacker);
	int checkStrip(SRLPlayer defender, SRLPlayer attacker);
	bool doFieldGoal(SRLPlayer defender, SRLPlayer attacker);
	bool doTry(SRLPlayer defender, SRLPlayer attacker);

	void doPenalty(SRLPlayer defender, SRLPlayer attacker);

	void changeOver(bool error);

	int getMinutesPassed() { return m_MinutesPassed; }

	vector<string> getPlayByPlay() { return m_PlayByPlay; }

private:

	SRLTeam m_HomeTeam;
	SRLTeam m_AwayTeam;
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
	const int tryErrorChance = 13;

	const int minTimeSecondSkip = 11;
	const int maxTimeSecondSkip = 19;

	int homeTeamScore;
	int awayTeamScore;

	int m_SecondsPassed;
	int m_MinutesPassed;

	vector<string> m_PlayByPlay;
	
	int m_BallPosition = 100;

	int m_Tackle = 0;
	bool m_HomeTeamHasBall = true;

	bool halfTimeHasPassed = false;
};