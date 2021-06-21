#include "SRL.h"
AssetsClass SRLGame::astVars = AssetsClass();
GameStateSYDE SRLGame::currentState = Unknown_STATE;
GameStateSYDE SRLGame::newState = MainMenu_STATE;
GameStateBettingSYDE SRLGame::bettingState = CurrentRound_STATE;
GameStateLeaderboardSYDE SRLGame::ldrState = Tries_State;
GameStateResultSYDE SRLGame::resultState = Summary_STATE;
SRLSeasonLength SRLGame::seasonLength = Length_NormalSeason;
bool SRLGame::SeasonStart = false;
bool SRLGame::NextRoundCall = false;
bool SRLGame::PrevRoundCall = false;
bool SRLGame::addCall = false;
bool SRLGame::removeCall = false;
bool SRLGame::Simulate = false;
bool SRLGame::generateCall = false;
bool SRLGame::randomFillCall = false;
bool SRLGame::errorCall = false;
bool SRLGame::menuCall = false;
bool SRLGame::m_GoalKicker = true;
bool SRLGame::m_Weather = true;
bool SRLGame::m_Stamina = true;
string SRLGame::errorMessage = "";
void ExhibitionMatchClick()
{
	if (SRLGame::currentState = MainMenu_STATE)
	{
		SRLGame::newState = Exhibition_LoadState;
	}
}

void SimulateClick()
{
	if (SRLGame::currentState == SeasonModeState)
	{
		SRLGame::Simulate = true;
	}
}

void ErrorOKClick()
{
	SRLGame::errorCall = false;
}

void MenuCNCLClick()
{
	SRLGame::menuCall = false;
}
void MenuOKViewClick()
{
	SRLGame::newState = MainMenu_STATE;
	SRLGame::menuCall = false;
}

void SeasonModeClick()
{
	SRLGame::newState = SeasonConfig_State;
}

void SeasonModeStartClick()
{
	SRLGame::SeasonStart = true;
}


void SeasonViewClick()
{
	SRLGame::newState = SeasonModeState;
}
void LadderViewClick()
{
	SRLGame::newState = LadderViewState;
}
void LeaderboardViewClick()
{
	SRLGame::newState = LeaderboardViewState;
}
void ResultsViewClick()
{
	SRLGame::newState = ResultsViewState;
}
void BettingViewClick()
{
	SRLGame::newState = BettingViewState;
}

void CurrentRoundViewClick()
{
	SRLGame::bettingState = CurrentRound_STATE;
}
void FuturesViewClick()
{
	SRLGame::bettingState = Futures_STATE;
}
void AccountViewClick()
{
	SRLGame::bettingState = Account_STATE;
}

void AddViewClick()
{
	SRLGame::addCall = true;
}
void RemoveViewClick()
{
	SRLGame::removeCall = true;
}

void TriesLdrViewClick()
{
	SRLGame::ldrState = Tries_State;
}
void GoalsLdrViewClick()
{
	SRLGame::ldrState = Goals_STATE;
}
void PointsLdrViewClick()
{
	SRLGame::ldrState = Points_STATE;
}
void MetresLdrViewClick()
{
	SRLGame::ldrState = Metres_State;
}
void DallyLdrViewClick()
{
	SRLGame::ldrState = Dally_State;
}
void FGLdrViewClick()
{
	SRLGame::ldrState = FG_State;
}
void TackleLdrViewClick()
{
	SRLGame::ldrState = Tackles_State;
}
void KickMetresLdrViewClick()
{
	SRLGame::ldrState = KickMetres_State;
}
void _4020LdrViewClick()
{
	SRLGame::ldrState = State_4020;
}
void StealsLdrViewClick()
{
	SRLGame::ldrState = Steals_State;
}
void ErrorsLdrViewClick()
{
	SRLGame::ldrState = ErrorsLdr_State;
}
void PenaltiesViewClick()
{
	SRLGame::ldrState = Penalty_State;
}
void RuckErrorLdrViewClick()
{
	SRLGame::ldrState = RuckError_State;
}
void NoTriesLdrViewClick()
{
	SRLGame::ldrState = NoTry_State;
}

void GenerateTeamViewClick()
{
	SRLGame::generateCall = true;
}

void ToggleKickerClick()
{
	SRLGame::m_GoalKicker = !SRLGame::m_GoalKicker;
}

void ToggleWeatherClick()
{
	SRLGame::m_Weather = !SRLGame::m_Weather;
}

void ToggleStaminaClick()
{
	SRLGame::m_Stamina = !SRLGame::m_Stamina;
}

void BlankViewClick()
{
	
}

void SummaryRsltViewClick()
{
	SRLGame::resultState = Summary_STATE;
}

void PlayByPlayRsltViewClick()
{
	SRLGame::resultState = PlayByPlay_STATE;
}

void NextRoundViewClick()
{
	if (SRLGame::currentState == SeasonModeState || SRLGame::currentState == ResultsViewState || SRLGame::currentState == SeasonConfig_State)
	{
		SRLGame::NextRoundCall = true;
	}
}

void PrevRoundViewClick()
{
	if (SRLGame::currentState == SeasonModeState || SRLGame::currentState == ResultsViewState || SRLGame::currentState == SeasonConfig_State)
	{
		SRLGame::PrevRoundCall = true;
	}
}

void MainMenuViewClick()
{
	if (SRLGame::currentState != SeasonModeState)
	{
		SRLGame::newState = MainMenu_STATE;
		return;
	}
	SRLGame::errorMessage = "Abort Season & Return To Menu?";
	SRLGame::menuCall = true;
}


void SettingsViewClick()
{
	SRLGame::newState = SettingsState;
}
void SettingsLengthViewClick()
{
	if (SRLGame::seasonLength == Length_ShortSeason)
	{
		SRLGame::seasonLength = Length_MediumSeason;
	}
	else if (SRLGame::seasonLength == Length_MediumSeason)
	{
		SRLGame::seasonLength = Length_NormalSeason;
	}
	else if (SRLGame::seasonLength == Length_NormalSeason)
	{
		SRLGame::seasonLength = Length_LongSeason;
	}
	else if (SRLGame::seasonLength == Length_LongSeason)
	{
		SRLGame::seasonLength = Length_ExtremeSeason;
	}
	else if (SRLGame::seasonLength == Length_ExtremeSeason)
	{
		SRLGame::seasonLength = Length_EnduranceSeason;
	}
	else if (SRLGame::seasonLength == Length_EnduranceSeason)
	{
		SRLGame::seasonLength = Length_ShortSeason;
	}
}


void InfoViewClick()
{
	SRLGame::newState = InformationState;
}

void RandomFillClick()
{
	SRLGame::randomFillCall = true;
}


