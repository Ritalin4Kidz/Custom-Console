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
#include <vector>
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
	ProfileViewState,
	SponsorChallengeViewState,
	MatchUpInDepthView,
	SimulateSingleMatchViewState
};

enum CoachingViewDrawState
{
	CoachingMain_STATE,
	CoachingTeamList_STATE,
	CoachingTrades_STATE,
	CoachingTraining_STATE,
	CoachingSwapPos_STATE
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

enum SeasonConfigState
{
	SelectSeasonTypeState,
	SelectSeasonTeamsState,
	SelectExhibitionTeamsState
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

enum SRLSponsorTypeState
{
	SponsorState_Casino,
	SponsorState_Shoes,
	SponsorState_Zeckfast
};

enum SRLPositionShowcaseState
{
	SRLPS_Backline = 0,
	SRLPS_Frontline,
	SRLPS_Interchange
};

enum SRLTeamListViewState
{
	TLV_GeneralStats = 0,
	TLV_Attack,
	TLV_Defence,
	TLV_Speed,
	TLV_Kicking,
	TLV_Handling
};

#pragma endregion

class SRLGame : public SYDEWindowGame {
public:
	SRLGame() { initSponsors();  init(); }
	virtual ~SRLGame() {}
	void init();

	deque<SRLPlayer> createRandomTeam(string prefix);
	deque<SRLPlayer> createOffSeasonTeam(string prefix);
	deque<SRLPlayer> createRandomTeam(string prefix, float multiplier);
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
	ConsoleWindow ProfileView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow ChallengesView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow MatchUpDepthView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow SingleMatchSimulateView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow TeamInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow TeamInDepthListView(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow PlayerInDepthView(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow LeaderboardPositions(ConsoleWindow window, deque<SRLLeaderboardPosition> ldrboard);

	void LeaderboardOutputStrings(deque<string> &mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName);
	void LeaderboardOutputStringsTopScorer(deque<string>& mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName);
	void LeaderboardOutputStringsTopPlayer(deque<string>& mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName);

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

	bool addGame(int limit, deque<SRLRound> rounds, deque<SRLGameMatchup>& games, deque<string>& teams, deque<string>& AttemptedTeams);

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
	void SimulateGameLadderAdjustment(int a_Round, int a_Game, SRLGameManager m_srlmanager);
	void SimulationEndOfRound(int m_ArticlesRemaining);
	void CalculateFeaturedGame();
	void CalculateTipMaster();

	static void saveGameSettings();
	static void loadGameSettings();

	void sortOutNews();
	void sortOutMatchButtons();
	void checkSpecificBetAchievements(SRLGameBet _bet);
	void checkBetAchievements();
	void checkCoachingAchievements();
	void offContractTrade();
	bool offContractTrade(int team1, int player1);
	void TeamTrade();
	void UpdateBets();

	void setUpTeamInDepthView(int teamViewing);
	void setUpSelectedTeamView();

	void setUpPositionShowcase(SRLPositionShowcaseState _state);

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
	static SeasonConfigState seasCfgState;

	static SRLSeasonLength seasonLength;

	static SRLSponsorTypeState sponsorState;

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

	static bool setUpPosShowcaseCall;

	static int gameNumberBet;

	static bool generateStartCall;

	static int articleClicked;

	static int priorBetNumberLine;
	void sortOutResultsScreen();
	void sortOutTrainingOptions();
	void sortOutTradingOptions();

	ConsoleWindow CreateSeason(ConsoleWindow window, bool isWorldCup);

	static deque<string> AchievementStrings;

	static int playerClicked;
	static bool playerCall;
	static bool finalsSystemCall;
	static bool RepRoundsOn;

	static bool allowJsonExportingSeason;

#pragma region coaching mode
	static bool coachingMode;
	static bool selectedTeamCall;
	static bool performTradeCall;
	static bool performTradeConfirmedCall;

	static bool performRefreshOptionsCall;

	static bool performTrainCall;
	static bool performTrainConfirmedCall;

	static bool TeamInDepthViewingJerseyAsset;

	static int playerMainTeamTrade;
	static int playerOtherTeamTrade;
	static SRLTeam otherTeamTrade;
	static SRLTrainingType trainType;
	static SRLPositionShowcaseState posSwapState;
	static SRLTeamListViewState tlViewState;
	static string posToSwap;
	static bool posSwapCall;
#pragma endregion

	static int exhibitionTeam1Num;
	static int exhibitionTeam2Num;
	static bool setUpExhibitionDisplayCall;

	static int matchInformationRound;
	static int matchInformationGame;

	static bool SimulateSingleMatchCall;

private:
	const int customTeamGenerateChance = 9999;

private:
	SYDEClickableButton m_StartSeasonBtn = SYDEClickableButton();
	SYDEClickableButton m_NextTeamSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_PrevTeamSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_AddTeamSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_RemoveTeamSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_GenerateTeamSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_RandomFillSeasonCfgBtn = SYDEClickableButton();

	//View Season
	SYDEClickableButton m_ErrorOkViewBtn = SYDEClickableButton();

	//View Season
	SYDEClickableButton m_MenuOkViewBtn = SYDEClickableButton();
	SYDEClickableButton m_MenuCnclViewBtn = SYDEClickableButton();

	//View Season
	SYDEClickableButton m_BetOkViewBtn = SYDEClickableButton();
	SYDEClickableButton m_BetCnclViewBtn = SYDEClickableButton();

	//View Season
	SYDEClickableButton m_SeasonViewBtn = SYDEClickableButton();
	//View Ladder
	SYDEClickableButton m_LadderViewBtn = SYDEClickableButton();
	//View Betting
	SYDEClickableButton m_BettingViewBtn = SYDEClickableButton();
	//VIEW COACHING
	SYDEClickableButton m_CoachingViewBtn = SYDEClickableButton();
	//View In Depth Results
	SYDEClickableButton m_ResultsViewBtn = SYDEClickableButton();
	//View Season Leader
	SYDEClickableButton m_LeaderboardViewBtn = SYDEClickableButton();
	//View Main menu
	SYDEClickableButton m_MainMenuViewBtn = SYDEClickableButton();

	SYDEClickableButton m_NewsViewBtn = SYDEClickableButton();

	SYDEClickableButton m_PreviousRoundViewBtn = SYDEClickableButton();

	SYDEClickableButton m_NextRoundViewBtn = SYDEClickableButton();

	SYDEClickableButton m_SimulateBtn = SYDEClickableButton();

	SYDEClickableButton m_BetBtnCurrentRound = SYDEClickableButton();
	SYDEClickableButton m_BetBtnViewBets = SYDEClickableButton();
	SYDEClickableButton m_BetBtnFutures = SYDEClickableButton();
	SYDEClickableButton m_BetBtnAccount = SYDEClickableButton();
	SYDEClickableButton m_BetTryscorers = SYDEClickableButton();

	SYDEClickableButton m_LeaderboardBtnMostTries = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostGoals = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostMetres = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostPoints = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostDallyM = SYDEClickableButton();

	SYDEClickableButton m_LeaderboardBtnMostFieldGoals = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostTackles = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostKickMetres = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMost4020 = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostSteals = SYDEClickableButton();

	SYDEClickableButton m_LeaderboardBtnMostErrors = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostPenalties = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostNoTries = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostRuckErrors = SYDEClickableButton();

	SYDEClickableButton m_LeaderboardBtnMostSinBin = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostSendOff = SYDEClickableButton();
	SYDEClickableButton m_LeaderboardBtnMostInjuries = SYDEClickableButton();

	SYDEClickableButton m_BackSeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_SeasonCfgBtn = SYDEClickableButton();
	SYDEClickableButton m_GameSettingsBtn = SYDEClickableButton();
	SYDEClickableButton m_GameInfoBtn = SYDEClickableButton();

	SYDEClickableButton m_SoundTrackOnBtn = SYDEClickableButton();
	SYDEClickableButton m_SoundTrackNextBtn = SYDEClickableButton();
	SYDEClickableButton m_SoundTrackVolume = SYDEClickableButton();
	SYDEClickableButton m_FormatTeamsBtn = SYDEClickableButton();
	SYDEClickableButton m_FormatTeamsOKBtn = SYDEClickableButton();
	SYDEClickableButton m_FormatTeamsCNCLBtn = SYDEClickableButton();

	//Results Page
	SYDEClickableButton m_GameResultSummaryBtn = SYDEClickableButton();
	SYDEClickableButton m_GameResultPlayByPlayBtn = SYDEClickableButton();

	//GameSettingsPage
	SYDEClickableButton m_GameSettingsSeasonBtn = SYDEClickableButton();
	SYDEClickableButton m_GameSettingsNormalBtn = SYDEClickableButton();

	//GameSettingsPage
	SYDEClickableButton m_PriorBetsGameBtn = SYDEClickableButton();
	SYDEClickableButton m_PriorBetsPremiershipBtn = SYDEClickableButton();
	SYDEClickableButton m_PriorBetsTryScorerBtn = SYDEClickableButton();

	//View Season
	SYDEClickableButton m_SettingsGoalKickerBtn = SYDEClickableButton();
	//View Season
	SYDEClickableButton m_SettingsWeatherBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsStaminaBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsSeasonLengthBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsExtraTimeBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsInjuryBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsSinBinBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsEventsBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsCoachBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsFinalsBtn = SYDEClickableButton();
	SYDEClickableButton m_SettingsRepRoundsBtn = SYDEClickableButton();

	//KEYPAD
	SYDEClickableButton m_KeypadBtn_1 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_2 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_3 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_4 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_5 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_6 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_7 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_8 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_9 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_0 = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_DOT = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_CLEAR = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_OK = SYDEClickableButton();
	SYDEClickableButton m_KeypadBtn_CNCL = SYDEClickableButton();

	SYDEClickableButton m_ExportBtn = SYDEClickableButton();
	SYDEClickableButton m_ExportOKBtn = SYDEClickableButton();
	SYDEClickableButton m_ExportCNCLBtn = SYDEClickableButton();

	deque<SYDEClickableButton> m_BetButtons = deque<SYDEClickableButton>({});
	deque<SYDEClickableButton> m_PremiershipBetButtons = deque<SYDEClickableButton>({});
	deque<SYDEClickableButton> m_TryScorerBetButtons = deque<SYDEClickableButton>({});

	deque<SYDEClickableButton> m_NewsHeadlines = deque<SYDEClickableButton>({});
	SYDEClickableButton m_BackHeadline = SYDEClickableButton();
	SRLNewsArticle m_Article;

	SYDEClickableButton m_TeamInDepthView = SYDEClickableButton();
	SYDEClickableButton m_TeamAssetSwitchView = SYDEClickableButton();
	SYDEClickableButton m_BackTeamInDepth = SYDEClickableButton();
	SYDEClickableButton m_NextTeamInDepth = SYDEClickableButton();
	SYDEClickableButton m_PrevTeamInDepth = SYDEClickableButton();
	SYDEClickableButton m_TeamListInDepth = SYDEClickableButton();
	SYDEClickableButton m_BackTeamListInDepth = SYDEClickableButton();
	SYDEClickableButton m_RegeneratePlayerBtn = SYDEClickableButton();
	SYDEClickableButton m_RegeneratePlayerOKBtn = SYDEClickableButton();
	SYDEClickableButton m_RegeneratePlayerCNCLBtn = SYDEClickableButton();

	SYDEClickableButton m_ProfileViewBtn = SYDEClickableButton();

	//EXIT GAME BUTTONS
	SYDEClickableButton m_ExitGame = SYDEClickableButton();
	SYDEClickableButton m_ExitGameOK = SYDEClickableButton();
	SYDEClickableButton m_ExitGameCNL = SYDEClickableButton();

	//FEATURED MATCH UP
	SYDEClickableButton m_FeatureViewBtn = SYDEClickableButton();
	SYDEClickableButton m_FeatureSwitchViewBtn = SYDEClickableButton();
	SYDEClickableButton m_MainDrawViewBtn = SYDEClickableButton();
	SYDEClickableButton m_MainSettingsViewBtn = SYDEClickableButton();
	SYDEClickableButton m_TipMasterViewBtn = SYDEClickableButton();
	CustomAsset m_TipMasterImg = CustomAsset(22, 11, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\Tipmaster.bmp", 11, 11));
	deque<string> TipMasterBets = deque<string>({});


	vector<string> m_SavedTeams = vector<string>({});;
	deque<string> m_SeasonTeams = deque<string>({});;
	int m_SelectedTeam = 0;
	SRLSeason m_Season;

	deque<string> m_ResultsScreenVector = deque<string>({});;
	deque<GameSummaryText> m_SummaryScreenVector;

	deque<SRLGameBetsWriting> m_GameBetsWriteUp;
	deque<SRLGameBetsWriting> m_PremiershipBetsWriteUp;
	deque<SRLGameBetsWriting> m_TryScorerBetsWriteUp;
	deque<string> AttackersHome = deque<string>({});
	deque<string> AttackersAway = deque<string>({});

	deque<SRLTeam> repTeams = deque<SRLTeam>({});

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
	deque<FinalsSeries> m_FSTYPES = deque<FinalsSeries>({
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
	CustomAsset m_FieldBg = CustomAsset(60, 20, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\fieldShowcase.bmp", 30, 20));
	CustomAsset m_ProfileLogo = CustomAsset(20, 10, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\DefaultLogo.bmp", 10, 10));
	CustomAsset_Clickable m_MiniJersery = CustomAsset_Clickable(10, 4, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\MiniJersey.bmp", 5, 4));
	deque<SRLPositionShowcase> _PositionsShowcase = deque<SRLPositionShowcase>({});
	float splashScreenTime = 0;
	bool splashScreenInit = true;
	SRLTeam m_InDepthTeamView;
	CustomAsset m_JerseyView;
	CustomAsset m_LogoView;
	int m_TeamViewing = 0;
	deque<SYDEClickableButton> m_PlayerButtons;

	deque<SYDEClickableButton> m_MatchResultButtons;

	SRLPlayer m_PlayerView;
	CustomAsset m_PlayerAsset;

	SRLProfile m_GameProfile;

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
	SYDEClickableButton m_CoachTeamCycleStatsViewBtn;
	SYDEClickableButton m_CoachTeamSwapPositionsBtn;

	SYDEClickableButton m_CoachTradeConfirmOKBtn;
	SYDEClickableButton m_CoachTradeConfirmCNCLBtn;

	SYDEClickableButton m_CoachTrainConfirmOKBtn;
	SYDEClickableButton m_CoachTrainConfirmCNCLBtn;

	SYDEClickableButton m_CoachPosSwapPrev;
	SYDEClickableButton m_CoachPosSwapNext;

	SYDEClickableButton m_CoachTrainRefreshBtn;
	const int maxRefreshes = 3;
	int refreshAvailable = 0;
	bool trainingAvailable = false;

	int startingRating = 99;

	deque<SRLTrainingOption> _trainingOptions;
	deque<SRLTradingOption> _tradingOptions;
	deque<SYDEClickableButton> m_TradingButtons;
	deque<SYDEClickableButton> m_TrainingButtons;
	bool tradingAvailable = false;
#pragma endregion

	SYDEClickableButton m_RegularSeasonCfgBtn;
	SYDEClickableButton m_WorldCupCfgBtn;
	SYDEClickableButton m_ExhibitionCfgBtn;
	FeaturedGame m_ExhibitionGameFeature;

	SYDEClickableButton m_ExhibitionSwap1Prev;
	SYDEClickableButton m_ExhibitionSwap1Next;
	SYDEClickableButton m_ExhibitionSwap2Prev;
	SYDEClickableButton m_ExhibitionSwap2Next;
	SYDEClickableButton m_SimulateSingleGameBtn;

#pragma region Challenges

	SYDEClickableButton m_Sponsor_Clarity_CasinoBtn = SYDEClickableButton();
	SYDEClickableButton m_Sponsor_Northkellion_ShoesBtn = SYDEClickableButton();
	SYDEClickableButton m_Sponsor_ZeckfastBtn = SYDEClickableButton();

	void initSponsors();
#pragma endregion


#pragma region SingleSimulation
	SRLGameManager m_SingleGameManager;
	int countSummaries = 0;
	bool singleMatchDisplayInfoCall = false;
	deque<GameSummaryText> m_LiveGameVector;
#pragma endregion
};