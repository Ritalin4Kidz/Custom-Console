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
#include "SRLStructs.h"
#include <iostream>
#include <fstream>
#include <iterator>


#pragma region states

enum GameStateSYDE
{
	Unknown_STATE,
	FMODSplashScreenState,
	MainMenu_STATE,
	Exhibition_LoadState,
	SeasonConfig_State,
	SeasonModeState,
	LadderViewState,
	ResultsViewState,
	BettingViewState,
	SelectTeamCoachingState,
	CoachingViewState,
	LeaderboardViewState,
	SettingsState,
	InformationState,
	NewsViewState,
	TeamInDepthViewState,
};

enum CoachingViewDrawState
{
	CoachingMain_STATE,
	CoachingTeamList_STATE,
	CoachingTrades_STATE,
	CoachingTraining_STATE
};

enum SeasonDrawViewState
{
	SeasonDrawMainView,
	FeaturedMatchView,
	FeaturedMatchTeamListView,
	GameSettingsInSeasonView,
	TippingMasterView
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
	Account_STATE,
	TryScorers_STATE
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
	Length_RoundRobin = 15,
	Length_MediumSeason = 20,
	Length_NormalSeason = 26,
	Length_LongSeason = 40,
	Length_ExtremeSeason = 66,
	Length_EnduranceSeason = 100
};

enum SRLPriorBets_State
{
	IndividualGameBets_State,
	PremiershipWinnerBets_State,
	TryScorerBets_State,
};