void SRLGame::init()
{

	m_SeasonViewBtn = SYDEClickableButton("   Season   ", Vector2(0, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SeasonViewBtn.setHighLight(RED);
	m_SeasonViewBtn.SetFunc(SeasonViewClick);
	m_LadderViewBtn = SYDEClickableButton("   Ladder   ", Vector2(12, 1), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_LadderViewBtn.setHighLight(RED);
	m_LadderViewBtn.SetFunc(LadderViewClick);
	m_BettingViewBtn = SYDEClickableButton("   Betting   ", Vector2(24, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BettingViewBtn.setHighLight(RED);
	m_BettingViewBtn.SetFunc(BettingViewClick);
	m_ResultsViewBtn = SYDEClickableButton("   Results  ", Vector2(36, 1), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_ResultsViewBtn.setHighLight(RED);
	m_ResultsViewBtn.SetFunc(ResultsViewClick);
	m_LeaderboardViewBtn = SYDEClickableButton("Leaderboard ", Vector2(48, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_LeaderboardViewBtn.setHighLight(RED);
	m_LeaderboardViewBtn.SetFunc(LeaderboardViewClick);
	m_MainMenuViewBtn = SYDEClickableButton("  Main Menu ", Vector2(0, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_MainMenuViewBtn.setHighLight(RED);
	m_MainMenuViewBtn.SetFunc(MainMenuViewClick);

	//BLANK BUTTONS EDIT LATER
	m_Blank1ViewBtn = SYDEClickableButton("    Blank   ", Vector2(12, 19), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_Blank1ViewBtn.setHighLight(RED);
	m_Blank1ViewBtn.SetFunc(BlankViewClick);
	m_PreviousRoundViewBtn = SYDEClickableButton("   Previous  ", Vector2(24, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_PreviousRoundViewBtn.setHighLight(RED);
	m_PreviousRoundViewBtn.SetFunc(PrevRoundViewClick);
	m_NextRoundViewBtn = SYDEClickableButton("    Next    ", Vector2(36, 19), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_NextRoundViewBtn.setHighLight(RED);
	m_NextRoundViewBtn.SetFunc(NextRoundViewClick);
	m_SimulateBtn = SYDEClickableButton("  Simulate  ", Vector2(48, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_SimulateBtn.setHighLight(RED);
	m_SimulateBtn.SetFunc(SimulateClick);

	m_BetBtnCurrentRound = SYDEClickableButton("    Current Round    ", Vector2(0, 2), Vector2(20, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnCurrentRound.setHighLight(RED);
	m_BetBtnCurrentRound.SetFunc(CurrentRoundViewClick);
	m_BetBtnFutures = SYDEClickableButton("       Futures       ", Vector2(20, 2), Vector2(20, 1), BRIGHTWHITE_BRIGHTGREEN_BG, false);
	m_BetBtnFutures.setHighLight(RED);
	m_BetBtnFutures.SetFunc(FuturesViewClick);
	m_BetBtnAccount = SYDEClickableButton("       Account       ", Vector2(40, 2), Vector2(20, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnAccount.setHighLight(RED);
	m_BetBtnAccount.SetFunc(AccountViewClick);

	//SEASON CONFIG
	m_PrevTeamSeasonCfgBtn = SYDEClickableButton(" Previous Team  ", Vector2(0, 19), Vector2(16, 1), BLACK_WHITE_BG, false);
	m_PrevTeamSeasonCfgBtn.setHighLight(RED);
	m_PrevTeamSeasonCfgBtn.SetFunc(PrevRoundViewClick);
	m_NextTeamSeasonCfgBtn = SYDEClickableButton("Next Team ", Vector2(16, 19), Vector2(10, 1), BLACK_BRIGHTWHITE_BG, false);
	m_NextTeamSeasonCfgBtn.setHighLight(RED);
	m_NextTeamSeasonCfgBtn.SetFunc(NextRoundViewClick);
	m_AddTeamSeasonCfgBtn = SYDEClickableButton(" Add Team", Vector2(26, 19), Vector2(9, 1), BLACK_WHITE_BG, false);
	m_AddTeamSeasonCfgBtn.setHighLight(RED);
	m_AddTeamSeasonCfgBtn.SetFunc(AddViewClick);
	m_RemoveTeamSeasonCfgBtn = SYDEClickableButton(" Remove Team ", Vector2(35, 19), Vector2(13, 1), BLACK_BRIGHTWHITE_BG, false);
	m_RemoveTeamSeasonCfgBtn.setHighLight(RED);
	m_RemoveTeamSeasonCfgBtn.SetFunc(RemoveViewClick);
	m_StartSeasonBtn = SYDEClickableButton("Start Season", Vector2(48, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_StartSeasonBtn.setHighLight(RED);
	m_StartSeasonBtn.SetFunc(SeasonModeStartClick);
	m_GenerateTeamSeasonCfgBtn = SYDEClickableButton("Generate Team", Vector2(47, 3), Vector2(13, 1), BLACK_WHITE_BG, false);
	m_GenerateTeamSeasonCfgBtn.setHighLight(RED);
	m_GenerateTeamSeasonCfgBtn.SetFunc(GenerateTeamViewClick);
	m_RandomFillSeasonCfgBtn = SYDEClickableButton("Random Fill", Vector2(49, 2), Vector2(11, 1), BLACK_BRIGHTWHITE_BG, false);
	m_RandomFillSeasonCfgBtn.setHighLight(RED);
	m_RandomFillSeasonCfgBtn.SetFunc(RandomFillClick);

	//LEADERBOARD
	m_LeaderboardBtnMostTries = SYDEClickableButton(" Most Tries ", Vector2(0, 2), Vector2(12, 1), BRIGHTWHITE_LIGHTBLUE_BG, false);
	m_LeaderboardBtnMostTries.setHighLight(RED);
	m_LeaderboardBtnMostTries.SetFunc(TriesLdrViewClick);
	m_LeaderboardBtnMostGoals = SYDEClickableButton(" Most Goals ", Vector2(12, 2), Vector2(12, 1), BRIGHTWHITE_AQUA_BG, false);
	m_LeaderboardBtnMostGoals.setHighLight(RED);
	m_LeaderboardBtnMostGoals.SetFunc(GoalsLdrViewClick);
	m_LeaderboardBtnMostMetres = SYDEClickableButton(" Top Metres ", Vector2(24, 2), Vector2(12, 1), BRIGHTWHITE_LIGHTBLUE_BG, false);
	m_LeaderboardBtnMostMetres.setHighLight(RED);
	m_LeaderboardBtnMostMetres.SetFunc(MetresLdrViewClick);
	m_LeaderboardBtnMostPoints = SYDEClickableButton(" Top Points ", Vector2(36, 2), Vector2(12, 1), BRIGHTWHITE_AQUA_BG, false);
	m_LeaderboardBtnMostPoints.setHighLight(RED);
	m_LeaderboardBtnMostPoints.SetFunc(PointsLdrViewClick);
	m_LeaderboardBtnMostDallyM = SYDEClickableButton(" Top Player ", Vector2(48, 2), Vector2(12, 1), BRIGHTWHITE_LIGHTBLUE_BG, false);
	m_LeaderboardBtnMostDallyM.setHighLight(RED);
	m_LeaderboardBtnMostDallyM.SetFunc(DallyLdrViewClick);

	m_LeaderboardBtnMostFieldGoals = SYDEClickableButton(" Field Goal ", Vector2(0, 3), Vector2(12, 1), BRIGHTWHITE_AQUA_BG, false);
	m_LeaderboardBtnMostFieldGoals.setHighLight(RED);
	m_LeaderboardBtnMostFieldGoals.SetFunc(FGLdrViewClick);
	m_LeaderboardBtnMostTackles = SYDEClickableButton(" Top Tackle ", Vector2(12, 3), Vector2(12, 1), BRIGHTWHITE_LIGHTBLUE_BG, false);
	m_LeaderboardBtnMostTackles.setHighLight(RED);
	m_LeaderboardBtnMostTackles.SetFunc(TackleLdrViewClick);
	m_LeaderboardBtnMostKickMetres = SYDEClickableButton(" Kick Metre ", Vector2(24, 3), Vector2(12, 1), BRIGHTWHITE_AQUA_BG, false);
	m_LeaderboardBtnMostKickMetres.setHighLight(RED);
	m_LeaderboardBtnMostKickMetres.SetFunc(KickMetresLdrViewClick);
	m_LeaderboardBtnMost4020 = SYDEClickableButton(" Most 40/20 ", Vector2(36, 3), Vector2(12, 1), BRIGHTWHITE_LIGHTBLUE_BG, false);
	m_LeaderboardBtnMost4020.setHighLight(RED);
	m_LeaderboardBtnMost4020.SetFunc(_4020LdrViewClick);
	m_LeaderboardBtnMostSteals = SYDEClickableButton(" Top Steals ", Vector2(48, 3), Vector2(12, 1), BRIGHTWHITE_AQUA_BG, false);
	m_LeaderboardBtnMostSteals.setHighLight(RED);
	m_LeaderboardBtnMostSteals.SetFunc(StealsLdrViewClick);

	m_LeaderboardBtnMostErrors = SYDEClickableButton(" Top Errors ", Vector2(6, 4), Vector2(12, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_LeaderboardBtnMostErrors.setHighLight(RED);
	m_LeaderboardBtnMostErrors.SetFunc(ErrorsLdrViewClick);
	m_LeaderboardBtnMostPenalties = SYDEClickableButton(" Top Penalty", Vector2(18, 4), Vector2(12, 1), BRIGHTWHITE_RED_BG, false);
	m_LeaderboardBtnMostPenalties.setHighLight(RED);
	m_LeaderboardBtnMostPenalties.SetFunc(PenaltiesViewClick);
	m_LeaderboardBtnMostRuckErrors = SYDEClickableButton(" Ruck Error ", Vector2(30, 4), Vector2(12, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_LeaderboardBtnMostRuckErrors.setHighLight(RED);
	m_LeaderboardBtnMostRuckErrors.SetFunc(RuckErrorLdrViewClick);
	m_LeaderboardBtnMostNoTries = SYDEClickableButton(" Top No Try ", Vector2(42, 4), Vector2(12, 1), BRIGHTWHITE_RED_BG, false);
	m_LeaderboardBtnMostNoTries.setHighLight(RED);
	m_LeaderboardBtnMostNoTries.SetFunc(NoTriesLdrViewClick);


	//MainMenuTabs
	m_BackSeasonCfgBtn = SYDEClickableButton("   Main Menu  ", Vector2(0, 1), Vector2(14, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BackSeasonCfgBtn.setHighLight(RED);
	m_BackSeasonCfgBtn.SetFunc(MainMenuViewClick);
	m_SeasonCfgBtn = SYDEClickableButton("  Season Mode  ", Vector2(14, 1), Vector2(15, 1), BLACK_WHITE_BG, false);
	m_SeasonCfgBtn.setHighLight(RED);
	m_SeasonCfgBtn.SetFunc(SeasonModeClick);
	m_GameSettingsBtn = SYDEClickableButton(" Game Settings ", Vector2(29, 1), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_GameSettingsBtn.setHighLight(RED);
	m_GameSettingsBtn.SetFunc(SettingsViewClick);
	m_GameInfoBtn = SYDEClickableButton("Game Information", Vector2(44, 1), Vector2(16, 1), BLACK_WHITE_BG, false);
	m_GameInfoBtn.setHighLight(RED);
	m_GameInfoBtn.SetFunc(InfoViewClick);

	//RESULTS PAGE
	m_GameResultSummaryBtn = SYDEClickableButton("            Summary           ", Vector2(0, 2), Vector2(30, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_GameResultSummaryBtn.setHighLight(RED);
	m_GameResultSummaryBtn.SetFunc(SummaryRsltViewClick);
	m_GameResultPlayByPlayBtn = SYDEClickableButton("         Play By Play         ", Vector2(30, 2), Vector2(30, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_GameResultPlayByPlayBtn.setHighLight(RED);
	m_GameResultPlayByPlayBtn.SetFunc(PlayByPlayRsltViewClick);

	m_ErrorOkViewBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4,1), BLACK_BRIGHTWHITE_BG, false);
	m_ErrorOkViewBtn.setHighLight(RED);
	m_ErrorOkViewBtn.SetFunc(ErrorOKClick);

	m_MenuOkViewBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_MenuOkViewBtn.setHighLight(RED);
	m_MenuOkViewBtn.SetFunc(MenuOKViewClick);

	m_MenuCnclViewBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_MenuCnclViewBtn.setHighLight(RED);
	m_MenuCnclViewBtn.SetFunc(MenuCNCLClick);

	//SETTINGS
	m_SettingsGoalKickerBtn = SYDEClickableButton(" Main Goal Kicker:", Vector2(3, 3), Vector2(18, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsGoalKickerBtn.setHighLight(RED);
	m_SettingsGoalKickerBtn.SetFunc(ToggleKickerClick);

	m_SettingsWeatherBtn = SYDEClickableButton(" Weather:", Vector2(12, 5), Vector2(9, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsWeatherBtn.setHighLight(RED);
	m_SettingsWeatherBtn.SetFunc(ToggleWeatherClick);

	m_SettingsStaminaBtn = SYDEClickableButton(" Stamina:", Vector2(12, 7), Vector2(9, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsStaminaBtn.setHighLight(RED);
	m_SettingsStaminaBtn.SetFunc(ToggleStaminaClick);

	m_SettingsSeasonLengthBtn = SYDEClickableButton(" Season Length:", Vector2(6, 9), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsSeasonLengthBtn.setHighLight(RED);
	m_SettingsSeasonLengthBtn.SetFunc(SettingsLengthViewClick);
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		m_Team.push_back(SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20));
	}
	return m_Team;
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix, float multiplier)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		m_Team.push_back(SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier));
	}
	return m_Team;
}

void SRLGame::test()
{
	SRLGameManager m_srlmanager;
	SRLTeam HomeTeam = generateRandomTeam();//SRLTeam("Mildews");
	//HomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\Mildews.json");
	SRLTeam AwayTeam = generateRandomTeam();
	//AwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\Honey Magnets.json");
	m_srlmanager.setTeams(HomeTeam, AwayTeam);
	try
	{
		m_srlmanager.addTeamLineupsPlayByPlay();
		m_srlmanager.addStartTimePlay();
		while (m_srlmanager.getMinutesPassed() < 80 || m_srlmanager.isTied())
		{
			m_srlmanager.play();
		}
		m_srlmanager.addFullTimePlay();
	}
	catch (exception ex)
	{
		//TODO
	}
	m_srlmanager.endStats();

	std::ofstream output_file("EngineFiles\\GameResults\\MainGame.txt");
	for (const auto& e : m_srlmanager.getPlayByPlay()) output_file << e << "\n";
}

SRLTeam SRLGame::generateRandomTeam()
{
	return SRLTeam(createRandomTeam(""), SRLNameGenerator::generateRandomTeamName());
}

SRLTeam SRLGame::generateRandomTeam(float multiplier)
{
	return SRLTeam(createRandomTeam("", multiplier), SRLNameGenerator::generateRandomTeamName());
}

ConsoleWindow SRLGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (errorCall)
	{
		return ErrorPop_UP(window, windowWidth, windowHeight);
	}
	else if (menuCall)
	{
		return ConfirmPop_UP(window, windowWidth, windowHeight);
	}
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	if (newState != currentState)
	{
		currentState = newState;
		if (currentState == MainMenu_STATE)
		{
			AssignState(std::bind(&SRLGame::main_menu_scene, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == Exhibition_LoadState)
		{
			AssignState(std::bind(&SRLGame::exhibition_match_settings, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == SeasonModeState)
		{
			AssignState(std::bind(&SRLGame::season_mode, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == LadderViewState)
		{
			AssignState(std::bind(&SRLGame::LadderView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == LeaderboardViewState)
		{
			AssignState(std::bind(&SRLGame::LeaderboardView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == BettingViewState)
		{
			AssignState(std::bind(&SRLGame::BettingView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == SettingsState)
		{
			AssignState(std::bind(&SRLGame::SettingsView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == InformationState)
		{
			AssignState(std::bind(&SRLGame::InfoView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == ResultsViewState)
		{
			m_SelectedGame = 0;
			sortOutResultsScreen();
			AssignState(std::bind(&SRLGame::ResultsView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == SeasonConfig_State)
		{
			while (SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				SRLTeam HomeTeam = generateRandomTeam();
				HomeTeam.saveTeam();
			}
			m_SelectedTeam = 0;
			m_SeasonTeams = vector<string>();
			m_SavedTeams = SYDEFileDefaults::getAllFileNamesInFolder("EngineFiles\\GameResults\\Teams", ".json", true, true);
			AssignState(std::bind(&SRLGame::season_config_settings, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
	}
	window = DoState(window, windowWidth, windowHeight);
	return window;
}

ConsoleWindow SRLGame::main_menu_scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_MainMenuBG.draw_asset(window, Vector2(0, 0));
	window = drawMainMenuTabs(window);
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	//window.setTextAtPoint(Vector2(0, 19), "", BLACK_BRIGHTWHITE_BG);
	return window;
}

ConsoleWindow SRLGame::exhibition_match_settings(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return window;
}

ConsoleWindow SRLGame::season_config_settings(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawMainMenuTabs(window);
	window = configTabs(window);
	if (SeasonStart)
	{
		BaseSeasonGames = static_cast<int>(seasonLength);
		SeasonStart = false;
		if (m_SeasonTeams.size() != 16)
		{
			errorCall = true;
			errorMessage = "Not Enough Teams To Start Season (16 Required)";
			return window;
		}
		//DO CONFIG IN HERE
		vector<SRLLadderPosition> ladders;
		for (int i = 0; i < m_SeasonTeams.size(); i++)
		{
			SRLLadderPosition newPosition;
			newPosition.teamName = m_SeasonTeams[i];
			ladders.push_back(newPosition);
		}
		SRLLadder Ladder = SRLLadder(ladders);
		vector<SRLRound> rounds;
		for (int i = 0; i < BaseSeasonGames; i++)
		{
			vector<SRLGameMatchup> games;
			vector<string> AvailableTeams = m_SeasonTeams;
			for (int ii = 0; ii < 8; ii++)
			{
				int team1 = rand() % AvailableTeams.size();
				string team1Name = AvailableTeams[team1];
				AvailableTeams.erase(AvailableTeams.begin() + team1);
				int team2 = rand() % AvailableTeams.size();
				string team2Name = AvailableTeams[team2];
				AvailableTeams.erase(AvailableTeams.begin() + team2);
				games.push_back(SRLGameMatchup(team1Name, team2Name));
			}
			rounds.push_back(SRLRound(games));
		}
		SRLDraw Draw(rounds);
		m_Season = SRLSeason(Draw, Ladder);
		newState = SeasonModeState;
		m_round = 0;
		m_roundToSimulate = 0;
		finals = false;
		CalculateOdds();
		return window;
	}


	window.setTextAtPoint(Vector2(0, 2), "SEASON CONFIG: ", WHITE);
	window.setTextAtPoint(Vector2(16, 2), m_SavedTeams[m_SelectedTeam], WHITE);
	window.setTextAtPoint(Vector2(0, 3), "TEAMS:", WHITE);
	for (int i = 0; i < m_SeasonTeams.size(); i++)
	{
		window.setTextAtPoint(Vector2(7, i + 3), m_SeasonTeams[i], WHITE);
	}

	if (NextRoundCall)
	{
		NextRoundCall = false;
		m_SelectedTeam++;
		if (m_SelectedTeam > m_SavedTeams.size() - 1)
		{
			m_SelectedTeam = 0;
		}
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
		m_SelectedTeam--;
		if (m_SelectedTeam < 0)
		{
			m_SelectedTeam = m_SavedTeams.size() - 1;
		}
	}
	if (generateCall)
	{
		generateCall = false;
		if (m_SeasonTeams.size() < 16)
		{
			SRLTeam HomeTeam = generateRandomTeam();
			HomeTeam.saveTeam();
			m_SeasonTeams.push_back(HomeTeam.getName());
		}
		else
		{
			errorCall = true;
			errorMessage = "Already 16 Teams In Season";
		}
	}
	if (addCall)
	{
		addCall = false;
		if (m_SeasonTeams.size() < 16)
		{
			m_SeasonTeams.push_back(m_SavedTeams[m_SelectedTeam]);
			m_SavedTeams.erase(m_SavedTeams.begin() + m_SelectedTeam);
			if (m_SelectedTeam > m_SavedTeams.size() - 1)
			{
				m_SelectedTeam = 0;
			}
		}
		else
		{
			errorCall = true;
			errorMessage = "Already 16 Teams In Season";
		}
	}
	if (removeCall)
	{
		removeCall = false;
		if (m_SeasonTeams.size() > 0)
		{
			m_SavedTeams.push_back(m_SeasonTeams[m_SeasonTeams.size()-1]);
			m_SeasonTeams.erase(m_SeasonTeams.begin() + m_SeasonTeams.size() - 1);
		}
		else
		{
			errorCall = true;
			errorMessage = "No Teams To Remove";
		}
	}

	if (randomFillCall)
	{
		randomFillCall = false;
		if (m_SeasonTeams.size() == 16)
		{
			errorCall = true;
			errorMessage = "Already 16 Teams In Season";
		}
		while (m_SeasonTeams.size() < 16)
		{
			m_SelectedTeam = rand() % m_SavedTeams.size();
			m_SeasonTeams.push_back(m_SavedTeams[m_SelectedTeam]);
			m_SavedTeams.erase(m_SavedTeams.begin() + m_SelectedTeam);
			if (m_SelectedTeam > m_SavedTeams.size() - 1)
			{
				m_SelectedTeam = 0;
			}
		}
	}

	return window;
}

ConsoleWindow SRLGame::season_mode(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//m_Season will contain all the data for the season
	//Grab the draw to determine the next game to play
	//after the game is complete, adjust the ladder with the new values
	// the ladder should be sorted by Points - P/D - Points For - Played - Alphabetical
	window = drawTabs(window);
	if (NextRoundCall)
	{
		NextRoundCall = false;
		m_round++;
		if (m_round >= m_Season.m_Draw.m_Rounds.size())
		{
			m_round =0;
		}
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
		m_round--;
		if (m_round < 0)
		{
			m_round = m_Season.m_Draw.m_Rounds.size() - 1;
		}
	}
	window.setTextAtPoint(Vector2(0, 2), "SRL ROUND " + std::to_string(m_round + 1), WHITE);
	for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_round].m_Games.size(); i++)
	{
		window.setTextAtPoint(Vector2(0, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].HomeTeam, WHITE);
		window.setTextAtPoint(Vector2(26, 3 + i), std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].homeTeamScore) + " v " + std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].awayTeamScore), WHITE);
		window.setTextAtPoint(Vector2(34, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].AwayTeam, WHITE);
	}
	SimulateGames();

	return window;
}

ConsoleWindow SRLGame::LadderView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window.setTextAtPoint(Vector2(0, 2), "SRL LADDER   ", WHITE);
	for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
	{
		if (i + 1 <= 8)
		{
			for (int ii = 0; ii < 60; ii++)
			{
				window.setTextAtPoint(Vector2(ii, 3 + i), " ", BRIGHTWHITE_BLUE_BG);
			}
			window.setTextAtPoint(Vector2(2, 3 + i), to_string(i + 1) + " " + m_Season.m_Ladder.m_Ladder[i].teamName, BRIGHTWHITE_BLUE_BG);
			window.setTextAtPoint(Vector2(34, 3 + i), "W: " + to_string(m_Season.m_Ladder.m_Ladder[i].won) + " L: " + to_string(m_Season.m_Ladder.m_Ladder[i].lost) + " PD: " + to_string(m_Season.m_Ladder.m_Ladder[i].pointsDifference) + " P: " + to_string(m_Season.m_Ladder.m_Ladder[i].points), BRIGHTWHITE_BLUE_BG);
		}
		else
		{
			window.setTextAtPoint(Vector2(2, 3 + i), to_string(i + 1) + " " + m_Season.m_Ladder.m_Ladder[i].teamName, WHITE);
			window.setTextAtPoint(Vector2(34, 3 + i), "W: " + to_string(m_Season.m_Ladder.m_Ladder[i].won) + " L: " + to_string(m_Season.m_Ladder.m_Ladder[i].lost) + " PD: " + to_string(m_Season.m_Ladder.m_Ladder[i].pointsDifference) + " P: " + to_string(m_Season.m_Ladder.m_Ladder[i].points), WHITE);
		}
	}
	return window;
}

ConsoleWindow SRLGame::BettingView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window = drawBetTabs(window);
	if (bettingState == CurrentRound_STATE)
	{
		if (m_roundToSimulate < BaseSeasonGames + 4)
		{
			int line = 3;
			for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
			{
				window.setTextAtPoint(Vector2(0, line ), "(H) " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + " - " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamOdds.ReturnPrice(), window._intToColour(i + 1));
				window.setTextAtPoint(Vector2(0, line + 1),"(A) " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + " - " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamOdds.ReturnPrice(), window._intToColour(i + 1));
				line += 2;
			}
		}
	}
	else if(bettingState == Futures_STATE)
	{

	}
	else if (bettingState == Account_STATE)
	{

	}


	return window;
}

ConsoleWindow SRLGame::LeaderboardView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window = drawLeaderboardTabs(window);
	if (ldrState == Tries_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopTries.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP TRY SCORERS   ", WHITE);
	}
	else if (ldrState == Goals_STATE)
	{
		window = LeaderboardPositions(window, m_Season.m_TopGoals.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP GOAL SCORERS   ", WHITE);
	}
	else if (ldrState == Metres_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopMetres.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP RUN METRES   ", WHITE);
	}
	else if (ldrState == Points_STATE)
	{
		window = LeaderboardPositions(window, m_Season.m_TopPoints.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP POINT SCORERS   ", WHITE);
	}
	else if (ldrState == Dally_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopPlayers.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "PLAYERS OF THE YEAR   ", WHITE);
	}
	else if (ldrState == Tackles_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopTackles.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP TACKLES   ", WHITE);
	}
	else if (ldrState == State_4020)
	{
		window = LeaderboardPositions(window, m_Season.m_Top4020.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP 40/20  ", WHITE);
	}
	else if (ldrState == KickMetres_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopKickMetres.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP KICK METRES   ", WHITE);
	}
	else if (ldrState == FG_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopFieldGoals.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "TOP FIELD GOALS   ", WHITE);
	}
	else if (ldrState == Steals_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopSteals.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST STEALS   ", WHITE);
	}
	else if (ldrState == ErrorsLdr_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopErrors.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST ERRORS   ", WHITE);
	}
	else if (ldrState == Penalty_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopPenalty.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST PENALTIES CONCEDED  ", WHITE);
	}
	else if (ldrState == RuckError_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopRuckErrors.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST RUCK INFRINGMENTS   ", WHITE);
	}
	else if (ldrState == NoTry_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopNoTries.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST TRIES DISALLOWED   ", WHITE);
	}
	return window;
}

ConsoleWindow SRLGame::ResultsView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window = drawResultTabs(window);
	if (NextRoundCall)
	{
		NextRoundCall = false;
		m_SelectedGame++;
		if (m_SelectedGame >= m_Season.m_Draw.m_Rounds[m_round].m_Games.size())
		{
			m_SelectedGame = 0;
		}
		sortOutResultsScreen();
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
		m_SelectedGame--;
		if (m_SelectedGame < 0)
		{
			m_SelectedGame = m_Season.m_Draw.m_Rounds[m_round].m_Games.size() - 1;
		}
		sortOutResultsScreen();
	}
	if (resultState == Summary_STATE)
	{

	}
	if (resultState == PlayByPlay_STATE)
	{
		if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
		{
			if (m_LineResults > 0)
			{
				m_LineResults--;
			}
		}

		if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEY))
		{
			if (m_LineResults < m_ResultsScreenVector.size() - 1)
			{
				m_LineResults++;
			}
		}

		for (int i = 0; i + m_LineResults < m_ResultsScreenVector.size() && i < 15; i++)
		{
			window.setTextAtPoint(Vector2(1, 3 + i), m_ResultsScreenVector[i + m_LineResults], WHITE);
		}
	}
	return window;
}

ConsoleWindow SRLGame::LeaderboardPositions(ConsoleWindow window, vector<SRLLeaderboardPosition> ldrboard)
{
	if (ldrboard.size() > 10)
	{
		for (int i = 0; i < 10; i++)
		{
			window.setTextAtPoint(Vector2(3, 7 + i), to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points), window._intToColour(i + 2));
		}
	}
	return window;
}

ConsoleWindow SRLGame::SettingsView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawMainMenuTabs(window);
	window.setTextAtPoint(Vector2(0, 2), "GAME SETTINGS", BRIGHTWHITE);
	window = m_SettingsGoalKickerBtn.draw_ui(window);
	if (m_GoalKicker)
	{
		window.setTextAtPoint(Vector2(22, 3), "On", BRIGHTWHITE);
	}
	else
	{
		window.setTextAtPoint(Vector2(22, 3), "Off", BRIGHTWHITE);
	}
	window = m_SettingsWeatherBtn.draw_ui(window);
	if (m_Weather)
	{
		window.setTextAtPoint(Vector2(22, 5), "On", BRIGHTWHITE);
	}
	else
	{
		window.setTextAtPoint(Vector2(22, 5), "Off", BRIGHTWHITE);
	}
	window = m_SettingsStaminaBtn.draw_ui(window);
	if (m_Stamina)
	{
		window.setTextAtPoint(Vector2(22, 7), "On", BRIGHTWHITE);
	}
	else
	{
		window.setTextAtPoint(Vector2(22, 7), "Off", BRIGHTWHITE);
	}
	window = m_SettingsSeasonLengthBtn.draw_ui(window);
	switch (seasonLength)
	{
	case Length_ShortSeason:
		window.setTextAtPoint(Vector2(22, 9), "Short", BRIGHTWHITE);
		break;
	case Length_MediumSeason:
		window.setTextAtPoint(Vector2(22, 9), "Medium", BRIGHTWHITE);
		break;
	case Length_NormalSeason:
		window.setTextAtPoint(Vector2(22, 9), "Normal", BRIGHTWHITE);
		break;
	case Length_LongSeason:
		window.setTextAtPoint(Vector2(22, 9), "Long", BRIGHTWHITE);
		break;
	case Length_ExtremeSeason:
		window.setTextAtPoint(Vector2(22, 9), "Extreme", BRIGHTWHITE);
		break;
	case Length_EnduranceSeason:
		window.setTextAtPoint(Vector2(22, 9), "Endurance", BRIGHTWHITE);
		break;
	}
	return window;
}

ConsoleWindow SRLGame::InfoView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawMainMenuTabs(window);
	window.setTextAtPoint(Vector2(0, 2), "GAME INFORMATION", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 3), "Created by Callum Hands", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 4), "In Association With Freebee Network", BRIGHTWHITE);
	return window;
}

ConsoleWindow SRLGame::drawTabs(ConsoleWindow window)
{
	window = m_SeasonViewBtn.draw_ui(window);
	window = m_LadderViewBtn.draw_ui(window);
	window = m_ResultsViewBtn.draw_ui(window);
	window = m_BettingViewBtn.draw_ui(window);
	window = m_LeaderboardViewBtn.draw_ui(window);
	window = m_MainMenuViewBtn.draw_ui(window);
	window = m_Blank1ViewBtn.draw_ui(window);
	window = m_PreviousRoundViewBtn.draw_ui(window);
	window = m_NextRoundViewBtn.draw_ui(window);
	window = m_SimulateBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::drawBetTabs(ConsoleWindow window)
{
	window = m_BetBtnCurrentRound.draw_ui(window);
	window = m_BetBtnFutures.draw_ui(window);
	window = m_BetBtnAccount.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::drawLeaderboardTabs(ConsoleWindow window)
{
	window = m_LeaderboardBtnMostTries.draw_ui(window);
	window = m_LeaderboardBtnMostGoals.draw_ui(window);
	window = m_LeaderboardBtnMostMetres.draw_ui(window);
	window = m_LeaderboardBtnMostPoints.draw_ui(window);
	window = m_LeaderboardBtnMostDallyM.draw_ui(window);

	window = m_LeaderboardBtnMostFieldGoals.draw_ui(window);
	window = m_LeaderboardBtnMostKickMetres.draw_ui(window);
	window = m_LeaderboardBtnMost4020.draw_ui(window);
	window = m_LeaderboardBtnMostTackles.draw_ui(window);
	window = m_LeaderboardBtnMostSteals.draw_ui(window);

	window = m_LeaderboardBtnMostErrors.draw_ui(window);
	window = m_LeaderboardBtnMostPenalties.draw_ui(window);
	window = m_LeaderboardBtnMostNoTries.draw_ui(window);
	window = m_LeaderboardBtnMostRuckErrors.draw_ui(window);

	return window;
}

ConsoleWindow SRLGame::drawMainMenuTabs(ConsoleWindow window)
{
	window = m_BackSeasonCfgBtn.draw_ui(window);
	window = m_SeasonCfgBtn.draw_ui(window);
	window = m_GameSettingsBtn.draw_ui(window);
	window = m_GameInfoBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::drawResultTabs(ConsoleWindow window)
{
	window = m_GameResultSummaryBtn.draw_ui(window);
	window = m_GameResultPlayByPlayBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::configTabs(ConsoleWindow window)
{
	window = m_BackSeasonCfgBtn.draw_ui(window);
	window = m_AddTeamSeasonCfgBtn.draw_ui(window);
	window = m_RemoveTeamSeasonCfgBtn.draw_ui(window);
	window = m_StartSeasonBtn.draw_ui(window);
	window = m_NextTeamSeasonCfgBtn.draw_ui(window);
	window = m_PrevTeamSeasonCfgBtn.draw_ui(window);
	window = m_GenerateTeamSeasonCfgBtn.draw_ui(window);
	window = m_RandomFillSeasonCfgBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::ErrorPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth-5; i++)
	{
		for (int ii = 5; ii < windowHeight-5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTRED_BRIGHTRED_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), errorMessage, BRIGHTWHITE_BRIGHTRED_BG);
	window = m_ErrorOkViewBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::ConfirmPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", GREEN_GREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), errorMessage, BRIGHTWHITE_GREEN_BG);
	window = m_MenuOkViewBtn.draw_ui(window);
	window = m_MenuCnclViewBtn.draw_ui(window);
	return window;
}

void SRLGame::CalculateOdds()
{
	//CalculateOdds
	for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
	{
		SRLTeam oddsHomeTeam;
		oddsHomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
		SRLTeam oddsAwayTeam;
		oddsAwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
		float oddsHAttack = oddsHomeTeam.totalAttackStat();
		float oddsHDefence = oddsHomeTeam.totalDefenceStat();
		float oddsHSpeed = oddsHomeTeam.totalSpeedStat();
		float totalH = oddsHAttack + oddsHDefence + oddsHSpeed + oddsHomeTeam.totalHandlingStat() + oddsHomeTeam.totalKickStat();
		float oddsAAttack = oddsAwayTeam.totalAttackStat();
		float oddsADefence = oddsAwayTeam.totalDefenceStat();
		float oddsASpeed = oddsAwayTeam.totalSpeedStat();
		float totalA = oddsAAttack + oddsADefence + oddsASpeed + oddsAwayTeam.totalHandlingStat() + oddsAwayTeam.totalKickStat();
		float totalStats = totalH + totalA;

		float percentH = (totalH / totalStats) * 100;
		float percentA = (totalA / totalStats) * 100;
		int winsH = 0;
		int winsA = 0;
		for (int ii = 0; ii < m_Season.m_Ladder.m_Ladder.size(); ii++)
		{
			if (m_Season.m_Ladder.m_Ladder[i].teamName == oddsHomeTeam.getName())
			{
				winsH = m_Season.m_Ladder.m_Ladder[i].won;
			}
			if (m_Season.m_Ladder.m_Ladder[i].teamName == oddsAwayTeam.getName())
			{
				winsA = m_Season.m_Ladder.m_Ladder[i].won;
			}
		}

		int winDiff = winsH - winsA;
		if (winDiff > 0)
		{
			percentH += winDiff * 2;
			percentA -= winDiff * 2;
		}
		if (winDiff < 0)
		{
			percentH -= winDiff * 2;
			percentA += winDiff * 2;
		}

		percentH *= 2;
		percentA *= 2;

		int oddsHCents = 280 - percentH;
		int oddsACents = 280 - percentA;

		if (oddsHCents < 101)
		{
			oddsHCents = 101;
		}
		if (oddsACents < 101)
		{
			oddsACents = 101;
		}
		m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamOdds = SRLBetPrice(oddsHCents / 100, oddsHCents % 100);
		m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamOdds = SRLBetPrice(oddsACents / 100, oddsACents % 100);
	}
}

void SRLGame::SimulateGames()
{
	int roundsSimulated = 0;
	while (Simulate)
	{
		if (m_round < m_roundToSimulate)
		{
			Simulate = false;
			if (roundsSimulated == 0)
			{
				errorCall = true;
				errorMessage = "Already Simulated This Round";
			}
			return;
		}
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
		{
			roundsSimulated++;
			SRLGameManager m_srlmanager;

			SRLTeam HomeTeam;
			HomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
			SRLTeam AwayTeam;
			AwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
			m_srlmanager.setTeams(HomeTeam, AwayTeam);
			m_srlmanager.teamHaveMainGoalKickers(m_GoalKicker);
			m_srlmanager.weatherEffects(m_Weather);
			m_srlmanager.staminaEffect(m_Stamina);
			try
			{
				m_srlmanager.addTeamLineupsPlayByPlay();
				m_srlmanager.addStartTimePlay();
				while (m_srlmanager.getMinutesPassed() < 80 || m_srlmanager.isTied())
				{
					m_srlmanager.play();
				}
				m_srlmanager.addFullTimePlay();
			}
			catch (exception ex)
			{
				//TODO
			}
			m_srlmanager.endStats();
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore = m_srlmanager.getHomeScore();
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore = m_srlmanager.getAwayScore();

			if (m_srlmanager.getHomeScore() > m_srlmanager.getAwayScore())
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam;
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].LosingTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam;
			}
			else
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam;
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].LosingTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam;
			}
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].ResultPlayByPlay = m_srlmanager.getPlayByPlay();

			for (int i = 0; i < m_srlmanager.getHomeTeam().getPlayers().size(); i++)
			{
				m_Season.m_TopPlayers.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getDallyMPointsWorth());
				m_Season.m_TopTries.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getTries());
				m_Season.m_TopGoals.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getGoals());
				m_Season.m_TopPoints.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getPoints());
				m_Season.m_TopMetres.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getMetres());
				m_Season.m_TopFieldGoals.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getFieldGoals());
				m_Season.m_Top4020.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].get4020());
				m_Season.m_TopTackles.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getTackles());
				m_Season.m_TopKickMetres.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getKickMetres());
				m_Season.m_TopErrors.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getErrors());
				m_Season.m_TopPenalty.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getPenalty());
				m_Season.m_TopSteals.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getSteals());
				m_Season.m_TopNoTries.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getNoTry());
				m_Season.m_TopRuckErrors.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getRuckErrors());
			}
			for (int i = 0; i < m_srlmanager.getAwayTeam().getPlayers().size(); i++)
			{
				m_Season.m_TopPlayers.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getDallyMPointsWorth());
				m_Season.m_TopTries.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getTries());
				m_Season.m_TopGoals.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getGoals());
				m_Season.m_TopPoints.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getPoints());
				m_Season.m_TopMetres.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getMetres());
				m_Season.m_TopFieldGoals.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getFieldGoals());
				m_Season.m_Top4020.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].get4020());
				m_Season.m_TopTackles.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getTackles());
				m_Season.m_TopKickMetres.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getKickMetres());
				m_Season.m_TopErrors.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getErrors());
				m_Season.m_TopPenalty.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getPenalty());
				m_Season.m_TopSteals.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getSteals());
				m_Season.m_TopNoTries.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getNoTry());
				m_Season.m_TopRuckErrors.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getRuckErrors());
			}
			m_Season.m_TopPlayers.orderShortlist();
			m_Season.m_TopTries.orderShortlist();
			m_Season.m_TopGoals.orderShortlist();
			m_Season.m_TopPoints.orderShortlist();
			m_Season.m_TopMetres.orderShortlist();
			m_Season.m_TopFieldGoals.orderShortlist();
			m_Season.m_Top4020.orderShortlist();
			m_Season.m_TopTackles.orderShortlist();
			m_Season.m_TopKickMetres.orderShortlist();
			m_Season.m_TopErrors.orderShortlist();
			m_Season.m_TopPenalty.orderShortlist();
			m_Season.m_TopSteals.orderShortlist();
			m_Season.m_TopNoTries.orderShortlist();
			m_Season.m_TopRuckErrors.orderShortlist();

			if (!finals)
			{
				for (int ii = 0; ii < m_Season.m_Ladder.m_Ladder.size(); ii++)
				{
					if (m_Season.m_Ladder.m_Ladder[ii].teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam)
					{
						m_Season.m_Ladder.m_Ladder[ii].played++;
						if (m_srlmanager.getHomeScore() > m_srlmanager.getAwayScore())
						{
							m_Season.m_Ladder.m_Ladder[ii].won++;
							m_Season.m_Ladder.m_Ladder[ii].points += 2;
						}
						else
						{
							m_Season.m_Ladder.m_Ladder[ii].lost++;
						}
						m_Season.m_Ladder.m_Ladder[ii].pointsFor += m_srlmanager.getHomeScore();
						m_Season.m_Ladder.m_Ladder[ii].pointsAgainst += m_srlmanager.getAwayScore();
						m_Season.m_Ladder.m_Ladder[ii].pointsDifference = m_Season.m_Ladder.m_Ladder[ii].pointsFor - m_Season.m_Ladder.m_Ladder[ii].pointsAgainst;
					}
					else if (m_Season.m_Ladder.m_Ladder[ii].teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam)
					{
						m_Season.m_Ladder.m_Ladder[ii].played++;
						if (m_srlmanager.getHomeScore() < m_srlmanager.getAwayScore())
						{
							m_Season.m_Ladder.m_Ladder[ii].won++;
							m_Season.m_Ladder.m_Ladder[ii].points += 2;
						}
						else
						{
							m_Season.m_Ladder.m_Ladder[ii].lost++;
						}
						m_Season.m_Ladder.m_Ladder[ii].pointsAgainst += m_srlmanager.getHomeScore();
						m_Season.m_Ladder.m_Ladder[ii].pointsFor += m_srlmanager.getAwayScore();
						m_Season.m_Ladder.m_Ladder[ii].pointsDifference = m_Season.m_Ladder.m_Ladder[ii].pointsFor - m_Season.m_Ladder.m_Ladder[ii].pointsAgainst;
					}
				}
			}

		}
		if (!finals)
		{
			m_Season.m_Ladder.sortLadder();
		}
		//Simulate = false;
		m_roundToSimulate++;
		if (m_roundToSimulate >= m_Season.m_Draw.m_Rounds.size())
		{
			finals = true;
			//THAT WAS GRAND FINAL, FINISH SEASON
			if (m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].m_Games.size() == 1)
			{

			}
			else
			{
				if (m_roundToSimulate == BaseSeasonGames)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[2].teamName)); //2v3
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[4].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //5v8
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[5].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //6v7
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 1)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //4v5
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //3v6
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v3
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam));//2v4
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam));//1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
			}
		}
		if (m_roundToSimulate < BaseSeasonGames + 4)
		{
			CalculateOdds();
		}
	}
}

