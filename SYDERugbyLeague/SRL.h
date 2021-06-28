#pragma once
#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "SRLNameGenerator.h"
#include "SRLNewsStoryGenerator.h"
#include "SYDESounds.h"
#include "Vector2.h"
#include "SRLGame.h"
#include <iostream>
#include <fstream>
#include <iterator>
#pragma region states

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
	LeaderboardViewState,
	SettingsState,
	InformationState,
	NewsViewState,
	TeamInDepthViewState,
};

enum GameStateInDepthView
{
	NormalInDepthView,
	TeamListViewState,
	PlayerViewState
};

enum ArticleViewingState
{
	HeadlinesState,
	ArticleFullViewState
};

enum GameStateBettingSYDE
{
	CurrentRound_STATE,
	Futures_STATE,
	ViewBets_STATE,
	Account_STATE
};

enum GameStateResultSYDE
{
	Summary_STATE,
	PlayByPlay_STATE
};

enum GameStateSettingsSYDE
{
	SeasonSettings_STATE,
	NormalSettings_STATE
};

enum GameStateLeaderboardSYDE
{
	Tries_State,
	Goals_STATE,
	Points_STATE,
	Metres_State,
	Dally_State,
	State_4020,
	Tackles_State,
	FG_State,
	KickMetres_State,
	Steals_State,
	ErrorsLdr_State,
	Penalty_State,
	RuckError_State,
	NoTry_State,
	Injury_State,
	SendOff_State,
	SinBin_State
};

enum SRLSeasonLength
{
	Length_ShortSeason = 10,
	Length_MediumSeason = 20,
	Length_NormalSeason = 26,
	Length_LongSeason = 40,
	Length_ExtremeSeason = 66,
	Length_EnduranceSeason = 100
};

enum SRLBetTag
{
	Bet_Lost,
	Bet_Won,
	Bet_InProgress
};

enum SRLPriorBets_State
{
	IndividualGameBets_State,
	PremiershipWinnerBets_State
};

#pragma endregion

enum FinalsSeriesType
{
	Top8Normal,
	Top4Normal,
	Top2Normal,
	Top8Knockout,
	Top4Knockout,
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

struct SRLGameBet
{
	SRLGameBet() {}
	SRLGameBet(string teamName, SRLBetPrice odds, SRLBetPrice amountBet) { m_teamName = teamName; betOdds = odds; betAmount = amountBet; originalBetAmount = betAmount; }
	SRLGameBet(string teamName, SRLBetPrice odds, SRLBetPrice amountBet, bool bet) { m_teamName = teamName; betOdds = odds; betAmount = amountBet; premiershipBet = bet; originalBetAmount = betAmount;}
	SRLBetPrice betOdds;
	SRLBetPrice betAmount;
	SRLBetPrice originalBetAmount;
	bool premiershipBet = false;
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
	SRLBetPrice homeTeamOdds = SRLBetPrice(1,90);
	SRLBetPrice awayTeamOdds = SRLBetPrice(1,90);
	string HomeTeam;
	string AwayTeam;
	vector<string> ResultPlayByPlay;
	vector<string> SummaryPlayByPlay;

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

enum SRLArticleType
{
	SRLAT_Premiership,
	SRLAT_PlayerTrade,
	SRLAT_PlayerSign,
	SRLAT_Normal,
	SRLAT_DropPlayer,
};

struct SRLNewsArticle
{
	SRLNewsArticle() {}
	string headline;
	vector<string> newsStory;
	CustomAsset newsPicture;
	SRLArticleType type = SRLAT_Normal;
};

struct SRLRound
{
	SRLRound(vector<SRLGameMatchup> games) { m_Games = games; }
	vector<SRLGameMatchup> m_Games;
	vector<SRLGameBet> m_Bets;
	vector<SRLNewsArticle> newsStories;
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

class SRLGame : public SYDEWindowGame {
public:
	SRLGame() { init(); }
	virtual ~SRLGame() {}
	void init();