#pragma endregion

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
	ConsoleWindow fmodSplashScreen(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow season_mode(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow LadderView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow BettingView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow SelectTeamCoachingView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow CoachingView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow LeaderboardView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ResultsView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow TeamInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow TeamInDepthListView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow PlayerInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow LeaderboardPositions(ConsoleWindow window, vector<SRLLeaderboardPosition> ldrboard);

	void LeaderboardOutputStrings(vector<string> &mainVec, vector<SRLLeaderboardPosition> ldrboard);
	void LeaderboardOutputStringsTopScorer(vector<string>& mainVec, vector<SRLLeaderboardPosition> ldrboard);
	void LeaderboardOutputStringsTopPlayer(vector<string>& mainVec, vector<SRLLeaderboardPosition> ldrboard);

	ConsoleWindow SettingsView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow NewsView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow InfoView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow SimulatePopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow CreateSeasonPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow GenerationPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow FormatPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ExitPopUp(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow RandomizePopUp(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow drawTabs(ConsoleWindow window);
	ConsoleWindow drawBetTabs(ConsoleWindow window);
	ConsoleWindow drawLeaderboardTabs(ConsoleWindow window);
	ConsoleWindow drawMainMenuTabs(ConsoleWindow window);
	ConsoleWindow drawResultTabs(ConsoleWindow window);
	ConsoleWindow drawCoachingTabs(ConsoleWindow window);

	ConsoleWindow drawSeasonModeTabs(ConsoleWindow window);

	ConsoleWindow configTabs(ConsoleWindow window);

	ConsoleWindow KeypadPop_Up(ConsoleWindow window, int windowWidth, int windowHeight);

	bool addGame(int limit, vector<SRLRound> rounds, vector<SRLGameMatchup>& games, vector<string>& teams, vector<string>& AttemptedTeams);

	ConsoleWindow ErrorPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ExportPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow BetPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ConfirmPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow TradingPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow TrainingPop_UP(ConsoleWindow window, int windowWidth, int windowHeight);
	void CalculateOdds();
	void CalculatePremiershipOdds();
	void CalculateTryScorerOdds();
	void SimulateGames();
	void CalculateFeaturedGame();
	void CalculateTipMaster();

	static void saveGameSettings();
	static void loadGameSettings();

	void sortOutNews();
	void checkSpecificBetAchievements(SRLGameBet _bet);
	void checkBetAchievements();
	void offContractTrade();
	bool offContractTrade(int team1, int player1);
	void TeamTrade();
	void UpdateBets();

	void setUpTeamInDepthView(int teamViewing);
	void setUpSelectedTeamView();

	void setUpPlayer();

	void otherArticles();

	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) { m_State = newState; }

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight);

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
	static SeasonDrawViewState drawViewState;
	static CoachingViewDrawState coachDrawState;

	static SRLSeasonLength seasonLength;

	static bool SeasonStart;
	static bool SeasonStartCall;

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
	static bool m_FaceOffLimit;

	static SRLSoundtrack m_GamePlaySoundtrack;
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
	static bool homeTeamTryBet;
	static bool keyPadCall;
	static int gameNumberBet;

	static bool generateStartCall;

	static int articleClicked;

	static int priorBetNumberLine;
	void sortOutResultsScreen();
	void sortOutTrainingOptions();
	void sortOutTradingOptions();

	static vector<string> AchievementStrings;

	static int playerClicked;
	static bool playerCall;
	static bool finalsSystemCall;

#pragma region coaching mode
	static bool coachingMode;
	static bool selectedTeamCall;
	static bool performTradeCall;
	static bool performTradeConfirmedCall;

	static bool performTrainCall;
	static bool performTrainConfirmedCall;

	static int playerMainTeamTrade;
	static int playerOtherTeamTrade;
	static SRLTeam otherTeamTrade;
	static SRLTrainingType trainType;
#pragma endregion
private:
	const int customTeamGenerateChance = 9999;

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
	//VIEW COACHING
	SYDEClickableButton m_CoachingViewBtn;
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
	SYDEClickableButton m_BetTryscorers;

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
	SYDEClickableButton m_PriorBetsTryScorerBtn;

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
	SYDEClickableButton m_SettingsCoachBtn;
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
	vector<SYDEClickableButton> m_TryScorerBetButtons;

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

	//EXIT GAME BUTTONS
	SYDEClickableButton m_ExitGame;
	SYDEClickableButton m_ExitGameOK;
	SYDEClickableButton m_ExitGameCNL;

	//FEATURED MATCH UP
	SYDEClickableButton m_FeatureViewBtn;
	SYDEClickableButton m_FeatureSwitchViewBtn;
	SYDEClickableButton m_MainDrawViewBtn;
	SYDEClickableButton m_MainSettingsViewBtn;
	SYDEClickableButton m_TipMasterViewBtn;
	CustomAsset m_TipMasterImg = CustomAsset(22, 11, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\Tipmaster.bmp", 11, 11));
	vector<string> TipMasterBets;


	vector<string> m_SavedTeams;
	vector<string> m_SeasonTeams;
	int m_SelectedTeam = 0;
	SRLSeason m_Season;

	vector<string> m_ResultsScreenVector;
	vector<GameSummaryText> m_SummaryScreenVector;

	vector<SRLGameBetsWriting> m_GameBetsWriteUp;
	vector<SRLGameBetsWriting> m_PremiershipBetsWriteUp;
	vector<SRLGameBetsWriting> m_TryScorerBetsWriteUp;
	vector<string> AttackersHome = vector<string>();
	vector<string> AttackersAway = vector<string>();

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

	float ScrollTickTime = 0;
	float maxScrollTickTime = 0.05f;

	int currentWonBetsSeason = 0;
	int currentLostBetsSeason = 0;
	int currentBetsTotalSeason = 0;
	int currentWonBetsSeasonMatchOnly = 0;
	int currentLostBetsSeasonMatchOnly = 0;
	int currentBetsTotalSeasonMatchOnly = 0;

	static float m_ScrollingSpeed;

	FinalsSeriesType fsType = Top8Normal;
	string finalsSettingStr = "Top 8 Normal";
	vector<FinalsSeries> m_FSTYPES = vector<FinalsSeries>({
		FinalsSeries("Top 8 Normal", Top8Normal, 4, 8),
		FinalsSeries("Top 4 Normal", Top4Normal, 3, 4),
		FinalsSeries("Top 2 Normal", Top2Normal, 1, 2),
		FinalsSeries("Top 8 Knock-Out", Top8Knockout, 3, 8),
		FinalsSeries("Top 4 Knock-Out", Top4Knockout, 2, 4),
		FinalsSeries("Top 8 Double-Elim", Top8DoubleElim, 6, 8),
		FinalsSeries("Knockout Tourny", KnockoutTournament, 4, 16),
		FinalsSeries("Double Elim Tourny", KnockoutTournamentDouble, 8, 16),
		});

	CustomAnimationAsset m_MainMenuBG = CustomAnimationAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\mainmenuAnim.bmp", astVars, 180, 280, 30, 20, 0, 81));
	CustomAsset m_FmodSplash = CustomAsset(60, 20, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\fmodlogo.bmp", 30, 20));
	float splashScreenTime = 0;
	bool splashScreenInit = true;
	SRLTeam m_InDepthTeamView;
	CustomAsset m_JerseyView;
	int m_TeamViewing = 0;
	vector<SYDEClickableButton> m_PlayerButtons;
	SRLPlayer m_PlayerView;
	CustomAsset m_PlayerAsset;

#pragma region COACHING
	SRLTeam m_CoachedTeam;
	string teamCoached = "";
	int teamSelected = 0;
	CustomAsset m_SelectedTeamJerseyView;
	int teamSelectedRating = 0;
	SYDEClickableButton m_SelectTeamBtn;
	SYDEClickableButton m_CoachMainStateBtn;
	SYDEClickableButton m_CoachTradeStateBtn;
	SYDEClickableButton m_CoachTrainStateBtn;
	SYDEClickableButton m_CoachTeamStateBtn;

	SYDEClickableButton m_CoachTradeConfirmOKBtn;
	SYDEClickableButton m_CoachTradeConfirmCNCLBtn;

	SYDEClickableButton m_CoachTrainConfirmOKBtn;
	SYDEClickableButton m_CoachTrainConfirmCNCLBtn;

	vector<SRLTrainingOption> _trainingOptions;
	vector<SRLTradingOption> _tradingOptions;
	vector<SYDEClickableButton> m_TradingButtons;
	vector<SYDEClickableButton> m_TrainingButtons;
	bool tradingAvailable = false;
#pragma endregion
};