void SRLGame::sortOutResultsScreen()
{
	m_ResultsScreenVector.clear();
	vector<string> temp = m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].ResultPlayByPlay;
	for (int i = 0; i < temp.size(); i++)
	{
		while (temp[i].length() > 55)
		{
			m_ResultsScreenVector.push_back(temp[i].substr(0,55));
			temp[i].erase(temp[i].begin(), temp[i].begin() + 55);
		}
		m_ResultsScreenVector.push_back(temp[i]);
	}
	m_LineResults = 0;
}

void SRLLadder::sortLadder()
{
	for (int i = 0; i < m_Ladder.size(); i++)
	{
		for (int ii = i + 1; ii < m_Ladder.size(); ii++)
		{
			if (m_Ladder[ii].points > m_Ladder[i].points)
			{
				SRLLadderPosition temp;
				temp = m_Ladder[i];
				m_Ladder[i] = m_Ladder[ii];
				m_Ladder[ii] = temp;
				i = 0;
				ii = i + 1;
			}
			else if (m_Ladder[ii].points == m_Ladder[i].points && m_Ladder[ii].pointsDifference > m_Ladder[i].pointsDifference)
			{
				SRLLadderPosition temp;
				temp = m_Ladder[i];
				m_Ladder[i] = m_Ladder[ii];
				m_Ladder[ii] = temp;
				i = 0;
				ii = i + 1;
			}
		}
	}
}

string SRLBetPrice::ReturnPrice()
{
	string priceStr = "$" + to_string(dollars);
	string centsStr = to_string(cents);
	if (centsStr.length() == 1)
	{
		centsStr = "0" + centsStr;
	}
	return priceStr + "." + centsStr;
}

void SRLLeaderboard::addToShortlist(string playerName, string teamName, int points)
{
	for (int i = 0; i < shortlist.size(); i++)
	{
		if (shortlist[i].TeamName == teamName && shortlist[i].Player == playerName)
		{
			shortlist[i].points += points;
			return;
		}
	}
	SRLLeaderboardPosition newPosition;
	newPosition.Player = playerName;
	newPosition.TeamName = teamName;
	newPosition.points = points;
	shortlist.push_back(newPosition);
}

void SRLLeaderboard::orderShortlist()
{
	for (int i = 0; i < shortlist.size(); i++)
	{
		for (int ii = i + 1; ii < shortlist.size(); ii++)
		{
			if (shortlist[ii].points > shortlist[i].points)
			{
				SRLLeaderboardPosition temp;
				temp = shortlist[i];
				shortlist[i] = shortlist[ii];
				shortlist[ii] = temp;
				i = 0;
				ii = i + 1;
			}
		}
	}
}