	vector<SRLPlayer> createRandomTeam(string prefix);
	vector<SRLPlayer> createOffSeasonTeam(string prefix);
	vector<SRLPlayer> createRandomTeam(string prefix, float multiplier);
	void test();
	static AssetsClass astVars;
	SRLTeam generateRandomTeam();
	SRLTeam generateOffSeasonTeam();
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

	ConsoleWindow TeamInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow TeamInDepthListView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow PlayerInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow LeaderboardPositions(ConsoleWindow window, vector<SRLLeaderboardPosition> ldrboard);

	void LeaderboardOutputStrings(vector<string> &mainVec, vector<SRLLeaderboardPosition> ldrboard);


	ConsoleWindow SettingsView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow NewsView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow InfoView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow SimulatePopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow FormatPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ExitPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow RandomizePopUp(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow drawTabs(ConsoleWindow window);
	ConsoleWindow drawBetTabs(ConsoleWindow window);
	ConsoleWindow drawLeaderboardTabs(ConsoleWindow window);
	ConsoleWindow drawMainMenuTabs(ConsoleWindow window);
	ConsoleWindow drawResultTabs(ConsoleWindow window);

	ConsoleWindow configTabs(ConsoleWindow window);

	ConsoleWindow KeypadPop_Up(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow ErrorPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ExportPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow BetPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ConfirmPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	void CalculateOdds();
	void CalculatePremiershipOdds();
	void SimulateGames();

	static void saveGameSettings();
	static void loadGameSettings();

	void sortOutNews();
	void checkSpecificBetAchievements(SRLGameBet _bet);
	void checkBetAchievements();
	void offContractTrade();
	void offContractTrade(int team1, int player1);
	void TeamTrade();
	void UpdateBets();

	void setUpTeamInDepthView(int teamViewing);

	void setUpPlayer();

	void otherArticles();

	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) { m_State = newState; }

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight) { return m_State(window, windowWidth, windowHeight); }

	static GameStateSYDE currentState;
	static GameStateSYDE newState;
	static void addCustomStrString(string charAdd);
	static void removeCustomStrString();
	static GameStateBettingSYDE bettingState;
	static GameStateLeaderboardSYDE ldrState;
	static GameStateResultSYDE resultState;
	static GameStateInDepthView inDepthState;
	static GameStateSettingsSYDE settingsState;
	static SRLPriorBets_State priorBetsState;
	static ArticleViewingState articleState;

	static SRLSeasonLength seasonLength;

	static bool SeasonStart;

	static bool Simulate;
	static bool SimulateCall;

	static bool NextRoundCall;
	static bool PrevRoundCall;

	static bool headlineCall;

	static bool addCall;
	static bool removeCall;
	static bool generateCall;

	static bool errorCall;
	static bool menuCall;
	static bool exportCall;
	static bool exportConfirmedCall;
	static bool formatCall;
	static bool formatConfirmedCall;
	static bool exitCall;
	static bool exitConfirmedCall;
	static bool randomizeCall;
	static bool randomizeConfirmedCall;

	static bool m_GoalKicker;
	static bool m_Weather;
	static bool m_Stamina;
	static bool m_ExtraTime;
	static bool m_Injuries;
	static bool m_SinBins;
	static bool m_SeasonEvents;


	static SYDESoundtrack m_GamePlaySoundtrack;
	static bool soundTrackOn;
	static bool m_ResultsTabCall;

	static SRLBetPrice m_BetAmount;

	static string errorMessage;

	static string customAmountStr;

	static bool randomFillCall;

	static string betTag;
	static bool betCall;
	static bool betPlaceCall;
	static bool homeTeamBet;
	static bool premiershipBet;
	static bool keyPadCall;
	static int gameNumberBet;

	static int articleClicked;

	static int priorBetNumberLine;
	void sortOutResultsScreen();

	static vector<string> AchievementStrings;

	static int playerClicked;
	static bool playerCall;
	static bool finalsSystemCall;
private:
	SYDEClickableButton m_StartSeasonBtn;
	SYDEClickableButton m_NextTeamSeasonCfgBtn;
	SYDEClickableButton m_PrevTeamSeasonCfgBtn;
	SYDEClickableButton m_AddTeamSeasonCfgBtn;
	SYDEClickableButton m_RemoveTeamSeasonCfgBtn;
	SYDEClickableButton m_GenerateTeamSeasonCfgBtn;
	SYDEClickableButton m_RandomFillSeasonCfgBtn;

