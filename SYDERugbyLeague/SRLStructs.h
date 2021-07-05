#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "SRLNameGenerator.h"
#include "SRLNewsStoryGenerator.h"
#include "SRLCustomTeams.h"
#include "SYDESounds.h"
#include "SRLSoundtrack.h"
#include "Vector2.h"
#include "SRLGame.h"
#include <iostream>
#include <fstream>
#include <iterator>
enum FinalsSeriesType
{
	Top8Normal,
	Top4Normal,
	Top2Normal,
	Top8Knockout,
	Top4Knockout,
	Top8DoubleElim,
	KnockoutTournament,
	KnockoutTournamentDouble,
};

struct FinalsSeries
{
	FinalsSeries() {}
	FinalsSeries(string str, FinalsSeriesType type, int r, int no) { FinalsStr = str; fsType = type; rounds = r; noTeams = no; }
	string FinalsStr;
	FinalsSeriesType fsType;
	int rounds;
	int noTeams;
};

struct SRLBetPrice
{
	SRLBetPrice() {}
	SRLBetPrice(int d, int c) { dollars = d; cents = c; }
	int dollars;
	int cents;

	bool suspended = false;

	void addCents(int c);
	void addBetPrice(SRLBetPrice bet);

	void removeBetPrice(SRLBetPrice bet);
	bool equal(SRLBetPrice bet) { return dollars == bet.dollars && cents == bet.cents; }
	bool greaterThan(SRLBetPrice bet);
	bool lessThan(SRLBetPrice bet);

	void absolute();

	int getAsCents() { return (dollars * 100) + cents; }

	string ReturnPrice();
};

struct SRLLadderPosition
{
	string teamName = "";
	int played = 0;
	int won = 0;
	int lost = 0;
	int points = 0;
	int pointsFor = 0;
	int pointsAgainst = 0;
	int pointsDifference = 0;
	SRLBetPrice premiershipOdds = SRLBetPrice(5, 0);
};

enum SRLBetType
{
	BetType_Game,
	BetType_Premiership,
	BetType_Try,
};

enum SRLBetTag
{
	Bet_Lost,
	Bet_Won,
	Bet_InProgress
};

struct SRLGameBet
{
	SRLGameBet() {}
	SRLGameBet(string teamName, SRLBetPrice odds, SRLBetPrice amountBet) { m_teamName = teamName; betOdds = odds; betAmount = amountBet; originalBetAmount = betAmount; }
	SRLGameBet(string teamName, SRLBetPrice odds, SRLBetPrice amountBet, SRLBetType bet) { m_teamName = teamName; betOdds = odds; betAmount = amountBet; _BetType = bet; originalBetAmount = betAmount; }
	SRLBetPrice betOdds;
	SRLBetPrice betAmount;
	SRLBetPrice originalBetAmount;
	SRLBetType _BetType = BetType_Game;
	SRLBetPrice ReturnBetWinnings();
	SRLBetTag betState = Bet_InProgress;
	string m_teamName;
};

struct SRLLadder
{
	SRLLadder() {}
	SRLLadder(vector<SRLLadderPosition> ladder) { m_Ladder = ladder; }
	void sortLadder();
	vector<SRLLadderPosition> m_Ladder;
};

struct SRLGameMatchup
{
	SRLGameMatchup(string homeTeam, string awayTeam) { HomeTeam = homeTeam; AwayTeam = awayTeam; }
	SRLBetPrice homeTeamOdds = SRLBetPrice(1, 90);
	SRLBetPrice awayTeamOdds = SRLBetPrice(1, 90);
	string HomeTeam;
	string AwayTeam;
	vector<string> ResultPlayByPlay;
	vector<string> SummaryPlayByPlay;

	vector<SRLBetPrice> homeTeamTryOdds = vector<SRLBetPrice>();
	vector<SRLBetPrice> awayTeamTryOdds = vector<SRLBetPrice>();

	int homeTeamScore = 0;
	int awayTeamScore = 0;

	bool tiedGame = false;

	string WinningTeam;
	string LosingTeam;
};

struct SRLGameBetsWriting
{
	string name;
	ColourClass colour;
};

