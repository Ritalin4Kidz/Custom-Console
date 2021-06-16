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
	void addPlay(string a_Play, SRLPlayer player);

	void setTeams(SRLTeam team1, SRLTeam team2) { m_HomeTeam = team1; m_AwayTeam = team2; }

	bool isTied() { return homeTeamScore == awayTeamScore; }

	void addStartTimePlay();
	void addFullTimePlay();

	void endStats();

	void play();

	bool checkError(SRLPlayer defender, SRLPlayer attacker);
	void doRegularMovement(SRLPlayer defender, SRLPlayer attacker);
	bool checkIntercept(SRLPlayer defender, SRLPlayer attacker);
	bool checkStrip(SRLPlayer defender, SRLPlayer attacker);
	bool doFieldGoal(SRLPlayer defender, SRLPlayer attacker);
	bool doTry(SRLPlayer defender, SRLPlayer attacker);

	void changeOver(bool error);

	int getMinutesPassed() { return m_MinutesPassed; }

	vector<string> getPlayByPlay() { return m_PlayByPlay; }

private:

	SRLTeam m_HomeTeam;
	SRLTeam m_AwayTeam;

	const int defaultErrorChance = 120;
	const int defaultStealChance = 150;
	const int defaultGoalChance = 95;
	const int secondaryErrorChance = 7;
	const int conversionErrorChance = 3;

	const int timeSecondSkip = 16;

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