	//View Season
	SYDEClickableButton m_ErrorOkViewBtn;

	//View Season
	SYDEClickableButton m_MenuOkViewBtn;
	SYDEClickableButton m_MenuCnclViewBtn;

	//View Season
	SYDEClickableButton m_BetOkViewBtn;
	SYDEClickableButton m_BetCnclViewBtn;

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

	SYDEClickableButton m_NewsViewBtn;

	SYDEClickableButton m_PreviousRoundViewBtn;

	SYDEClickableButton m_NextRoundViewBtn;

	SYDEClickableButton m_SimulateBtn;

	SYDEClickableButton m_BetBtnCurrentRound;
	SYDEClickableButton m_BetBtnViewBets;
	SYDEClickableButton m_BetBtnFutures;
	SYDEClickableButton m_BetBtnAccount;

	SYDEClickableButton m_LeaderboardBtnMostTries;
	SYDEClickableButton m_LeaderboardBtnMostGoals;
	SYDEClickableButton m_LeaderboardBtnMostMetres;
	SYDEClickableButton m_LeaderboardBtnMostPoints;
	SYDEClickableButton m_LeaderboardBtnMostDallyM;

	SYDEClickableButton m_LeaderboardBtnMostFieldGoals;
	SYDEClickableButton m_LeaderboardBtnMostTackles;
	SYDEClickableButton m_LeaderboardBtnMostKickMetres;
	SYDEClickableButton m_LeaderboardBtnMost4020;
	SYDEClickableButton m_LeaderboardBtnMostSteals;

	SYDEClickableButton m_LeaderboardBtnMostErrors;
	SYDEClickableButton m_LeaderboardBtnMostPenalties;
	SYDEClickableButton m_LeaderboardBtnMostNoTries;
	SYDEClickableButton m_LeaderboardBtnMostRuckErrors;

	SYDEClickableButton m_LeaderboardBtnMostSinBin;
	SYDEClickableButton m_LeaderboardBtnMostSendOff;
	SYDEClickableButton m_LeaderboardBtnMostInjuries;

	SYDEClickableButton m_BackSeasonCfgBtn;
	SYDEClickableButton m_SeasonCfgBtn;
	SYDEClickableButton m_GameSettingsBtn;
	SYDEClickableButton m_GameInfoBtn;

	SYDEClickableButton m_SoundTrackOnBtn;
	SYDEClickableButton m_SoundTrackNextBtn;
	SYDEClickableButton m_SoundTrackVolume;
	SYDEClickableButton m_FormatTeamsBtn;
	SYDEClickableButton m_FormatTeamsOKBtn;
	SYDEClickableButton m_FormatTeamsCNCLBtn;

	//Results Page
	SYDEClickableButton m_GameResultSummaryBtn;
	SYDEClickableButton m_GameResultPlayByPlayBtn;

	//GameSettingsPage
	SYDEClickableButton m_GameSettingsSeasonBtn;
	SYDEClickableButton m_GameSettingsNormalBtn;

	//GameSettingsPage
	SYDEClickableButton m_PriorBetsGameBtn;
	SYDEClickableButton m_PriorBetsPremiershipBtn;

	//View Season
	SYDEClickableButton m_SettingsGoalKickerBtn;
	//View Season
	SYDEClickableButton m_SettingsWeatherBtn;
	SYDEClickableButton m_SettingsStaminaBtn;
	SYDEClickableButton m_SettingsSeasonLengthBtn;
	SYDEClickableButton m_SettingsExtraTimeBtn;
	SYDEClickableButton m_SettingsInjuryBtn;
	SYDEClickableButton m_SettingsSinBinBtn;
	SYDEClickableButton m_SettingsEventsBtn;
	SYDEClickableButton m_SettingsFinalsBtn;