struct FeaturedGame
{
	FeaturedGame() {}
	FeaturedGame(string home, string away, AssetsClass astVars, int gameNo, SRLBetPrice homeOdds, SRLBetPrice awayOdds);
	bool featuredGameAvail = false;
	int fg_homeTeamScore = 0;
	int fg_awayTeamScore = 0;
	int gameNumber = 0;
	SRLTeam fg_homeTeam;
	CustomAsset fg_homeTeamJersey;
	SRLTeam fg_awayTeam;
	CustomAsset fg_awayTeamJersey;

	SRLBetPrice fg_homeOdds;
	SRLBetPrice fg_awayOdds;

	vector<string> homeTeamKeyPlayers;
	vector<string> awayTeamKeyPlayers;

	vector<string> MatchHistory = vector<string>({ "No Match History To Show" });
};

struct SRLRound
{
	SRLRound(vector<SRLGameMatchup> games) { m_Games = games; }
	vector<SRLGameMatchup> m_Games;
	vector<SRLGameBet> m_Bets;
	vector<SRLGameBet> m_TryScorerBets;
	vector<SRLNewsArticle> newsStories;
	FeaturedGame gameToFeature;
};

struct SRLDraw
{
	SRLDraw() {}
	SRLDraw(vector<SRLRound> rounds) { m_Rounds = rounds; }
	vector<SRLRound> m_Rounds;
};

struct SRLLeaderboardPosition
{
	string Player;
	string TeamName;
	int points;
};

struct SRLLeaderboard
{
	void addToShortlist(string playerName, string teamName, int points);
	vector<SRLLeaderboardPosition> shortlist;
	void orderShortlist();

	void changePlayerTeam(string playerName, string oldTeam, string newTeam);
};

struct SRLSeason
{
	SRLSeason() {}
	SRLSeason(SRLDraw draw, SRLLadder ladder) { m_Draw = draw; m_Ladder = ladder; }
	SRLDraw m_Draw;
	vector<SRLGameBet> m_PremiershipBets;
	SRLLadder m_Ladder;
	SRLLeaderboard m_TopPlayers;
	SRLLeaderboard m_TopTries;
	SRLLeaderboard m_TopGoals;
	SRLLeaderboard m_TopPoints;
	SRLLeaderboard m_TopMetres;
	SRLLeaderboard m_TopFieldGoals;
	SRLLeaderboard m_TopTackles;
	SRLLeaderboard m_Top4020;
	SRLLeaderboard m_TopKickMetres;
	SRLLeaderboard m_TopSteals;
	SRLLeaderboard m_TopErrors;
	SRLLeaderboard m_TopPenalty;
	SRLLeaderboard m_TopRuckErrors;
	SRLLeaderboard m_TopNoTries;

	SRLLeaderboard m_TopSinBin;
	SRLLeaderboard m_TopSendOff;
	SRLLeaderboard m_TopInjuries;
};

enum GameSummaryTextType
{
	GSTType_Error = 0,
	GSTType_Points = 1,
	GSTType_Penalty = 2,
	GSTType_Sent = 3,
	GSTType_Interchange_Injury = 4,
};

struct GameSummaryText
{
	GameSummaryText(string t, string p, string player, string s);
	ConsoleWindow draw(ConsoleWindow window, Vector2 point);
	string Time;
	string Play;
	string Player;
	string ScoreText;
	GameSummaryTextType summaryTextType;
};

enum SRLTrainingType
{
	Training_Attack = 0,
	Training_Defence,
	Training_Speed,
	Training_Kick,
	Training_Handling,
};

struct SRLTrainingOption
{
	SRLTrainingOption(string p, int i, SRLTrainingType t) { player = p; playerID = i; training = t; _price = SRLBetPrice(((rand() % 9) + 1) * 10, 0); }
	ConsoleWindow draw(ConsoleWindow window, Vector2 point);
	SRLBetPrice _price;
	string player;
	int playerID;
	SRLTrainingType training;
};

struct SRLTradingOption
{
	SRLTradingOption(string p1, int i1, string p2, int i2, string otherTeam) { player1 = p1; playerID1 = i1; player2 = p2; playerID2 = i2; OtherTeam = otherTeam; }
	ConsoleWindow draw(ConsoleWindow window, Vector2 point);
	string player1;
	int playerID1;
	string player2;
	int playerID2;
	string OtherTeam;
};