#pragma once
#include <string>
#include <vector>
#include "SRLTeam.h"
#include "SRLStatics.h"
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

	void ClearCache() { m_Summary.clear(); m_PlayByPlay.clear(); 
		homeTeamScore = 0; 
		awayTeamScore = 0; 
		m_MinutesPassed = 0; 
		m_SecondsPassed = 0; 
		m_BallPosition = 100;
		m_Tackle = 0;
		m_HomeTeamHasBall = true;
		halfTimeHasPassed = false;
		fullTimeHasPassed = false;
		m_MainGoalKickers = true;
		m_Weather = true;
		m_Stamina = true;
		m_Injuries = false;
		m_sendOffs = true;
		m_ExtraTime = false;
		m_PlayerHasBeenSent = false;
		weather = Weather_Clear;
		weatherAtkErrorBonus = 1;
		weatherDefErrorBonus = 1;
		weatherGoalErrorBonus = 1;
	}

	void addPlay(string a_Play);
	void addPlayNoMinutes(string a_Play);
	void addPlay(string a_Play, SRLPlayer player);
	void addSumary(string a_Play);
	void addSumaryNoMinutes(string a_Play);
	void addSummary(string a_Play, SRLPlayer player);
	void addSummaryDirect(string a_Play);

	void addScoreUniversal(int points);
	void setPositionUniversal(int metresFromGoalLine);
	void addPositionUniversal(int metres);

	int getPositionUniversal(int metres);

	//Get the position of the ball scaled down
	int getBallPosition(int divider) { return m_BallPosition / divider; }

	string getTimeString();

	string getTackle();

	void addMinute();
	void addTimeRandom(int min, int max, bool allowBreak);
	bool addTime(int seconds, bool allowBreak);

	string getTeamInPossession() { if (m_HomeTeamHasBall) { return getHomeTeam().getName(); } return getAwayTeam().getName(); }

	void addSinBinPlays(int seconds);

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
	void setWeather(SRLGameWeather w) { weather = w; }
	void staminaEffect(bool isOn) { m_Stamina = isOn; }
	void injuriesEffect(bool isOn) { m_Injuries = isOn; }
	void sinBinsEffect(bool isOn) { m_sendOffs = isOn; }

	bool doVideoRef(SRLPlayer defender, SRLPlayer attacker, SRLTeam& defendingTeam, SRLTeam& attackingTeam);


	void extraTimeEffect(bool isOn) { m_ExtraTime = isOn; }

	bool rollBasicChance(int baseChance, int failureChance);

	SRLPlayer getRandomSafe(SRLTeam team);

	bool checkError(SRLPlayer defender, SRLPlayer attacker);
	int checkKick(SRLPlayer defender, SRLPlayer attacker);
	int doKick(SRLPlayer defender, SRLPlayer attacker);
	bool doRegularMovement(SRLPlayer defender, SRLPlayer attacker);
	bool doRegularMovementPlay(SRLPlayer defender, SRLPlayer attacker, SRLTeam& defendingTeam, SRLTeam& attackingTeam);
	bool checkIntercept(SRLPlayer& defender, SRLPlayer& attacker);
	int checkStrip(SRLPlayer defender, SRLPlayer attacker);
	int checkOffload(SRLPlayer defender, SRLPlayer attacker);
	bool doFieldGoal(SRLPlayer defender, SRLPlayer attacker);
	bool doTry(SRLPlayer defender, SRLPlayer attacker);

	bool doFieldGoalAttempt(SRLPlayer attacker, SRLTeam& attackingTeam, SRLTeam& defendingTeam);

	void doInnovation(SRLPlayer attacker, SRLTeam& attackingTeam);
	void doChipAndChase(SRLPlayer attacker, SRLTeam& attackingTeam, int execution);

	bool addTry(SRLTeam& m_AttackingTeam, SRLTeam& m_DefendingTeam, SRLPlayer attacker);

	bool doInjury(SRLPlayer defender, SRLPlayer attacker, bool homeTeam);
	bool getPlayerWasSentInGame() { return m_PlayerHasBeenSent; }
	bool doSendOff(SRLPlayer defender, SRLPlayer attacker, bool homeTeam, bool sendOff);

	void addAttackerErrorStats(string PlayerName, int StaminaLoss);

	void doPenalty(SRLPlayer defender, SRLPlayer attacker);

	void changeOver(bool error);

	int getMinutesPassed() { return m_MinutesPassed; }

	vector<string> getPlayByPlay() { return m_PlayByPlay; }
	vector<string> getSummary() { return m_Summary; }

	void saveSettings();

private:
	//CONSTANTS
	const int defaultAttackErrorChance = SRLStatics::loadConstSetting("defaultAttackErrorChance", 90);
	const int defaultDefenceErrorChance = SRLStatics::loadConstSetting("defaultDefenceErrorChance", 90);
	const int defaultStealChance = SRLStatics::loadConstSetting("defaultStealChance", 160);
	const int defaultGoalChance = SRLStatics::loadConstSetting("defaultGoalChance", 90);
	const int secondaryErrorChance = SRLStatics::loadConstSetting("secondaryErrorChance", 19);
	const int conversionErrorChance = SRLStatics::loadConstSetting("conversionErrorChance", 3);
	const int secondaryStripChance = SRLStatics::loadConstSetting("secondaryStripChance", 10);
	const int defaultEarlyKickChance = SRLStatics::loadConstSetting("defaultEarlyKickChance", 15);
	const int fortytwentyChance = SRLStatics::loadConstSetting("fortytwentyChance", 18);
	const int tryVideoRefChance = SRLStatics::loadConstSetting("tryVideoRefChance", 4);
	const int tryErrorChance = SRLStatics::loadConstSetting("tryErrorChance", 18);
	const int incorrectPlayTheBallChance = SRLStatics::loadConstSetting("incorrectPlayTheBallChance", 1000);
	const int tryInfringementChance = SRLStatics::loadConstSetting("tryInfringementChance", 160);
	const int minTimeSecondSkip = SRLStatics::loadConstSetting("minTimeSecondSkip", 11);
	const int maxTimeSecondSkip = SRLStatics::loadConstSetting("maxTimeSecondSkip", 19);
	const int outOnFullErrorChance = SRLStatics::loadConstSetting("outOnFullErrorChance", 35);
	const int injuryChance = SRLStatics::loadConstSetting("injuryChance", 17500);
	const int professionalFoulChance = SRLStatics::loadConstSetting("professionalFoulChance", 3);
	const float playerSentDivision = 0.8f;
	const int offloadChance = SRLStatics::loadConstSetting("offloadChance", 30);
	const int videoRefAutoSucceedChance = SRLStatics::loadConstSetting("videoRefAutoSucceedChance", 50);
	const int InnovationSucceedChance = SRLStatics::loadConstSetting("InnovationSucceedChance", 60);
	const int kickOutOnTheFullChance = SRLStatics::loadConstSetting("kickOutOnTheFullChance", 1000);
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

	bool m_PlayerHasBeenSent = false;

	//WEATHER BONUSES
	SRLGameWeather weather = Weather_Clear;
	float weatherAtkErrorBonus = 1;
	float weatherDefErrorBonus = 1;
	float weatherGoalErrorBonus = 1;
};