	//KEYPAD
	SYDEClickableButton m_KeypadBtn_1;
	SYDEClickableButton m_KeypadBtn_2;
	SYDEClickableButton m_KeypadBtn_3;
	SYDEClickableButton m_KeypadBtn_4;
	SYDEClickableButton m_KeypadBtn_5;
	SYDEClickableButton m_KeypadBtn_6;
	SYDEClickableButton m_KeypadBtn_7;
	SYDEClickableButton m_KeypadBtn_8;
	SYDEClickableButton m_KeypadBtn_9;
	SYDEClickableButton m_KeypadBtn_0;
	SYDEClickableButton m_KeypadBtn_DOT;
	SYDEClickableButton m_KeypadBtn_CLEAR;
	SYDEClickableButton m_KeypadBtn_OK;
	SYDEClickableButton m_KeypadBtn_CNCL;

	SYDEClickableButton m_ExportBtn;
	SYDEClickableButton m_ExportOKBtn;
	SYDEClickableButton m_ExportCNCLBtn;

	vector<SYDEClickableButton> m_BetButtons;
	vector<SYDEClickableButton> m_PremiershipBetButtons;

	vector<SYDEClickableButton> m_NewsHeadlines;
	SYDEClickableButton m_BackHeadline;
	SRLNewsArticle m_Article;

	SYDEClickableButton m_TeamInDepthView;
	SYDEClickableButton m_BackTeamInDepth;
	SYDEClickableButton m_NextTeamInDepth;
	SYDEClickableButton m_PrevTeamInDepth;
	SYDEClickableButton m_TeamListInDepth;
	SYDEClickableButton m_BackTeamListInDepth;
	SYDEClickableButton m_RegeneratePlayerBtn;
	SYDEClickableButton m_RegeneratePlayerOKBtn;
	SYDEClickableButton m_RegeneratePlayerCNCLBtn;

	SYDEClickableButton m_ExitGame;
	SYDEClickableButton m_ExitGameOK;
	SYDEClickableButton m_ExitGameCNL;

	vector<string> m_SavedTeams;
	vector<string> m_SeasonTeams;
	int m_SelectedTeam = 0;
	SRLSeason m_Season;

	vector<string> m_ResultsScreenVector;
	vector<string> m_SummaryScreenVector;

	vector<SRLGameBetsWriting> m_GameBetsWriteUp;
	vector<SRLGameBetsWriting> m_PremiershipBetsWriteUp;

	int m_LineResults = 0;
	int m_SelectedGame = 0;

	const int newsArticlesPerRound = 8;

	int BaseSeasonGames = 26;

	int m_round = 0;
	int m_roundToSimulate = 0;
	SRLBetPrice m_BetMoney = SRLBetPrice(100, 0);
	SRLBetPrice m_CustomBet = SRLBetPrice(42, 30);

	bool finals = false;
	int finalsThreshold = 8;
	int finalsRounds = 4;
	int finalsSystemInt = 0;

	int currentWonBetsSeason = 0;
	int currentLostBetsSeason = 0;
	int currentBetsTotalSeason = 0;
	int currentWonBetsSeasonMatchOnly = 0;
	int currentLostBetsSeasonMatchOnly = 0;
	int currentBetsTotalSeasonMatchOnly = 0;

	FinalsSeriesType fsType = Top8Normal;
	string finalsSettingStr = "Top 8 Normal";
	vector<FinalsSeries> m_FSTYPES = vector<FinalsSeries>({
		FinalsSeries("Top 8 Normal", Top8Normal, 4, 8),
		FinalsSeries("Top 4 Normal", Top4Normal, 3, 4),
		FinalsSeries("Top 2 Normal", Top2Normal, 1, 2),
		FinalsSeries("Top 8 Knock-Out", Top8Knockout, 3, 8),
		FinalsSeries("Top 4 Knock-Out", Top4Knockout, 2, 4),
		});

	CustomAsset m_MainMenuBG = CustomAsset(60, 20, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\mainMenuBmp.bmp", 30, 20));

	SRLTeam m_InDepthTeamView;
	CustomAsset m_JerseyView;
	int m_TeamViewing = 0;
	vector<SYDEClickableButton> m_PlayerButtons;
	SRLPlayer m_PlayerView;
	CustomAsset m_PlayerAsset;
};