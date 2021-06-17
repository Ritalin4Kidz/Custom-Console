#pragma once
#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "SRLNameGenerator.h"
#include "Vector2.h"
#include "SRLGame.h"
#include <iostream>
#include <fstream>
#include <iterator>
enum GameStateSYDE
{
	Unknown_STATE,
	MainMenu_STATE,
	Exhibition_LoadState,
	SeasonConfig_State,
	SeasonModeState,
	LadderViewState,
	ResultsViewState,
	BettingViewState,
	LeaderboardViewState
};

enum GameStateBettingSYDE
{
	CurrentRound_STATE,
	Futures_STATE,
	Account_STATE,
};

enum GameStateLeaderboardSYDE
{
	Tries_State,
	Goals_STATE,
	Points_STATE,
	Metres_State,
	Dally_State
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
};

struct SRLBetPrice
{
	SRLBetPrice(int d, int c) { dollars = d; cents = c; }
	int dollars;
	int cents;
	string ReturnPrice();
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
	SRLBetPrice homeTeamOdds = SRLBetPrice(1,90);
	SRLBetPrice awayTeamOdds = SRLBetPrice(1,90);
	string HomeTeam;
	string AwayTeam;
	vector<string> ResultPlayByPlay;

	int homeTeamScore = 0;
	int awayTeamScore = 0;

	string WinningTeam;
	string LosingTeam;
};

struct SRLRound
{
	SRLRound(vector<SRLGameMatchup> games) { m_Games = games; }
	vector<SRLGameMatchup> m_Games;
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
};

struct SRLSeason
{
	SRLSeason() {}
	SRLSeason(SRLDraw draw, SRLLadder ladder) { m_Draw = draw; m_Ladder = ladder; }
	SRLDraw m_Draw;
	SRLLadder m_Ladder;
	SRLLeaderboard m_TopPlayers;
	SRLLeaderboard m_TopTries;
	SRLLeaderboard m_TopGoals;
	SRLLeaderboard m_TopPoints;
	SRLLeaderboard m_TopMetres;
};

class SRLGame : public SYDEWindowGame {
public:
	SRLGame() { init(); }
	virtual ~SRLGame() {}
	void init();

	vector<SRLPlayer> createRandomTeam(string prefix);
	vector<SRLPlayer> createRandomTeam(string prefix, float multiplier);
	void test();

	SRLTeam generateRandomTeam();
	SRLTeam generateRandomTeam(float multiplier);
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow main_menu_scene(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow exhibition_match_settings(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow season_config_settings(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow season_mode(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow LadderView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow BettingView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow LeaderboardView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ResultsView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow drawTabs(ConsoleWindow window);
	ConsoleWindow drawBetTabs(ConsoleWindow window);
	ConsoleWindow drawLeaderboardTabs(ConsoleWindow window);

	ConsoleWindow configTabs(ConsoleWindow window);

	static AssetsClass astVars;

	void CalculateOdds();

	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) { m_State = newState; }

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight) { return m_State(window, windowWidth, windowHeight); }

	static GameStateSYDE currentState;
	static GameStateSYDE newState;

	static GameStateBettingSYDE bettingState;
	static GameStateLeaderboardSYDE ldrState;

	static bool SeasonStart;

	static bool Simulate;

	static bool NextRoundCall;
	static bool PrevRoundCall;

	static bool addCall;
	static bool removeCall;

	void sortOutResultsScreen();

private:
	SYDEClickableButton m_SeasonModeBtn;
	SYDEClickableButton m_ExhibitionMatchBtn;

	SYDEClickableButton m_BackSeasonCfgBtn;
	SYDEClickableButton m_StartSeasonBtn;
	SYDEClickableButton m_NextTeamSeasonCfgBtn;
	SYDEClickableButton m_PrevTeamSeasonCfgBtn;
	SYDEClickableButton m_AddTeamSeasonCfgBtn;
	SYDEClickableButton m_RemoveTeamSeasonCfgBtn;

	//View Season
	SYDEClickableButton m_SeasonViewBtn;
	//View Ladder
	SYDEClickableButton m_LadderViewBtn;
	//View Betting
	SYDEClickableButton m_BettingViewBtn;
	//View In Depth Results
	SYDEClickableButton m_ResultsViewBtn;
	//View Season Leader
	SYDEClickableButton m_LeaderboardViewBtn;
	//View Main menu
	SYDEClickableButton m_MainMenuViewBtn;

	SYDEClickableButton m_Blank1ViewBtn;

	SYDEClickableButton m_PreviousRoundViewBtn;

	SYDEClickableButton m_NextRoundViewBtn;

	SYDEClickableButton m_SimulateBtn;

	SYDEClickableButton m_BetBtnCurrentRound;
	SYDEClickableButton m_BetBtnFutures;
	SYDEClickableButton m_BetBtnAccount;

	SYDEClickableButton m_LeaderboardBtnMostTries;
	SYDEClickableButton m_LeaderboardBtnMostGoals;
	SYDEClickableButton m_LeaderboardBtnMostMetres;
	SYDEClickableButton m_LeaderboardBtnMostPoints;
	SYDEClickableButton m_LeaderboardBtnMostDallyM;


	vector<string> m_SavedTeams;
	vector<string> m_SeasonTeams;
	int m_SelectedTeam = 0;
	SRLSeason m_Season;

	vector<string> m_ResultsScreenVector;
	int m_LineResults = 0;
	int m_SelectedGame = 0;

	int m_round = 0;
	int m_roundToSimulate = 0;
	bool finals = false;
};