#include "SRL.h"

#pragma region Static

AssetsClass SRLGame::astVars = AssetsClass();
GameStateSYDE SRLGame::currentState = Unknown_STATE;
GameStateSYDE SRLGame::newState = FMODSplashScreenState;
GameStateBettingSYDE SRLGame::bettingState = CurrentRound_STATE;
GameStateLeaderboardSYDE SRLGame::ldrState = Tries_State;
GameStateResultSYDE SRLGame::resultState = Summary_STATE;
GameStateSettingsSYDE SRLGame::settingsState = SeasonSettings_STATE;
GameStateInDepthView SRLGame::inDepthState = NormalInDepthView;
SeasonDrawViewState SRLGame::drawViewState = SeasonDrawMainView;
SRLPriorBets_State SRLGame::priorBetsState = IndividualGameBets_State;
SRLSeasonLength SRLGame::seasonLength = Length_NormalSeason;
bool SRLGame::SeasonStart = false;
bool SRLGame::SeasonStartCall = false;
bool SRLGame::NextRoundCall = false;
bool SRLGame::PrevRoundCall = false;
bool SRLGame::addCall = false;
bool SRLGame::removeCall = false;
bool SRLGame::Simulate = false;
bool SRLGame::SimulateCall = false;
bool SRLGame::generateCall = false;
bool SRLGame::generateStartCall = false;
bool SRLGame::randomFillCall = false;
bool SRLGame::errorCall = false;
bool SRLGame::menuCall = false;
bool SRLGame::m_GoalKicker = true;
bool SRLGame::m_Weather = true;
bool SRLGame::m_Stamina = true;
//WOULD PREFER TO BE OFF BUT FOR SOME REASON MAIN BG DOESN"T LOAD WHEN IT IS SO RIP
bool SRLGame::m_ExtraTime = true;
bool SRLGame::m_Injuries = true;
bool SRLGame::m_SinBins = true;
bool SRLGame::m_ResultsTabCall = false;
bool SRLGame::soundTrackOn = true;
bool SRLGame::homeTeamBet = false;
bool SRLGame::betPlaceCall = false;
bool SRLGame::premiershipBet = false;
bool SRLGame::m_SeasonEvents = true;
bool SRLGame::headlineCall = false;
bool SRLGame::keyPadCall = false;
bool SRLGame::playerCall = false;
int SRLGame::playerClicked = 0;
float SRLGame::m_ScrollingSpeed = 1.0f;
string SRLGame::customAmountStr = "";
SRLBetPrice SRLGame::m_BetAmount = SRLBetPrice(10, 0);
int SRLGame::gameNumberBet = 0;
int SRLGame::priorBetNumberLine = 0;
string SRLGame::errorMessage = "";
int SRLGame::articleClicked = 0;
string SRLGame::betTag = "";
bool SRLGame::betCall = false;
bool SRLGame::exportCall = false;
bool SRLGame::exportConfirmedCall = false;
bool SRLGame::formatCall = false;
bool SRLGame::formatConfirmedCall = false;
bool SRLGame::exitCall = false;
bool SRLGame::exitConfirmedCall = false;
bool SRLGame::randomizeCall = false;
bool SRLGame::randomizeConfirmedCall = false;
bool SRLGame::finalsSystemCall = false;
bool SRLGame::m_FaceOffLimit = true;
vector<string> SRLGame::AchievementStrings = vector<string>();
ArticleViewingState SRLGame::articleState = HeadlinesState;

SRLSoundtrack SRLGame::m_GamePlaySoundtrack = SRLSoundtrack();

#pragma endregion

vector<string> Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

#pragma region ButtonVoids

void FinalsSystemClick()
{
	SRLGame::finalsSystemCall = true;
}

void MainDrawViewClick()
{
	SRLGame::drawViewState = SeasonDrawMainView;
}

void TipMasterViewClick()
{
	SRLGame::drawViewState = TippingMasterView;
}

void InGameSettingsViewClick()
{
	SRLGame::drawViewState = GameSettingsInSeasonView;
}

void FeaturedMatchViewClick()
{
	SRLGame::drawViewState = FeaturedMatchView;
}

void RandomizeButtonClick()
{
	SRLGame::randomizeCall = true;
}

void RandomizeOKClick()
{
	SRLGame::randomizeConfirmedCall = true;
}
void RandomizeCNCLClick()
{
	SRLGame::randomizeCall = false;
}

void ExitButtonClick()
{
	SRLGame::exitCall = true;
}

void ExitOKClick()
{
	SRLGame::exitConfirmedCall = true;
}
void ExitCNCLClick()
{
	SRLGame::exitCall = false;
}

void ExportButtonClick()
{
	SRLGame::exportCall = true;
}

void ExportOKClick()
{
	SRLGame::exportConfirmedCall = true;
}
void ExportCNCLClick()
{
	SRLGame::exportCall = false;
}

void FormatButtonClick()
{
	SRLGame::formatCall = true;
}

void FormatOKClick()
{
	SRLGame::formatConfirmedCall = true;
}
void FormatCNCLClick()
{
	SRLGame::formatCall = false;
}

void PlayerClick()
{
	SRLGame::playerCall = true;
	SRLGame::playerClicked = stoi(SYDEClickableButton::getLastButtonTag());
}

void InDepthTeamListViewClick()
{
	SRLGame::inDepthState = TeamListViewState;
}
void InDepthTeamListBackClick()
{
	SRLGame::inDepthState = NormalInDepthView;
}

void InDepthTeamViewClick()
{
	SRLGame::newState = TeamInDepthViewState;
}

void InDepthBackClick()
{
	SRLGame::newState = MainMenu_STATE;
}

void KeypadClick1()
{
	SRLGame::addCustomStrString("1");
}
void KeypadClick2()
{
	SRLGame::addCustomStrString("2");
}

void KeypadClick3()
{
	SRLGame::addCustomStrString("3");
}

void KeypadClick4()
{
	SRLGame::addCustomStrString("4");
}

void KeypadClick5()
{
	SRLGame::addCustomStrString("5");
}

void KeypadClick6()
{
	SRLGame::addCustomStrString("6");
}

void KeypadClick7()
{
	SRLGame::addCustomStrString("7");
}

void KeypadClick8()
{
	SRLGame::addCustomStrString("8");
}

void KeypadClick9()
{
	SRLGame::addCustomStrString("9");
}

void KeypadClick0()
{
	SRLGame::addCustomStrString("0");
}

void KeypadClickDOT()
{
	SRLGame::addCustomStrString(".");
}

void KeypadClickClear()
{
	SRLGame::removeCustomStrString();
}

void KeypadClickOK()
{
	SRLGame::keyPadCall = false;
	try
	{
		vector<string> bets = Split(SRLGame::customAmountStr, '.');
		SRLGame::m_BetAmount.dollars = stoi(bets[0]);
		if (bets.size() >= 2)
		{
			SRLGame::m_BetAmount.cents = stoi(bets[1]);
			if (SRLGame::m_BetAmount.cents < 10)
			{
				SRLGame::m_BetAmount.cents *= 10;
			}
		}
		else
		{
			SRLGame::m_BetAmount.cents = 0;
		}
	}
	catch (exception e)
	{
		SRLGame::errorCall = true;
		SRLGame::errorMessage = "Invalid betting amount";
		return;
	}
	if (SRLGame::m_BetAmount.dollars == 0 && SRLGame::m_BetAmount.cents == 0)
	{
		SRLGame::errorCall = true;
		SRLGame::errorMessage = "Bet must be greater than $0.00";
		return;
	}
	SRLGame::errorMessage = "Confirm " + SRLGame::m_BetAmount.ReturnPrice() + " Bet On " + SRLGame::betTag + "?";
	SRLGame::betCall = true;
}

void KeypadClickCNCL()
{
	SRLGame::keyPadCall = false;
}

void ExhibitionMatchClick()
{
	if (SRLGame::currentState = MainMenu_STATE)
	{
		SRLGame::newState = Exhibition_LoadState;
	}
}

void ToggleEventsClick()
{
	SRLGame::m_SeasonEvents = !SRLGame::m_SeasonEvents;
}

void ArticleBackClick()
{
	SRLGame::articleState = HeadlinesState;
}

void MusicVolumeClick()
{
	if (BaseSYDESoundSettings::getDefaultVolumeState() == SYDE_VOLUME_OFF)
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_LOW);
	else if (BaseSYDESoundSettings::getDefaultVolumeState() == SYDE_VOLUME_LOW)
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_NML);
	else if (BaseSYDESoundSettings::getDefaultVolumeState() == SYDE_VOLUME_NML)
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_MED);
	else if (BaseSYDESoundSettings::getDefaultVolumeState() == SYDE_VOLUME_MED)
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_HIG);
	else if (BaseSYDESoundSettings::getDefaultVolumeState() == SYDE_VOLUME_HIG)
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_OFF);

	SRLGame::saveGameSettings();
}

void CustomBetClick()
{
	SRLGame::customAmountStr = "";
	SRLGame::betTag = SYDEClickableButton::getLastButtonTag();
	vector<string> bets = Split(SRLGame::betTag, ';');
	SRLGame::betTag = bets[4];
	SRLGame::homeTeamBet = bets[3] == "H";
	SRLGame::premiershipBet = bets[3] == "P";
	SRLGame::gameNumberBet = stoi(bets[0]);
	SRLGame::keyPadCall = true;
}

void BetMatchClick()
{
	SRLGame::betTag = SYDEClickableButton::getLastButtonTag();
	vector<string> bets = Split(SRLGame::betTag, ';');
	SRLGame::betTag = bets[4];
	SRLGame::m_BetAmount.dollars = stoi(bets[1]);
	SRLGame::m_BetAmount.cents = stoi(bets[2]);
	SRLGame::homeTeamBet = bets[3] == "H";
	SRLGame::premiershipBet = bets[3] == "P";
	SRLGame::gameNumberBet = stoi(bets[0]);
	SRLGame::betCall = true;

	SRLGame::errorMessage = "Confirm " + SRLGame::m_BetAmount.ReturnPrice() +" Bet On " + SRLGame::betTag + "?";
}

void ArticleClick()
{
	SRLGame::articleClicked = stoi(SYDEClickableButton::getLastButtonTag());
	SRLGame::headlineCall = true;
}

void SoundTrackClick()
{
	if (SRLGame::soundTrackOn)
	{
		SRLGame::m_GamePlaySoundtrack.stop();
	}
	else
	{
		SRLGame::m_GamePlaySoundtrack.start();
	}
	SRLGame::soundTrackOn = !SRLGame::soundTrackOn;
	SRLGame::saveGameSettings();
}

void SimulateClick()
{
	if (SRLGame::currentState == SeasonModeState)
	{
		SRLGame::SimulateCall = true;
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

void betCNCLClick()
{
	SRLGame::betCall = false;
}
void betOKClick()
{
	SRLGame::betPlaceCall = true;
	SRLGame::betCall = false;
}

void newsViewClick()
{
	SRLGame::newState = NewsViewState;
}

void SeasonModeClick()
{
	SRLGame::newState = SeasonConfig_State;
}

void SeasonModeStartClick()
{
	SRLGame::SeasonStartCall = true;
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
void PastBetViewClick()
{
	SRLGame::bettingState = ViewBets_STATE;
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
void SinBinLdrViewClick()
{
	SRLGame::ldrState = SinBin_State;
}
void SendOffLdrViewClick()
{
	SRLGame::ldrState = SendOff_State;
}
void InjuryLdrViewClick()
{
	SRLGame::ldrState = Injury_State;
}
void SeasonSettingsViewClick()
{
	SRLGame::settingsState = SeasonSettings_STATE;
}
void NormalSettingsViewClick()
{
	SRLGame::settingsState = NormalSettings_STATE;
}

void GenerateTeamViewClick()
{
	SRLGame::generateCall = true;
	SRLGame::generateStartCall = true;
}
void ToggleSinBinClick()
{
	SRLGame::m_SinBins = !SRLGame::m_SinBins;
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
	SRLGame::m_ResultsTabCall = true;
	SRLGame::resultState = Summary_STATE;
}

void PlayByPlayRsltViewClick()
{
	SRLGame::m_ResultsTabCall = true;
	SRLGame::resultState = PlayByPlay_STATE;
}

void NextRoundViewClick()
{
	if (SRLGame::currentState == SeasonModeState || SRLGame::currentState == ResultsViewState || SRLGame::currentState == SeasonConfig_State || SRLGame::currentState == TeamInDepthViewState)
	{
		SRLGame::NextRoundCall = true;
	}
}

void PrevRoundViewClick()
{
	if (SRLGame::currentState == SeasonModeState || SRLGame::currentState == ResultsViewState || SRLGame::currentState == SeasonConfig_State || SRLGame::currentState == TeamInDepthViewState)
	{
		SRLGame::PrevRoundCall = true;
	}
}

void MainMenuViewClick()
{
	if (SRLGame::currentState == MainMenu_STATE || SRLGame::currentState == InformationState || SRLGame::currentState == SettingsState)
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
void ExtraTimeViewClick()
{
	SRLGame::m_ExtraTime = !SRLGame::m_ExtraTime;
}
void InjuriesViewClick()
{
	SRLGame::m_Injuries = !SRLGame::m_Injuries;
}
void SettingsLengthViewClick()
{
	if (SRLGame::seasonLength == Length_ShortSeason)
	{
		SRLGame::seasonLength = Length_RoundRobin;
	}
	else if (SRLGame::seasonLength == Length_RoundRobin)
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

void nextSongClick()
{
	if (SRLGame::soundTrackOn)
	{
		SRLGame::m_GamePlaySoundtrack.next();
		SRLGame::m_GamePlaySoundtrack.play();
	}
}

void GameResultsViewClick()
{
	SRLGame::priorBetsState = IndividualGameBets_State;
	SRLGame::priorBetNumberLine = 0;
}

void PremiershipResultsViewClick()
{
	SRLGame::priorBetsState = PremiershipWinnerBets_State;
	SRLGame::priorBetNumberLine = 0;
}

void FeaturedMatchSwitchViewClick()
{
	if (SRLGame::drawViewState == FeaturedMatchView)
	{
		SRLGame::drawViewState = FeaturedMatchTeamListView;
	}
	else
	{
		SRLGame::drawViewState = FeaturedMatchView;
	}
}

#pragma endregion

void SRLGame::init()
{
	loadGameSettings();

	maxScrollTickTime = maxScrollTickTime / m_ScrollingSpeed;

#pragma region SoundTrack

	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\01MeetMeOneDay.mp3", "Meet Me One Day", "Rit@lin4Kidz","", 168);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\02IThink.mp3", "I Think, Therefore I Suck", "Handsprime", "(Rit@lin4Kidz Remix)", 96);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\03Waterfall.mp3", "Waterfall", "Handsprime", "(Rit@lin4Kidz Remix)", 136);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\04LetMeShowYouARemix.mp3", "Let Me Show You A Remix", "Rit@lin4Kidz", "", 89);
	m_GamePlaySoundtrack.setYPos(14);
	m_GamePlaySoundtrack.setOn(soundTrackOn);
	if (soundTrackOn)
	{
		m_GamePlaySoundtrack.start();
	}
	m_GamePlaySoundtrack.shuffleSongs(true, false);

#pragma endregion

#pragma region SoundTrackSettings

	m_SoundTrackOnBtn =SYDEClickableButton(" Background Music:", Vector2(3, 4), Vector2(18, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SoundTrackOnBtn.setHighLight(RED);
	m_SoundTrackOnBtn.SetFunc(SoundTrackClick);

	m_SoundTrackNextBtn = SYDEClickableButton(" Current Song:", Vector2(7, 6), Vector2(14, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SoundTrackNextBtn.setHighLight(RED);
	m_SoundTrackNextBtn.SetFunc(nextSongClick);

	m_SoundTrackVolume = SYDEClickableButton(" Music Volume:", Vector2(7, 8), Vector2(14, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SoundTrackVolume.setHighLight(RED);
	m_SoundTrackVolume.SetFunc(MusicVolumeClick);

#pragma endregion


#pragma region SeasonOptions
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


	m_FeatureViewBtn = SYDEClickableButton(" Featured", Vector2(15, 18), Vector2(10, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_FeatureViewBtn.setHighLight(RED);
	m_FeatureViewBtn.SetFunc(FeaturedMatchViewClick);
	m_MainDrawViewBtn = SYDEClickableButton(" Main Draw", Vector2(3, 18), Vector2(11, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_MainDrawViewBtn.setHighLight(RED);
	m_MainDrawViewBtn.SetFunc(MainDrawViewClick);

	m_MainSettingsViewBtn = SYDEClickableButton(" Settings", Vector2(26, 18), Vector2(10, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_MainSettingsViewBtn.setHighLight(RED);
	m_MainSettingsViewBtn.SetFunc(InGameSettingsViewClick);

	m_TipMasterViewBtn = SYDEClickableButton(" TipMaster", Vector2(37, 18), Vector2(11, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_TipMasterViewBtn.setHighLight(RED);
	m_TipMasterViewBtn.SetFunc(TipMasterViewClick);

	m_FeatureSwitchViewBtn = SYDEClickableButton(" Alt View ", Vector2(25, 16), Vector2(10, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_FeatureSwitchViewBtn.setHighLight(RED);
	m_FeatureSwitchViewBtn.SetFunc(FeaturedMatchSwitchViewClick);


	//BLANK BUTTONS EDIT LATER
	m_NewsViewBtn = SYDEClickableButton("Season News ", Vector2(12, 19), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_NewsViewBtn.setHighLight(RED);
	m_NewsViewBtn.SetFunc(newsViewClick);
	m_PreviousRoundViewBtn = SYDEClickableButton("  Previous  ", Vector2(24, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_PreviousRoundViewBtn.setHighLight(RED);
	m_PreviousRoundViewBtn.SetFunc(PrevRoundViewClick);
	m_NextRoundViewBtn = SYDEClickableButton("    Next    ", Vector2(36, 19), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_NextRoundViewBtn.setHighLight(RED);
	m_NextRoundViewBtn.SetFunc(NextRoundViewClick);
	m_SimulateBtn = SYDEClickableButton("  Simulate  ", Vector2(48, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_SimulateBtn.setHighLight(RED);
	m_SimulateBtn.SetFunc(SimulateClick);

#pragma endregion

#pragma region BettingOptions
	m_BetBtnCurrentRound = SYDEClickableButton(" Current Round  ", Vector2(0, 2), Vector2(15, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnCurrentRound.setHighLight(RED);
	m_BetBtnCurrentRound.SetFunc(CurrentRoundViewClick);
	m_BetBtnFutures = SYDEClickableButton("    Futures     ", Vector2(15, 2), Vector2(15, 1), BRIGHTWHITE_BRIGHTGREEN_BG, false);
	m_BetBtnFutures.setHighLight(RED);
	m_BetBtnFutures.SetFunc(FuturesViewClick);
	m_BetBtnViewBets = SYDEClickableButton("Betting History", Vector2(30, 2), Vector2(15, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnViewBets.setHighLight(RED);
	m_BetBtnViewBets.SetFunc(PastBetViewClick);
	m_BetBtnAccount = SYDEClickableButton("     Account    ", Vector2(45, 2), Vector2(15, 1), BRIGHTWHITE_BRIGHTGREEN_BG, false);
	m_BetBtnAccount.setHighLight(RED);
	m_BetBtnAccount.SetFunc(AccountViewClick);

	m_BetOkViewBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BetOkViewBtn.setHighLight(RED);
	m_BetOkViewBtn.SetFunc(betOKClick);

	m_BetCnclViewBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BetCnclViewBtn.setHighLight(RED);
	m_BetCnclViewBtn.SetFunc(betCNCLClick);

	m_PriorBetsGameBtn = SYDEClickableButton("    Individual Game Results    ", Vector2(0, 3), Vector2(30, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_PriorBetsGameBtn.setHighLight(RED);
	m_PriorBetsGameBtn.SetFunc(GameResultsViewClick);

	m_PriorBetsPremiershipBtn = SYDEClickableButton("    Premiership Winner Bets    ", Vector2(30, 3), Vector2(30, 1), BRIGHTWHITE_RED_BG, false);
	m_PriorBetsPremiershipBtn.setHighLight(RED);
	m_PriorBetsPremiershipBtn.SetFunc(PremiershipResultsViewClick);
#pragma endregion

#pragma region SeasonConfig
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


	m_BackHeadline = SYDEClickableButton("BACK", Vector2(2, 17), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BackHeadline.setHighLight(RED);
	m_BackHeadline.SetFunc(ArticleBackClick);
#pragma endregion

#pragma region LeaderboardOptions
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

	m_LeaderboardBtnMostSinBin = SYDEClickableButton("   Sin Bin  ", Vector2(12, 18), Vector2(12, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_LeaderboardBtnMostSinBin.setHighLight(RED);
	m_LeaderboardBtnMostSinBin.SetFunc(SinBinLdrViewClick);
	m_LeaderboardBtnMostSendOff = SYDEClickableButton("  Send Off  ", Vector2(24, 18), Vector2(12, 1), BRIGHTWHITE_RED_BG, false);
	m_LeaderboardBtnMostSendOff.setHighLight(RED);
	m_LeaderboardBtnMostSendOff.SetFunc(SendOffLdrViewClick);
	m_LeaderboardBtnMostInjuries = SYDEClickableButton(" Top Injury ", Vector2(36, 18), Vector2(12, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_LeaderboardBtnMostInjuries.setHighLight(RED);
	m_LeaderboardBtnMostInjuries.SetFunc(InjuryLdrViewClick);
#pragma endregion

#pragma region MainMenuOptions
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

	m_TeamInDepthView = SYDEClickableButton(" In Depth Team View ", Vector2(0, 19), Vector2(20, 1), BLACK_WHITE_BG, false);
	m_TeamInDepthView.setHighLight(RED);
	m_TeamInDepthView.SetFunc(InDepthTeamViewClick);

	m_ExitGame = SYDEClickableButton("  Exit Application  ", Vector2(40, 19), Vector2(20, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_ExitGame.setHighLight(RED);
	m_ExitGame.SetFunc(ExitButtonClick);

	m_ExitGameOK = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ExitGameOK.setHighLight(RED);
	m_ExitGameOK.SetFunc(ExitOKClick);

	m_ExitGameCNL = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ExitGameCNL.setHighLight(RED);
	m_ExitGameCNL.SetFunc(ExitCNCLClick);

#pragma endregion

#pragma region GameSettings

	//RESULTS PAGE
	m_GameSettingsSeasonBtn = SYDEClickableButton("       Season Settings        ", Vector2(0, 2), Vector2(30, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_GameSettingsSeasonBtn.setHighLight(RED);
	m_GameSettingsSeasonBtn.SetFunc(SeasonSettingsViewClick);
	m_GameSettingsNormalBtn = SYDEClickableButton("     Application Settings     ", Vector2(30, 2), Vector2(30, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_GameSettingsNormalBtn.setHighLight(RED);
	m_GameSettingsNormalBtn.SetFunc(NormalSettingsViewClick);

#pragma endregion


#pragma region ResultsOptions
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

	m_ExportBtn = SYDEClickableButton(" Export", Vector2(50, 18), Vector2(8, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_ExportBtn.setHighLight(RED);
	m_ExportBtn.SetFunc(ExportButtonClick);

	m_ExportOKBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ExportOKBtn.setHighLight(RED);
	m_ExportOKBtn.SetFunc(ExportOKClick);

	m_ExportCNCLBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ExportCNCLBtn.setHighLight(RED);
	m_ExportCNCLBtn.SetFunc(ExportCNCLClick);

#pragma endregion

#pragma region GameSettingsOptions
	//SETTINGS
	m_SettingsGoalKickerBtn = SYDEClickableButton(" Main Goal Kicker:", Vector2(3, 4), Vector2(18, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsGoalKickerBtn.setHighLight(RED);
	m_SettingsGoalKickerBtn.SetFunc(ToggleKickerClick);

	m_SettingsWeatherBtn = SYDEClickableButton(" Weather:", Vector2(12, 6), Vector2(9, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsWeatherBtn.setHighLight(RED);
	m_SettingsWeatherBtn.SetFunc(ToggleWeatherClick);

	m_SettingsStaminaBtn = SYDEClickableButton(" Stamina:", Vector2(12, 8), Vector2(9, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsStaminaBtn.setHighLight(RED);
	m_SettingsStaminaBtn.SetFunc(ToggleStaminaClick);

	m_SettingsSeasonLengthBtn = SYDEClickableButton(" Season Length:", Vector2(6, 10), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsSeasonLengthBtn.setHighLight(RED);
	m_SettingsSeasonLengthBtn.SetFunc(SettingsLengthViewClick);

	m_SettingsExtraTimeBtn = SYDEClickableButton(" Extra Time:", Vector2(9, 12), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsExtraTimeBtn.setHighLight(RED);
	m_SettingsExtraTimeBtn.SetFunc(ExtraTimeViewClick);

	m_SettingsInjuryBtn = SYDEClickableButton(" Injuries:", Vector2(11, 14), Vector2(10, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsInjuryBtn.setHighLight(RED);
	m_SettingsInjuryBtn.SetFunc(InjuriesViewClick);

	m_SettingsSinBinBtn = SYDEClickableButton(" Sin Bins:", Vector2(11, 16), Vector2(10, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsSinBinBtn.setHighLight(RED);
	m_SettingsSinBinBtn.SetFunc(ToggleSinBinClick);

	m_SettingsEventsBtn = SYDEClickableButton(" Season Events:", Vector2(36, 4), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsEventsBtn.setHighLight(RED);
	m_SettingsEventsBtn.SetFunc(ToggleEventsClick);

	m_SettingsFinalsBtn = SYDEClickableButton(" Finals Series:", Vector2(6, 18), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsFinalsBtn.setHighLight(RED);
	m_SettingsFinalsBtn.SetFunc(FinalsSystemClick);

	m_FormatTeamsBtn = SYDEClickableButton(" Format Teams ", Vector2(7, 10), Vector2(14, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_FormatTeamsBtn.setHighLight(RED);
	m_FormatTeamsBtn.SetFunc(FormatButtonClick);


	m_FormatTeamsOKBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_FormatTeamsOKBtn.setHighLight(RED);
	m_FormatTeamsOKBtn.SetFunc(FormatOKClick);

	m_FormatTeamsCNCLBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_FormatTeamsCNCLBtn.setHighLight(RED);
	m_FormatTeamsCNCLBtn.SetFunc(FormatCNCLClick);
#pragma endregion

#pragma region keypad
	m_KeypadBtn_1 = SYDEClickableButton("        1", Vector2(18, 11), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_1.setHighLight(RED);
	m_KeypadBtn_1.SetFunc(KeypadClick1);
	m_KeypadBtn_1._WrapText(true);

	m_KeypadBtn_2 = SYDEClickableButton("        2", Vector2(11, 11), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_2.setHighLight(RED);
	m_KeypadBtn_2.SetFunc(KeypadClick2);
	m_KeypadBtn_2._WrapText(true);

	m_KeypadBtn_3 = SYDEClickableButton("        3", Vector2(4, 11), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_3.setHighLight(RED);
	m_KeypadBtn_3.SetFunc(KeypadClick3);
	m_KeypadBtn_3._WrapText(true);

	m_KeypadBtn_4 = SYDEClickableButton("        4", Vector2(18, 7), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_4.setHighLight(RED);
	m_KeypadBtn_4.SetFunc(KeypadClick4);
	m_KeypadBtn_4._WrapText(true);

	m_KeypadBtn_5 = SYDEClickableButton("        5", Vector2(11, 7), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_5.setHighLight(RED);
	m_KeypadBtn_5.SetFunc(KeypadClick5);
	m_KeypadBtn_5._WrapText(true);

	m_KeypadBtn_6 = SYDEClickableButton("        6", Vector2(4, 7), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_6.setHighLight(RED);
	m_KeypadBtn_6.SetFunc(KeypadClick6);
	m_KeypadBtn_6._WrapText(true);

	m_KeypadBtn_7 = SYDEClickableButton("        7", Vector2(18, 3), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_7.setHighLight(RED);
	m_KeypadBtn_7.SetFunc(KeypadClick7);
	m_KeypadBtn_7._WrapText(true);

	m_KeypadBtn_8 = SYDEClickableButton("        8", Vector2(11, 3), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_8.setHighLight(RED);
	m_KeypadBtn_8.SetFunc(KeypadClick8);
	m_KeypadBtn_8._WrapText(true);

	m_KeypadBtn_9 = SYDEClickableButton("        9", Vector2(4, 3), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_9.setHighLight(RED);
	m_KeypadBtn_9.SetFunc(KeypadClick9);
	m_KeypadBtn_9._WrapText(true);

	m_KeypadBtn_0 = SYDEClickableButton("        0", Vector2(11, 15), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_0.setHighLight(RED);
	m_KeypadBtn_0.SetFunc(KeypadClick0);
	m_KeypadBtn_0._WrapText(true);

	m_KeypadBtn_DOT = SYDEClickableButton("        .", Vector2(4, 15), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_DOT.setHighLight(RED);
	m_KeypadBtn_DOT.SetFunc(KeypadClickDOT);
	m_KeypadBtn_DOT._WrapText(true);

	m_KeypadBtn_CLEAR = SYDEClickableButton("        C", Vector2(18, 15), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_CLEAR.setHighLight(RED);
	m_KeypadBtn_CLEAR.SetFunc(KeypadClickClear);
	m_KeypadBtn_CLEAR._WrapText(true);

	m_KeypadBtn_OK = SYDEClickableButton("        OK", Vector2(25, 15), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_OK.setHighLight(RED);
	m_KeypadBtn_OK.SetFunc(KeypadClickOK);
	m_KeypadBtn_OK._WrapText(true);

	m_KeypadBtn_CNCL = SYDEClickableButton("       CNCL", Vector2(25, 11), Vector2(6, 3), BLACK_BRIGHTWHITE_BG, false);
	m_KeypadBtn_CNCL.setHighLight(RED);
	m_KeypadBtn_CNCL.SetFunc(KeypadClickCNCL);
	m_KeypadBtn_CNCL._WrapText(true);

#pragma endregion

#pragma region Team In-Depth View
	m_BackTeamInDepth = SYDEClickableButton("  To Main Menu ", Vector2(0, 19), Vector2(15, 1), BLACK_WHITE_BG, false);
	m_BackTeamInDepth.setHighLight(RED);
	m_BackTeamInDepth.SetFunc(InDepthBackClick);

	m_PrevTeamInDepth = SYDEClickableButton("   Prev Team   ", Vector2(15, 19), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_PrevTeamInDepth.setHighLight(RED);
	m_PrevTeamInDepth.SetFunc(PrevRoundViewClick);

	m_NextTeamInDepth = SYDEClickableButton("   Next Team   ", Vector2(30, 19), Vector2(15, 1), BLACK_WHITE_BG, false);
	m_NextTeamInDepth.setHighLight(RED);
	m_NextTeamInDepth.SetFunc(NextRoundViewClick);

	m_TeamListInDepth = SYDEClickableButton("   Team List   ", Vector2(45, 19), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_TeamListInDepth.setHighLight(RED);
	m_TeamListInDepth.SetFunc(InDepthTeamListViewClick);

	m_BackTeamListInDepth = SYDEClickableButton("  To Team View ", Vector2(0, 19), Vector2(15, 1), BLACK_WHITE_BG, false);
	m_BackTeamListInDepth.setHighLight(RED);
	m_BackTeamListInDepth.SetFunc(InDepthTeamListBackClick);

	m_RegeneratePlayerBtn = SYDEClickableButton(" Randomize ", Vector2(47, 18), Vector2(11, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_RegeneratePlayerBtn.setHighLight(RED);
	m_RegeneratePlayerBtn.SetFunc(RandomizeButtonClick);

	m_RegeneratePlayerOKBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_RegeneratePlayerOKBtn.setHighLight(RED);
	m_RegeneratePlayerOKBtn.SetFunc(RandomizeOKClick);
	m_RegeneratePlayerCNCLBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_RegeneratePlayerCNCLBtn.setHighLight(RED);
	m_RegeneratePlayerCNCLBtn.SetFunc(RandomizeCNCLClick);

	for (int i = 0; i < 17; i++)
	{
		SYDEClickableButton button = SYDEClickableButton("View Player", Vector2(46, i + 2), Vector2(11, 1), BLACK_BRIGHTWHITE_BG, false);
		button.setHighLight(RED);
		button.setTag(to_string(i));
		button.SetFunc(PlayerClick);
		m_PlayerButtons.push_back(button);
	}

#pragma endregion
}

#pragma region Misc

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		bool canAddPlayer = true;
		SRLPlayer player = SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), SRLNameGenerator::generateRandomOriginCountry(), (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20);
		for (int ii = 0; ii < i; ii++)
		{
			if (player.getName() == m_Team[ii].getName())
			{
				canAddPlayer = false;
				i--;
				break;
			}
		}
		if (canAddPlayer)
		{
			m_Team.push_back(SRLPlayer(player));
		}
	}
	return m_Team;
}

vector<SRLPlayer> SRLGame::createOffSeasonTeam(string prefix)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 200; i++)
	{
		bool canAddPlayer = true;
		SRLPlayer player = SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), SRLNameGenerator::generateRandomOriginCountry(), (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20);
		for (int ii = 0; ii < i; ii++)
		{
			if (player.getName() == m_Team[ii].getName())
			{
				canAddPlayer = false;
				i--;
				break;
			}
		}
		if (canAddPlayer)
		{
			m_Team.push_back(SRLPlayer(player));
		}
	}
	return m_Team;
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix, float multiplier)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		bool canAddPlayer = true;
		SRLPlayer player = SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), SRLNameGenerator::generateRandomOriginCountry(), ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier, ((rand() % 80) + 20) * multiplier);
		for (int ii = 0; ii < i; ii++)
		{
			if (player.getName() == m_Team[ii].getName())
			{
				canAddPlayer = false;
				i--;
				break;
			}
		}
		if (canAddPlayer)
		{
			m_Team.push_back(SRLPlayer(player));
		}
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
	return SRLTeam(createRandomTeam(""), SRLNameGenerator::generateRandomTeamNameSafe());
}

SRLTeam SRLGame::generateOffSeasonTeam()
{
	return SRLTeam(createOffSeasonTeam(""), "Off Contract Players");
}

SRLTeam SRLGame::generateRandomTeam(float multiplier)
{
	return SRLTeam(createRandomTeam("", multiplier), SRLNameGenerator::generateRandomTeamNameSafe());
}

ConsoleWindow SRLGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (generateStartCall)
	{
		return GenerationPopUp(window, windowWidth, windowHeight);
	}
	if (SimulateCall)
	{
		return SimulatePopUp(window, windowWidth, windowHeight);
	}
	if (SeasonStartCall)
	{
		return CreateSeasonPopUp(window, windowWidth, windowHeight);
	}
	if (randomizeCall)
	{
		return RandomizePopUp(window, windowWidth, windowHeight);
	}
	if (exportCall)
	{
		return ExportPop_UP(window, windowWidth, windowHeight);
	}
	if (exitCall)
	{
		return ExitPopUp(window, windowWidth, windowHeight);
	}
	if (formatCall)
	{
		return FormatPopUp(window, windowWidth, windowHeight);
	}
	if (errorCall)
	{
		return ErrorPop_UP(window, windowWidth, windowHeight);
	}
	if (keyPadCall)
	{
		return KeypadPop_Up(window, windowWidth, windowHeight);
	}
	else if (menuCall)
	{
		return ConfirmPop_UP(window, windowWidth, windowHeight);
	}
	else if (betCall)
	{
		return BetPop_UP(window, windowWidth, windowHeight);
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
		GameStateSYDE oldState = currentState;
		currentState = newState;
		if (currentState == FMODSplashScreenState)
		{
			AssignState(std::bind(&SRLGame::fmodSplashScreen, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
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
		else if (currentState == TeamInDepthViewState)
		{
			if (!generateCall && SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				generateCall = true;
				generateStartCall = true;
				currentState = oldState;
				return window;
			}
			while (SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				generateCall = false;
				SRLTeam HomeTeam;
				int chance = rand() % customTeamGenerateChance;
				if (chance == 0)
				{
					string CustomTeamStr;
					HomeTeam = SRLCustomTeamGenerator::generateRandomCustomTeam(CustomTeamStr);
					AchievementStrings.push_back(CustomTeamStr);
				}
				else
				{
					HomeTeam = generateRandomTeam();
				}
				if (HomeTeam.getName() != "Could Not Generate Error")
				{
					HomeTeam.saveTeam();
				}
			}
			if (!SYDEFileDefaults::exists("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json"))
			{
				SRLTeam HomeTeam = generateOffSeasonTeam();
				HomeTeam.saveTeamOffContract();
			}
			setUpTeamInDepthView(0);
			AssignState(std::bind(&SRLGame::TeamInDepthView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == NewsViewState)
		{
			sortOutNews();
			AssignState(std::bind(&SRLGame::NewsView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == ResultsViewState)
		{
			m_SelectedGame = 0;
			sortOutResultsScreen();
			AssignState(std::bind(&SRLGame::ResultsView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == SeasonConfig_State)
		{
			if (!generateCall && SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				generateCall = true;
				generateStartCall = true;
				currentState = oldState;
				return window;
			}
			while (SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				generateCall = false;
				SRLTeam HomeTeam;
				int chance = rand() % customTeamGenerateChance;
				if (chance == 0)
				{
					string CustomTeamStr;
					HomeTeam = SRLCustomTeamGenerator::generateRandomCustomTeam(CustomTeamStr);
					AchievementStrings.push_back(CustomTeamStr);
				}
				else
				{
					HomeTeam = generateRandomTeam();
				}
				if (HomeTeam.getName() != "Could Not Generate Error")
				{
					HomeTeam.saveTeam();
				}
			}
			if (!SYDEFileDefaults::exists("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json"))
			{
				SRLTeam HomeTeam = generateOffSeasonTeam();
				HomeTeam.saveTeamOffContract();
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

#pragma endregion

#pragma region Windows
ConsoleWindow SRLGame::main_menu_scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_MainMenuBG.draw_asset(window, Vector2(0, 0));
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window = drawMainMenuTabs(window);
	window = m_TeamInDepthView.draw_ui(window);
	window = m_ExitGame.draw_ui(window);
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
		//THE AMOUNT OF TIMES THE SAME MATCH-UP CAN HAPPEN IN A SEASON (WHERE HOME TEAM & AWAY TEAM ARE THE SAME)
		int VersusLimit = 1;
		if (seasonLength == Length_MediumSeason || seasonLength == Length_NormalSeason)
		{
			VersusLimit = 2;
		}
		if (seasonLength == Length_LongSeason)
		{
			//ACTUAL LIMIT SHOULD BE 3 BUT FOR THE SAKE OF LOADING GIVE SOME LEEWAY
			VersusLimit = 4;
		}
		if (seasonLength == Length_ExtremeSeason)
		{
			//ACTUAL LIMIT SHOULD BE 5 BUT FOR THE SAKE OF LOADING GIVE SOME LEEWAY
			VersusLimit = 6;
		}
		if (seasonLength == Length_EnduranceSeason)
		{
			//ACTUAL LIMIT SHOULD BE 7 BUT FOR THE SAKE OF LOADING GIVE SOME LEEWAY
			VersusLimit = 8;
		}
		currentWonBetsSeason = 0;
		currentLostBetsSeason = 0;
		currentBetsTotalSeason = 0;
		currentWonBetsSeasonMatchOnly = 0;
		currentLostBetsSeasonMatchOnly = 0;
		currentBetsTotalSeasonMatchOnly = 0;

		BaseSeasonGames = static_cast<int>(seasonLength);
		SeasonStart = false;
		if (m_SeasonTeams.size() != 16)
		{
			errorCall = true;
			errorMessage = "Not Enough Teams To Start Season (16 Required)";
			return window;
		}
		//DO CONFIG IN HERE
		finals = false;
		if (fsType == KnockoutTournament || fsType == KnockoutTournamentDouble)
		{
			BaseSeasonGames = 0;
			finals = true;
		}
		vector<SRLLadderPosition> ladders;
		for (int i = 0; i < m_SeasonTeams.size(); i++)
		{
			SRLLadderPosition newPosition;
			newPosition.teamName = m_SeasonTeams[i];
			ladders.push_back(newPosition);
		}
#pragma region Add Rounds
		SRLLadder Ladder = SRLLadder(ladders);
		vector<SRLRound> rounds = vector<SRLRound>();
		if (fsType == KnockoutTournament || fsType == KnockoutTournamentDouble)
		{
			vector<SRLGameMatchup> games;
			vector<string> AvailableTeams = m_SeasonTeams;
			games.push_back(SRLGameMatchup(AvailableTeams[0], AvailableTeams[15]));
			games.push_back(SRLGameMatchup(AvailableTeams[1], AvailableTeams[14]));
			games.push_back(SRLGameMatchup(AvailableTeams[2], AvailableTeams[13]));
			games.push_back(SRLGameMatchup(AvailableTeams[3], AvailableTeams[12]));
			games.push_back(SRLGameMatchup(AvailableTeams[4], AvailableTeams[11]));
			games.push_back(SRLGameMatchup(AvailableTeams[5], AvailableTeams[10]));
			games.push_back(SRLGameMatchup(AvailableTeams[6], AvailableTeams[9]));
			games.push_back(SRLGameMatchup(AvailableTeams[7], AvailableTeams[8]));
			rounds.push_back(SRLRound(games));
		}
		for (int i = 0; i < BaseSeasonGames; i++)
		{
			bool pushBack = true;
			vector<SRLGameMatchup> games;
			vector<string> AvailableTeams = m_SeasonTeams;
			vector<string> AttemptedTeams = vector<string>();
			for (int ii = 0; ii < 8; ii++)
			{
				if (!addGame(VersusLimit, rounds, games, AvailableTeams, AttemptedTeams))
				{
					if (AvailableTeams.size() > 2)
					{
						ii--;
					}
					else
					{
						i--;
						pushBack = false;
						games.clear();
						break;
					}
				}
				else
				{
					for (int j = 0;j < AttemptedTeams.size(); j++)
					{
						AvailableTeams.push_back(AttemptedTeams[j]);
					}
					AttemptedTeams.clear();
				}
			}
			if (pushBack)
			{
				rounds.push_back(SRLRound(games));
			}
		}
#pragma endregion
		//FEATURE A GAME
		int _HighlightedFirstGame = rand() % 8;
		rounds[0].gameToFeature = FeaturedGame(rounds[0].m_Games[_HighlightedFirstGame].HomeTeam, rounds[0].m_Games[_HighlightedFirstGame].AwayTeam, astVars, _HighlightedFirstGame, SRLBetPrice(0,0), SRLBetPrice(0, 0));
		SRLDraw Draw(rounds);
		m_Season = SRLSeason(Draw, Ladder);
		m_Season.m_PremiershipBets.clear();
		m_GameBetsWriteUp.clear();
		m_PremiershipBetsWriteUp.clear();
		m_BetMoney = SRLBetPrice(500, 0);
		newState = SeasonModeState;
		m_round = 0;
		m_roundToSimulate = 0;
		drawViewState = SeasonDrawMainView;
		CalculateOdds();
		m_Season.m_Draw.m_Rounds[0].gameToFeature.fg_homeOdds = m_Season.m_Draw.m_Rounds[0].m_Games[_HighlightedFirstGame].homeTeamOdds;
		m_Season.m_Draw.m_Rounds[0].gameToFeature.fg_awayOdds = m_Season.m_Draw.m_Rounds[0].m_Games[_HighlightedFirstGame].awayTeamOdds;
		CalculatePremiershipOdds();
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
			SRLTeam HomeTeam;
			int chance = rand() % customTeamGenerateChance;
			if (chance == 0)
			{
				string CustomTeamStr;
				HomeTeam = SRLCustomTeamGenerator::generateRandomCustomTeam(CustomTeamStr);
				AchievementStrings.push_back(CustomTeamStr);
			}
			else
			{
				HomeTeam = generateRandomTeam();
			}
			if (HomeTeam.getName() != "Could Not Generate Error")
			{
				HomeTeam.saveTeam();
				m_SeasonTeams.push_back(HomeTeam.getName());
			}
			else
			{
				errorCall = true;
				errorMessage = "Error creating new team: Try Again";
			}
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

ConsoleWindow SRLGame::fmodSplashScreen(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_FmodSplash.draw_asset(window, Vector2(0, 0));
	if (splashScreenInit)
	{
		splashScreenInit = false;
		return window;
	}
	splashScreenTime += SYDEDefaults::getDeltaTime();
	if (splashScreenTime >= 3.5f)
	{
		newState = MainMenu_STATE;
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
	if (drawViewState == GameSettingsInSeasonView)
	{
		//SANITY
		NextRoundCall = false;
		PrevRoundCall = false;
		SimulateCall = false;


		window = m_SoundTrackOnBtn.draw_ui(window);
		if (soundTrackOn)
		{
			window.setTextAtPoint(Vector2(22, 4), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 4), "Off", BRIGHTWHITE);
		}
		window = m_SoundTrackNextBtn.draw_ui(window);
		window.setTextAtPoint(Vector2(22, 6), m_GamePlaySoundtrack.getSongPlaying(), BRIGHTWHITE);
		window = m_SoundTrackVolume.draw_ui(window);
		switch (BaseSYDESoundSettings::getDefaultVolumeState())
		{
		case SYDE_VOLUME_OFF:
			window.setTextAtPoint(Vector2(22, 8), "Off", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_LOW:
			window.setTextAtPoint(Vector2(22, 8), "Low", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_HIG:
			window.setTextAtPoint(Vector2(22, 8), "High", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_NML:
			window.setTextAtPoint(Vector2(22, 8), "Normal", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_MED:
			window.setTextAtPoint(Vector2(22, 8), "Medium", BRIGHTWHITE);
			break;
		}
		window = drawSeasonModeTabs(window);
		return window;
	}
	else if (drawViewState == TippingMasterView)
	{
		//SANITY
		NextRoundCall = false;
		PrevRoundCall = false;
		SimulateCall = false;

		window = drawSeasonModeTabs(window);

		window = m_TipMasterImg.draw_asset(window, Vector2(38, 3));
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
		{
			for (int i = 0; i < TipMasterBets.size(); i++)
			{
				window.setTextAtPoint(Vector2(0, 3 + i), TipMasterBets[i], WHITE);
			}
		}
		else
		{
			window.setTextAtPoint(Vector2(0, 3), "THE SEASON IS OVER", WHITE);
			window.setTextAtPoint(Vector2(0, 4), "I MUST SLEEP UNTIL THE NEXT", WHITE);
		}
		return window;
	}
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
	if (drawViewState == SeasonDrawMainView)
	{
		window.setTextAtPoint(Vector2(0, 2), "SRL ROUND " + std::to_string(m_round + 1), WHITE);
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_round].m_Games.size(); i++)
		{
			window.setTextAtPoint(Vector2(0, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].HomeTeam, WHITE);
			window.setTextAtPoint(Vector2(26, 3 + i), std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].homeTeamScore) + " v " + std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].awayTeamScore), WHITE);
			window.setTextAtPoint(Vector2(34, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].AwayTeam, WHITE);
		}
		SimulateGames();
	}
	else if (drawViewState == FeaturedMatchView)
	{
		//SANITY
		SimulateCall = false;
		window.setTextAtPoint(Vector2(0, 2), "SRL ROUND " + std::to_string(m_round + 1), WHITE);
		string awayTeamText = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_awayTeam.getName();
		if (m_Season.m_Draw.m_Rounds[m_round].gameToFeature.featuredGameAvail)
		{
			int sizeText = awayTeamText.length();

			window = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_homeTeamJersey.draw_asset(window, Vector2(0, 3));
			window = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_awayTeamJersey.draw_asset(window, Vector2(30, 3));
			window.setTextAtPoint(Vector2(0, 3), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_homeTeam.getName(), WHITE);
			window.setTextAtPoint(Vector2(60 - sizeText, 3), awayTeamText, WHITE);

			window.setTextAtPoint(Vector2(12, 17), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_homeOdds.ReturnPrice(), WHITE);
			window.setTextAtPoint(Vector2(42, 17), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_awayOdds.ReturnPrice(), WHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(0, 3), "NO FEATURED GAME FOR THIS ROUND AT THE MOMENT", WHITE);
		}
		window = m_FeatureSwitchViewBtn.draw_ui(window);
	}
	else if (drawViewState == FeaturedMatchTeamListView)
	{
		//SANITY
		SimulateCall = false;
		window.setTextAtPoint(Vector2(0, 2), "SRL ROUND " + std::to_string(m_round + 1), WHITE);
		string awayTeamText = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_awayTeam.getName();
		if (m_Season.m_Draw.m_Rounds[m_round].gameToFeature.featuredGameAvail)
		{
			int sizeText = awayTeamText.length();
			window.setTextAtPoint(Vector2(0, 3), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.fg_homeTeam.getName(), WHITE);
			window.setTextAtPoint(Vector2(60 - sizeText, 3), awayTeamText, WHITE);
			window.setTextAtPoint(Vector2(24, 4), "KEY PLAYERS:", WHITE);
			for (int i = 0; i < 5; i++)
			{
				int sizeText = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.awayTeamKeyPlayers[i].length();
				window.setTextAtPoint(Vector2(0, 5 + i), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.homeTeamKeyPlayers[i], BRIGHTGREEN);
				window.setTextAtPoint(Vector2(60 - sizeText, 5 + i), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.awayTeamKeyPlayers[i], BRIGHTGREEN);
			}
			window.setTextAtPoint(Vector2(23, 10), "MATCH HISTORY:", WHITE);
			for (int i = 0; i < 5 && i < m_Season.m_Draw.m_Rounds[m_round].gameToFeature.MatchHistory.size(); i++)
			{
				int sizeText = m_Season.m_Draw.m_Rounds[m_round].gameToFeature.MatchHistory[i].length();
				int spacing = (60 - sizeText) / 2;
				window.setTextAtPoint(Vector2(spacing, 11 + i), m_Season.m_Draw.m_Rounds[m_round].gameToFeature.MatchHistory[i], BRIGHTGREEN);
			}
		}
		else
		{
			window.setTextAtPoint(Vector2(0, 3), "NO FEATURED GAME FOR THIS ROUND AT THE MOMENT", WHITE);
		}
		window = m_FeatureSwitchViewBtn.draw_ui(window);
	}
	window = drawSeasonModeTabs(window);
	return window;
}

ConsoleWindow SRLGame::LadderView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window.setTextAtPoint(Vector2(0, 2), "SRL LADDER   ", WHITE);
	for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
	{
		if (i + 1 <= finalsThreshold)
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
		if (betPlaceCall)
		{
			betPlaceCall = false;
			if (m_BetMoney.greaterThan(m_BetAmount) || m_BetMoney.equal(m_BetAmount))
			{
				if (m_BetAmount.equal(SRLBetPrice(420, 69)))
				{
					AchievementStrings.push_back("SRL_BET_NICE");
				}
				m_BetMoney.removeBetPrice(m_BetAmount);
				if (homeTeamBet)
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets.push_back(SRLGameBet(betTag, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameNumberBet].homeTeamOdds, m_BetAmount));
				}
				else
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets.push_back(SRLGameBet(betTag, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameNumberBet].awayTeamOdds, m_BetAmount));
				}
				UpdateBets();
			}
			else
			{
				errorCall = true;
				errorMessage = "Not Enough Money To Bet";
				return window;
			}
		}
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
		{
			int line = 3;
			for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
			{
				window.setTextAtPoint(Vector2(0, line ), "(H) " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + " - " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamOdds.ReturnPrice(), window._intToColour(i + 2));
				window.setTextAtPoint(Vector2(0, line + 1),"(A) " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + " - " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamOdds.ReturnPrice(), window._intToColour(i + 2));
				line += 2;
			}
			for (int i = 0; i < m_BetButtons.size(); i++)
			{
				window = m_BetButtons[i].draw_ui(window);
			}
		}
		else
		{
			window.setTextAtPoint(Vector2(2, 3), "PREMIERSHIP COMPLETED, NO MORE BETS", BRIGHTWHITE);
		}
	}
	else if(bettingState == Futures_STATE)
	{
		if (betPlaceCall)
		{
			betPlaceCall = false;
			if (m_BetMoney.greaterThan(m_BetAmount) || m_BetMoney.equal(m_BetAmount))
			{
				if (m_BetAmount.equal(SRLBetPrice(420, 69)))
				{
					AchievementStrings.push_back("SRL_BET_NICE");
				}
				m_BetMoney.removeBetPrice(m_BetAmount);
				m_Season.m_PremiershipBets.push_back(SRLGameBet(betTag, m_Season.m_Ladder.m_Ladder[gameNumberBet].premiershipOdds, m_BetAmount, true));
				UpdateBets();
			}
			else
			{
				errorCall = true;
				errorMessage = "Not Enough Money To Bet";
				return window;
			}
		}
		if (m_roundToSimulate >= BaseSeasonGames)
		{
			window.setTextAtPoint(Vector2(2, 3), "PREMIERSHIP BETS SUSPENDED", BRIGHTWHITE);
		}
		else
		{
			for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
			{
				if (i + 1 <= 8)
				{
					window.setTextAtPoint(Vector2(2, 3 + i), to_string(i + 1) + " " + m_Season.m_Ladder.m_Ladder[i].teamName + "(" + m_Season.m_Ladder.m_Ladder[i].premiershipOdds.ReturnPrice() + ")", BRIGHTGREEN);
				}
				else
				{
					window.setTextAtPoint(Vector2(2, 3 + i), to_string(i + 1) + " " + m_Season.m_Ladder.m_Ladder[i].teamName + "(" + m_Season.m_Ladder.m_Ladder[i].premiershipOdds.ReturnPrice() + ")", RED);
				}
			}
			for (int i = 0; i < m_PremiershipBetButtons.size(); i++)
			{
				window = m_PremiershipBetButtons[i].draw_ui(window);
			}
		}
	}
	else if (bettingState == ViewBets_STATE)
	{
		window = m_PriorBetsGameBtn.draw_ui(window);
		window = m_PriorBetsPremiershipBtn.draw_ui(window);
		if (priorBetsState == IndividualGameBets_State)
		{
			if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEYDOWN))
			{
				if (priorBetNumberLine > 0)
				{
					priorBetNumberLine--;
				}
			}
			if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEYDOWN))
			{
				if (priorBetNumberLine < m_GameBetsWriteUp.size() - 1)
				{
					priorBetNumberLine++;
				}
			}
			else if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
			{
				ScrollTickTime += SYDEDefaults::getDeltaTime();
				if (ScrollTickTime >= maxScrollTickTime)
				{
					if (priorBetNumberLine > 0)
					{
						priorBetNumberLine--;
					}
					ScrollTickTime = 0;
				}
			}
			else if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEY))
			{
				ScrollTickTime += SYDEDefaults::getDeltaTime();
				if (ScrollTickTime >= maxScrollTickTime)
				{
					if (priorBetNumberLine < m_GameBetsWriteUp.size() - 1)
					{
						priorBetNumberLine++;
					}
					ScrollTickTime = 0;
				}
			}
			else
			{
				ScrollTickTime = 0;
			}

			for (int i = 0; i + priorBetNumberLine < m_GameBetsWriteUp.size() && i < 14; i++)
			{
				window.setTextAtPoint(Vector2(1, 4 + i), m_GameBetsWriteUp[i + priorBetNumberLine].name, m_GameBetsWriteUp[i + priorBetNumberLine].colour);
			}
		}
		else if (priorBetsState == PremiershipWinnerBets_State)
		{
			if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEYDOWN))
			{
				if (priorBetNumberLine > 0)
				{
					priorBetNumberLine--;
				}
			}
			if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEYDOWN))
			{
				if (priorBetNumberLine < m_PremiershipBetsWriteUp.size() - 1)
				{
					priorBetNumberLine++;
				}
			}
			else if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
			{
				ScrollTickTime += SYDEDefaults::getDeltaTime();
				if (ScrollTickTime >= maxScrollTickTime)
				{
					if (priorBetNumberLine > 0)
					{
						priorBetNumberLine--;
					}
					ScrollTickTime = 0;
				}
			}
			else if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEY))
			{
				ScrollTickTime += SYDEDefaults::getDeltaTime();
				if (ScrollTickTime >= maxScrollTickTime)
				{
					if (priorBetNumberLine < m_PremiershipBetsWriteUp.size() - 1)
					{
						priorBetNumberLine++;
					}
					ScrollTickTime = 0;
				}
			}
			else
			{
				ScrollTickTime = 0;
			}

			for (int i = 0; i + priorBetNumberLine < m_PremiershipBetsWriteUp.size() && i < 14; i++)
			{
				window.setTextAtPoint(Vector2(1, 4 + i), m_PremiershipBetsWriteUp[i + priorBetNumberLine].name, m_PremiershipBetsWriteUp[i + priorBetNumberLine].colour);
			}
		}
	}
	else if (bettingState == Account_STATE)
	{
		window.setTextAtPoint(Vector2(2, 3), "Account Balance: " + m_BetMoney.ReturnPrice(), BRIGHTWHITE);

		window.setTextAtPoint(Vector2(2, 5), "Bets Won: " + to_string(currentWonBetsSeason), BRIGHTGREEN);
		window.setTextAtPoint(Vector2(2, 6), "Bets Lost: " + to_string(currentLostBetsSeason), RED);
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
	else if (ldrState == SinBin_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopSinBin.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST SIN BINS   ", WHITE);
	}
	else if (ldrState == SendOff_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopSendOff.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST SEND OFFS   ", WHITE);
	}
	else if (ldrState == Injury_State)
	{
		window = LeaderboardPositions(window, m_Season.m_TopInjuries.shortlist);
		window.setTextAtPoint(Vector2(0, 5), "MOST INJURIES   ", WHITE);
	}
	return window;
}

ConsoleWindow SRLGame::ResultsView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	window = drawResultTabs(window);
	if (m_ResultsTabCall)
	{
		m_ResultsTabCall = false;
		m_LineResults = 0;
	}
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
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, 3), " ", BLACK_BRIGHTWHITE_BG);
		}
		window.setTextAtPoint(Vector2(0, 3), m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].HomeTeam, BLACK_BRIGHTWHITE_BG);
		window.setTextAtPoint(Vector2(26, 3), std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].homeTeamScore) + " v " + std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].awayTeamScore), BLACK_BRIGHTWHITE_BG);
		window.setTextAtPoint(Vector2(34, 3), m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].AwayTeam, BLACK_BRIGHTWHITE_BG);
		if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEYDOWN))
		{
			if (m_LineResults > 0)
			{
				m_LineResults--;
			}
		}
		if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEYDOWN))
		{
			if (m_LineResults < m_SummaryScreenVector.size() - 1)
			{
				m_LineResults++;
			}
		}
		else if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
		{
			ScrollTickTime += SYDEDefaults::getDeltaTime();
			if (ScrollTickTime >= maxScrollTickTime)
			{
				if (m_LineResults > 0)
				{
					m_LineResults--;
				}
				ScrollTickTime = 0;
			}
		}
		else if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEY))
		{
			ScrollTickTime += SYDEDefaults::getDeltaTime();
			if (ScrollTickTime >= maxScrollTickTime)
			{
				if (m_LineResults < m_SummaryScreenVector.size() - 1)
				{
					m_LineResults++;
				}
				ScrollTickTime = 0;
			}
		}
		else
		{
			ScrollTickTime = 0;
		}

		for (int i = 0; i + m_LineResults < m_SummaryScreenVector.size() && i < 14; i++)
		{
			window.setTextAtPoint(Vector2(1, 4 + i), m_SummaryScreenVector[i + m_LineResults], WHITE);
		}
	}
	if (resultState == PlayByPlay_STATE)
	{
		if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEYDOWN))
		{
			if (m_LineResults > 0)
			{
				m_LineResults--;
			}
		}
		if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEYDOWN))
		{
			if (m_LineResults < m_ResultsScreenVector.size() - 1)
			{
				m_LineResults++;
			}
		}
		else if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
		{
			ScrollTickTime += SYDEDefaults::getDeltaTime();
			if (ScrollTickTime >= maxScrollTickTime)
			{
				if (m_LineResults > 0)
				{
					m_LineResults--;
				}
				ScrollTickTime = 0;
			}
		}
		else if (SYDEKeyCode::get_key(VK_UP)._CompareState(KEY))
		{
			ScrollTickTime += SYDEDefaults::getDeltaTime();
			if (ScrollTickTime >= maxScrollTickTime)
			{
				if (m_LineResults > 0)
				{
					m_LineResults--;
				}
				ScrollTickTime = 0;
			}
		}

		else if (SYDEKeyCode::get_key(VK_DOWN)._CompareState(KEY))
		{
			ScrollTickTime += SYDEDefaults::getDeltaTime();
			if (ScrollTickTime >= maxScrollTickTime)
			{
				if (m_LineResults < m_ResultsScreenVector.size() - 1)
				{
					m_LineResults++;
				}
				ScrollTickTime = 0;
			}
		}
		else
		{
			ScrollTickTime = 0;
		}

		for (int i = 0; i + m_LineResults < m_ResultsScreenVector.size() && i < 15; i++)
		{
			window.setTextAtPoint(Vector2(1, 3 + i), m_ResultsScreenVector[i + m_LineResults], WHITE);
		}

		window = m_ExportBtn.draw_ui(window);
	}
	return window;
}

ConsoleWindow SRLGame::TeamInDepthView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (playerCall)
	{
		playerCall = false;
		setUpPlayer();
		inDepthState = PlayerViewState;
	}
	if (inDepthState == TeamListViewState)
	{
		return TeamInDepthListView(window, windowWidth, windowHeight);
	}
	else if (inDepthState == PlayerViewState)
	{
		return PlayerInDepthView(window, windowWidth, windowHeight);
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
		m_TeamViewing--;
		if (m_TeamViewing < 0)
		{
			m_TeamViewing = SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") - 1;
		}
		setUpTeamInDepthView(m_TeamViewing);
	}
	if (NextRoundCall)
	{
		NextRoundCall = false;
		m_TeamViewing++;
		if (m_TeamViewing >= SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json"))
		{
			m_TeamViewing = 0;
		}
		setUpTeamInDepthView(m_TeamViewing);
	}
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(2, 1), m_InDepthTeamView.getName(), BLACK_BRIGHTWHITE_BG);
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(2, 3), "Attack: " + to_string(m_InDepthTeamView.averageAttackStat()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 4), "Defence: " + to_string(m_InDepthTeamView.averageDefenceStat()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 5), "Speed: " + to_string(m_InDepthTeamView.averageSpeedStat()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 6), "Kicking: " + to_string(m_InDepthTeamView.averageKickStat()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 7), "Handling: " + to_string(m_InDepthTeamView.averageHandlingStat()), BRIGHTWHITE);

	window.setTextAtPoint(Vector2(2, 9), "Team Rating: " + to_string(m_InDepthTeamView.TeamRating()), BRIGHTWHITE);

	window.setTextAtPoint(Vector2(2, 11), "Goal Kicker: " + m_InDepthTeamView.getGoalKickerNoLimit().getName(), BRIGHTWHITE);

	window = m_JerseyView.draw_asset(window, Vector2(30,3));
	window = m_BackTeamInDepth.draw_ui(window);
	window = m_PrevTeamInDepth.draw_ui(window);
	window = m_NextTeamInDepth.draw_ui(window);
	window = m_TeamListInDepth.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::TeamInDepthListView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(2, 1), m_InDepthTeamView.getName(), BLACK_BRIGHTWHITE_BG);
	for (int i = 0; i < m_InDepthTeamView.getPlayers().size(); i++)
	{
		window.setTextAtPoint(Vector2(1, i+ 2), to_string(i+1) + ". " + m_InDepthTeamView.getPlayers()[i].getName(), BRIGHTWHITE);
		window = m_PlayerButtons[i].draw_ui(window);
	}
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window = m_BackTeamListInDepth.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::PlayerInDepthView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(2, 1), m_PlayerView.getName(), BLACK_BRIGHTWHITE_BG);
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window = m_PlayerAsset.draw_asset(window, Vector2(30, 3));
	window = m_TeamListInDepth.draw_ui(window, Vector2(0,19));

	window.setTextAtPoint(Vector2(2, 3), "Attack: " + to_string(m_PlayerView.getAttack()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 4), "Defence: " + to_string(m_PlayerView.getDefence()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 5), "Speed: " + to_string(m_PlayerView.getSpeed()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 6), "Kicking: " + to_string(m_PlayerView.getKicking()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 7), "Handling: " + to_string(m_PlayerView.getHandling()), BRIGHTWHITE);

	window.setTextAtPoint(Vector2(2, 9), "Player Rating: " + to_string(m_PlayerView.getRating()), BRIGHTWHITE);

	window.setTextAtPoint(Vector2(2, 18), "Country Of Origin: " + m_PlayerView.getOrigin(), BRIGHTWHITE);
	window = m_RegeneratePlayerBtn.draw_ui(window);
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

void SRLGame::LeaderboardOutputStrings(vector<string>& mainVec, vector<SRLLeaderboardPosition> ldrboard)
{
	for (int i = 0; i < 10; i++)
	{
		mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
	}
}

void SRLGame::LeaderboardOutputStringsTopScorer(vector<string>& mainVec, vector<SRLLeaderboardPosition> ldrboard)
{
	for (int i = 0; i < 25; i++)
	{
		mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
	}
}

void SRLGame::LeaderboardOutputStringsTopPlayer(vector<string>& mainVec, vector<SRLLeaderboardPosition> ldrboard)
{
	for (int i = 0; i < 25; i++)
	{
		mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
	}
}

ConsoleWindow SRLGame::SettingsView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawMainMenuTabs(window);
	window = m_GameSettingsSeasonBtn.draw_ui(window);
	window = m_GameSettingsNormalBtn.draw_ui(window);
	if (settingsState == SeasonSettings_STATE)
	{
		window = m_SettingsGoalKickerBtn.draw_ui(window);
		if (m_GoalKicker)
		{
			window.setTextAtPoint(Vector2(22, 4), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 4), "Off", BRIGHTWHITE);
		}
		window = m_SettingsWeatherBtn.draw_ui(window);
		if (m_Weather)
		{
			window.setTextAtPoint(Vector2(22, 6), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 6), "Off", BRIGHTWHITE);
		}
		window = m_SettingsStaminaBtn.draw_ui(window);
		if (m_Stamina)
		{
			window.setTextAtPoint(Vector2(22, 8), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 8), "Off", BRIGHTWHITE);
		}
		window = m_SettingsSeasonLengthBtn.draw_ui(window);
		switch (seasonLength)
		{
		case Length_ShortSeason:
			window.setTextAtPoint(Vector2(22, 10), "Short", BRIGHTWHITE);
			break;
		case Length_RoundRobin:
			window.setTextAtPoint(Vector2(22, 10), "Round Robin", BRIGHTWHITE);
			break;
		case Length_MediumSeason:
			window.setTextAtPoint(Vector2(22, 10), "Medium", BRIGHTWHITE);
			break;
		case Length_NormalSeason:
			window.setTextAtPoint(Vector2(22, 10), "Normal", BRIGHTWHITE);
			break;
		case Length_LongSeason:
			window.setTextAtPoint(Vector2(22, 10), "Long", BRIGHTWHITE);
			break;
		case Length_ExtremeSeason:
			window.setTextAtPoint(Vector2(22, 10), "Extreme", BRIGHTWHITE);
			break;
		case Length_EnduranceSeason:
			window.setTextAtPoint(Vector2(22, 10), "Endurance", BRIGHTWHITE);
			break;
		}
		window = m_SettingsExtraTimeBtn.draw_ui(window);
		if (m_ExtraTime)
		{
			window.setTextAtPoint(Vector2(22, 12), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 12), "Off", BRIGHTWHITE);
		}
		window = m_SettingsInjuryBtn.draw_ui(window);
		if (m_Injuries)
		{
			window.setTextAtPoint(Vector2(22, 14), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 14), "Off", BRIGHTWHITE);
		}
		window = m_SettingsSinBinBtn.draw_ui(window);
		if (m_SinBins)
		{
			window.setTextAtPoint(Vector2(22, 16), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 16), "Off", BRIGHTWHITE);
		}
		window = m_SettingsEventsBtn.draw_ui(window);
		if (m_SeasonEvents)
		{
			window.setTextAtPoint(Vector2(52, 4), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(52, 4), "Off", BRIGHTWHITE);
		}
		window = m_SettingsFinalsBtn.draw_ui(window);
		if (finalsSystemCall)
		{
			finalsSystemCall = false;
			finalsSystemInt++;
			if (finalsSystemInt >= m_FSTYPES.size())
			{
				finalsSystemInt = 0;
			}
			finalsSettingStr = m_FSTYPES[finalsSystemInt].FinalsStr;
			fsType = m_FSTYPES[finalsSystemInt].fsType;
			finalsThreshold = m_FSTYPES[finalsSystemInt].noTeams;
			finalsRounds = m_FSTYPES[finalsSystemInt].rounds;
		}
		window.setTextAtPoint(Vector2(22, 18), finalsSettingStr, BRIGHTWHITE);
	}
	else if (settingsState == NormalSettings_STATE)
	{
		window = m_SoundTrackOnBtn.draw_ui(window);
		if (soundTrackOn)
		{
			window.setTextAtPoint(Vector2(22, 4), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(22, 4), "Off", BRIGHTWHITE);
		}
		window = m_SoundTrackNextBtn.draw_ui(window);
		window.setTextAtPoint(Vector2(22, 6), m_GamePlaySoundtrack.getSongPlaying(), BRIGHTWHITE);
		window = m_SoundTrackVolume.draw_ui(window);
		switch (BaseSYDESoundSettings::getDefaultVolumeState())
		{
		case SYDE_VOLUME_OFF:
			window.setTextAtPoint(Vector2(22, 8), "Off", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_LOW:
			window.setTextAtPoint(Vector2(22, 8), "Low", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_HIG:
			window.setTextAtPoint(Vector2(22, 8), "High", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_NML:
			window.setTextAtPoint(Vector2(22, 8), "Normal", BRIGHTWHITE);
			break;
		case SYDE_VOLUME_MED:
			window.setTextAtPoint(Vector2(22, 8), "Medium", BRIGHTWHITE);
			break;
		}
		window = m_FormatTeamsBtn.draw_ui(window);
	}
	return window;
}

ConsoleWindow SRLGame::NewsView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawTabs(window);
	if (m_Season.m_Draw.m_Rounds[m_round].newsStories.size() == 0)
	{
		window.setTextAtPoint(Vector2(0, 2), "NO NEWS FOR THIS ROUND AT THE MOMENT", BRIGHTWHITE);
	}
	if (headlineCall)
	{
		m_Article = m_Season.m_Draw.m_Rounds[m_round].newsStories[articleClicked];
		if (m_Article.type == SRLAT_Normal)
		{
			AchievementStrings.push_back("SRL_NEWSPAPER");
		}
		else if (m_Article.type == SRLAT_DropPlayer)
		{
			AchievementStrings.push_back("SRL_CONTROVERSY");
		}
		articleState = ArticleFullViewState;
		headlineCall = false;
	}
	if (articleState == HeadlinesState)
	{
		for (int i = 0; i < m_NewsHeadlines.size(); i++)
		{
			window = m_NewsHeadlines[i].draw_ui(window);
		}
	}
	else if (articleState == ArticleFullViewState)
	{
		for (int i = 0; i < m_Article.newsStory.size(); i++)
		{
			window.setTextAtPoint(Vector2(0, i+2), m_Article.newsStory[i], BRIGHTWHITE);
		}
		window = m_BackHeadline.draw_ui(window);
		window = m_Article.newsPicture.draw_asset(window, Vector2(46, 12));
	}
	return window;
}

ConsoleWindow SRLGame::InfoView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = drawMainMenuTabs(window);
	window.setTextAtPoint(Vector2(0, 2), "GAME INFORMATION", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 3), "Created by Callum Hands", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 4), "In Association With Freebee Network", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(0, 5), "Version: 0.11.1.0-beta", BRIGHTWHITE);
	return window;
}

ConsoleWindow SRLGame::SimulatePopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	SimulateCall = false;
	Simulate = true;
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6),"SIMULATING....PLEASE WAIT...." , BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 7), "Please note simulation will take longer", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 8), "the more rounds simulated at once", BLACK_BRIGHTYELLOW_BG);
	return window;
}

ConsoleWindow SRLGame::CreateSeasonPopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	SeasonStartCall = false;
	SeasonStart = true;
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Generating Season Draw", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 7), "Please note generation can take a while", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 8), "due to face off limits and randomness", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 9), "more specific seasons (e.g. round robin)", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 10), "will take longer to generate the draw", BLACK_BRIGHTYELLOW_BG);
	return window;
}

ConsoleWindow SRLGame::GenerationPopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	generateStartCall = false;
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Generating Teams", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 7), "Please note generation can take a while", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 8), "especially if already a large number of", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(6, 9), "teams, or first time playing", BLACK_BRIGHTYELLOW_BG);
	return window;
}

ConsoleWindow SRLGame::FormatPopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (formatConfirmedCall)
	{
		formatCall = false;
		formatConfirmedCall = false;
		AchievementStrings.push_back("SRL_FORMAT_TEAMS");
		try
		{
			SYDEFileDefaults::deleteAllFilesInFolder("EngineFiles\\GameResults\\Teams");
			SYDEFileDefaults::deleteAllFilesInFolder("EngineFiles\\GameResults\\OffContract");
			SYDEFileDefaults::deleteAllFilesInFolder("EngineFiles\\GameResults\\Players");
		}
		catch (exception e)
		{
			errorCall = true;
			errorMessage = "Error Occured When Formatting";
		}
	}
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Are you sure you want to delete team data?", BRIGHTWHITE_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(6, 7), "This cannot be undone!", BRIGHTWHITE_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(6, 8), "New teams will be generated when opening", BRIGHTWHITE_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(6, 9), "In depth view mode or new season", BRIGHTWHITE_BRIGHTGREEN_BG);
	window = m_FormatTeamsOKBtn.draw_ui(window);
	window = m_FormatTeamsCNCLBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::ExitPopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Are you sure you want to exit?", BRIGHTWHITE_BRIGHTGREEN_BG);
	window = m_ExitGameOK.draw_ui(window);
	window = m_ExitGameCNL.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::RandomizePopUp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (randomizeConfirmedCall)
	{
		randomizeCall = false;
		randomizeConfirmedCall = false;
		AchievementStrings.push_back("SRL_REGEN");
		int id = m_PlayerView.getID();
		m_PlayerView = SRLPlayer(SRLNameGenerator::generateRandomName(), SRLNameGenerator::generateRandomOriginCountry(), (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20);
		m_PlayerView.setID(id);
		m_PlayerView.savePlayer();

		setUpTeamInDepthView(m_TeamViewing);
		setUpPlayer();
	}
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Are you sure you want to randomize?", BRIGHTWHITE_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(6, 7), "This cannot be undone", BRIGHTWHITE_BRIGHTGREEN_BG);
	window = m_RegeneratePlayerOKBtn.draw_ui(window);
	window = m_RegeneratePlayerCNCLBtn.draw_ui(window);
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
	window = m_NewsViewBtn.draw_ui(window);
	window = m_PreviousRoundViewBtn.draw_ui(window);
	window = m_NextRoundViewBtn.draw_ui(window);
	window = m_SimulateBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::drawBetTabs(ConsoleWindow window)
{
	window = m_BetBtnCurrentRound.draw_ui(window);
	window = m_BetBtnFutures.draw_ui(window);
	window = m_BetBtnViewBets.draw_ui(window);
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

	window = m_LeaderboardBtnMostSinBin.draw_ui(window);
	window = m_LeaderboardBtnMostSendOff.draw_ui(window);
	window = m_LeaderboardBtnMostInjuries.draw_ui(window);

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

ConsoleWindow SRLGame::drawSeasonModeTabs(ConsoleWindow window)
{
	window = m_FeatureViewBtn.draw_ui(window);
	window = m_MainDrawViewBtn.draw_ui(window);
	window = m_ExportBtn.draw_ui(window);
	window = m_MainSettingsViewBtn.draw_ui(window);
	window = m_TipMasterViewBtn.draw_ui(window);
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

ConsoleWindow SRLGame::KeypadPop_Up(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 2; ii < windowHeight - 1; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(25, 3), "Bet Amount: $" + customAmountStr, BRIGHTWHITE);
	window = m_KeypadBtn_1.draw_ui(window);
	window = m_KeypadBtn_2.draw_ui(window);
	window = m_KeypadBtn_3.draw_ui(window);
	window = m_KeypadBtn_4.draw_ui(window);
	window = m_KeypadBtn_5.draw_ui(window);
	window = m_KeypadBtn_6.draw_ui(window);
	window = m_KeypadBtn_7.draw_ui(window);
	window = m_KeypadBtn_8.draw_ui(window);
	window = m_KeypadBtn_9.draw_ui(window);
	window = m_KeypadBtn_0.draw_ui(window);
	window = m_KeypadBtn_DOT.draw_ui(window);
	window = m_KeypadBtn_CLEAR.draw_ui(window);
	window = m_KeypadBtn_OK.draw_ui(window);
	window = m_KeypadBtn_CNCL.draw_ui(window);
	return window;
}

bool SRLGame::addGame(int limit, vector<SRLRound> rounds, vector<SRLGameMatchup>& games, vector<string>& teams, vector<string>& AttemptedTeams)
{
	if (teams.size() < 2)
	{
		return false;
	}
	int team1 = rand() % teams.size();
	string team1Name = teams[team1];
	teams.erase(teams.begin() + team1);
	int team2 = rand() % teams.size();
	string team2Name = teams[team2];
	teams.erase(teams.begin() + team2);
	if (m_FaceOffLimit)
	{
		int count = 0;
		int exactLineUp = 0;
		for (int j = 0; j < rounds.size(); j++)
		{
			for (int jj = 0; jj < 8; jj++)
			{
				bool VersedBefore1 = (rounds[j].m_Games[jj].HomeTeam == team1Name) && (rounds[j].m_Games[jj].AwayTeam == team2Name);
				bool VersedBefore2 = (rounds[j].m_Games[jj].HomeTeam == team2Name) && (rounds[j].m_Games[jj].AwayTeam == team1Name);
				if (VersedBefore1 || VersedBefore2)
				{
					count++;
					if (VersedBefore1)
					{
						exactLineUp++;
					}
					if (count >= limit || exactLineUp > limit/2)
					{
						teams.push_back(team1Name);
						AttemptedTeams.push_back(team2Name);
						return false;
					}
				}
			}
		}
	}
	games.push_back(SRLGameMatchup(team1Name, team2Name));
	return true;
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

ConsoleWindow SRLGame::ExportPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (exportConfirmedCall)
	{
		exportCall = false;
		exportConfirmedCall = false;
		try
		{
			if (currentState == ResultsViewState)
			{
				if (m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].ResultPlayByPlay.empty())
				{
					errorCall = true;
					errorMessage = "No data to export";
					return window;
				}

				std::chrono::system_clock currentTime;
				std::time_t t = std::chrono::system_clock::to_time_t(currentTime.now());
				std::string time = std::ctime(&t);
				time.resize(time.size() - 1);
				string fileName = "EngineFiles\\SavedGameResults\\" + m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].HomeTeam + "v" + m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].AwayTeam + "_" + time + ".txt";
				fileName.erase(std::remove(fileName.begin(), fileName.end(), ':'), fileName.end());
				fileName.erase(std::remove(fileName.begin(), fileName.end(), ' '), fileName.end());
				std::ofstream output_file(fileName.c_str());
				for (const auto& e : m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].ResultPlayByPlay) output_file << e << "\n";
			}
			else if (currentState == SeasonModeState)
			{
				if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
				{
					errorCall = true;
					errorMessage = "Season must be complete first";
					return window;
				}
				vector<string> temp;
				temp.push_back("LADDER RESULTS");
				temp.push_back("--------------------------------");
				for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
				{
					temp.push_back(to_string(i + 1) + ". " + m_Season.m_Ladder.m_Ladder[i].teamName + " Wins: " + to_string(m_Season.m_Ladder.m_Ladder[i].won) + "| Lost: " + to_string(m_Season.m_Ladder.m_Ladder[i].lost) + "| PD: " + to_string(m_Season.m_Ladder.m_Ladder[i].pointsDifference) + "| Points: " + to_string(m_Season.m_Ladder.m_Ladder[i].points));
				}
				temp.push_back("--------------------------------");
				temp.push_back("");
				for (int i = 0; i < m_Season.m_Draw.m_Rounds.size(); i++)
				{
					temp.push_back("Round " + to_string(i + 1) + " Results");
					temp.push_back("--------------------------------");
					for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_Games.size(); ii++)
					{
						temp.push_back(m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam + " " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamScore) + " v " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamScore) + " " + m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam);
					}
					temp.push_back("--------------------------------");
					temp.push_back("");
				}
				temp.push_back("Top Try Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopTries.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Goal Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopGoals.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Field Goal Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopFieldGoals.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Metres Ran");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopMetres.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Tackles Made");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopTackles.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most 40/20's Kicked");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_Top4020.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Kicking Metres");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopKickMetres.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Steals");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSteals.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most No Tries");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopNoTries.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Errors");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopErrors.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Penalties");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopPenalty.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Ruck Infringements");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopRuckErrors.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Sin Bins");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSinBin.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Send Offs");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSendOff.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Injuries");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopInjuries.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Point Scores");
				temp.push_back("--------------------------------");
				LeaderboardOutputStringsTopScorer(temp, m_Season.m_TopPoints.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Players Of The Season");
				temp.push_back("--------------------------------");
				LeaderboardOutputStringsTopPlayer(temp, m_Season.m_TopPlayers.shortlist);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("News Stories");
				temp.push_back("--------------------------------");
				for (int i = 0; i < m_Season.m_Draw.m_Rounds.size(); i++)
				{
					temp.push_back("");
					temp.push_back("Round " + to_string(i+1) + " News Stories");
					temp.push_back("--------------------------------");
					for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].newsStories.size(); ii++)
					{
						temp.push_back(m_Season.m_Draw.m_Rounds[i].newsStories[ii].headline);
					}
					temp.push_back("--------------------------------");
					temp.push_back("");
				}
				std::chrono::system_clock currentTime;
				std::time_t t = std::chrono::system_clock::to_time_t(currentTime.now());
				std::string time = std::ctime(&t);
				time.resize(time.size() - 1);
				string fileName = "EngineFiles\\SavedSeasonResults\\Season_" + time + ".txt";
				fileName.erase(std::remove(fileName.begin(), fileName.end(), ':'), fileName.end());
				fileName.erase(std::remove(fileName.begin(), fileName.end(), ' '), fileName.end());
				std::ofstream output_file(fileName.c_str());
				for (const auto& e : temp) output_file << e << "\n";

			}
		}
		catch (exception e)
		{
			errorCall = true;
			errorMessage = "Export Failed: unexpected error";
		}
		return window;
	}
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", GREEN_GREEN_BG);
		}
	}
	if (currentState == ResultsViewState)
	{
		window.setTextAtPoint(Vector2(6, 6), "Export Game To Text File?", BRIGHTWHITE_GREEN_BG);
	}
	else if (currentState == SeasonModeState)
	{
		window.setTextAtPoint(Vector2(6, 6), "Export Season To Text File?", BRIGHTWHITE_GREEN_BG);
	}
	window = m_ExportOKBtn.draw_ui(window);
	window = m_ExportCNCLBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::BetPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 5; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", GREEN_GREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), errorMessage, BRIGHTWHITE_GREEN_BG);
	window = m_BetOkViewBtn.draw_ui(window);
	window = m_BetCnclViewBtn.draw_ui(window);
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

#pragma endregion

#pragma region Simulate

void SRLGame::CalculateOdds()
{
	//CalculateOdds
	m_BetButtons.clear();
	for (int i = 0, j = 2; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++, j+=2)
	{
		SRLTeam oddsHomeTeam;
		oddsHomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
		SYDEClickableButton a_BetBtnH = SYDEClickableButton("Bet $10",Vector2(42, j+1), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnH.SetFunc(BetMatchClick);
		a_BetBtnH.setTag(to_string(i) + ";10;0;" + "H;" + oddsHomeTeam.getName());
		m_BetButtons.push_back(a_BetBtnH);
		SYDEClickableButton a_BetBtnHCustom = SYDEClickableButton("$Custom", Vector2(51, j + 1), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnHCustom.SetFunc(CustomBetClick);
		a_BetBtnHCustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "H;" + oddsHomeTeam.getName());
		m_BetButtons.push_back(a_BetBtnHCustom);
		SRLTeam oddsAwayTeam;
		oddsAwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
		SYDEClickableButton a_BetBtnA = SYDEClickableButton("Bet $10", Vector2(42, j + 2), Vector2(7, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
		a_BetBtnA.SetFunc(BetMatchClick);
		a_BetBtnA.setTag(to_string(i) + ";10;0;" + "A;" + oddsAwayTeam.getName());
		m_BetButtons.push_back(a_BetBtnA);
		SYDEClickableButton a_BetBtnACustom = SYDEClickableButton("$Custom", Vector2(51, j + 2), Vector2(7, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
		a_BetBtnACustom.SetFunc(CustomBetClick);
		a_BetBtnACustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "A;" + oddsAwayTeam.getName());
		m_BetButtons.push_back(a_BetBtnACustom);
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
	CalculateTipMaster();
}

void SRLGame::CalculatePremiershipOdds()
{
	m_PremiershipBetButtons.clear();
	for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
	{
		int currentThreshold = m_Season.m_Ladder.m_Ladder[finalsThreshold - 1].points;
		int winDiff = m_Season.m_Ladder.m_Ladder[i].won - m_Season.m_Ladder.m_Ladder[i].lost;
		int maxPointsSeason = seasonLength * 2;
		int maxPointsCurrent = m_roundToSimulate * 2;
		int maxPointsPotential = m_Season.m_Ladder.m_Ladder[i].points + ((seasonLength - m_roundToSimulate) * 2);
		if (m_roundToSimulate >= seasonLength)
		{
			maxPointsCurrent = maxPointsSeason;
		}
		if (maxPointsCurrent == 0)
		{
			maxPointsCurrent = 1;
		}

		int pointPercent = (m_Season.m_Ladder.m_Ladder[i].points / maxPointsCurrent) * 100;
		int ladderAdj = i * 25;
		int oddsCents = 500;
		oddsCents += ladderAdj;
		oddsCents -= pointPercent;
		m_Season.m_Ladder.m_Ladder[i].premiershipOdds = SRLBetPrice(oddsCents / 100, oddsCents % 100);
		if (currentThreshold > maxPointsPotential)
		{
			m_Season.m_Ladder.m_Ladder[i].premiershipOdds.suspended = true;
		}
		if (!m_Season.m_Ladder.m_Ladder[i].premiershipOdds.suspended)
		{
			SYDEClickableButton a_BetBtn = SYDEClickableButton("Bet $10", Vector2(42, i + 3), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
			a_BetBtn.SetFunc(BetMatchClick);
			a_BetBtn.setTag(to_string(i) + ";10;0;" + "P;" + m_Season.m_Ladder.m_Ladder[i].teamName);
			m_PremiershipBetButtons.push_back(a_BetBtn);
			SYDEClickableButton a_BetBtnCustom = SYDEClickableButton("$Custom", Vector2(51, i + 3), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
			a_BetBtnCustom.SetFunc(CustomBetClick);
			a_BetBtnCustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "P;" + m_Season.m_Ladder.m_Ladder[i].teamName);
			m_PremiershipBetButtons.push_back(a_BetBtnCustom);
		}
	}
}

void SRLGame::SimulateGames()
{
	int roundsSimulated = 0;
	while (Simulate)
	{
		int m_ArticlesRemaining = newsArticlesPerRound;
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
			m_srlmanager.injuriesEffect(m_Injuries);
			m_srlmanager.sinBinsEffect(m_SinBins);
			m_srlmanager.extraTimeEffect(m_ExtraTime);
			try
			{
				m_srlmanager.addTeamLineupsPlayByPlay();
				m_srlmanager.addStartTimePlay();
				bool continuePlay = finals || m_ExtraTime;
				while (m_srlmanager.getMinutesPassed() < 80 || (m_srlmanager.isTied() && continuePlay))
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
			if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.gameNumber == i)
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.fg_homeTeamScore = m_srlmanager.getHomeScore();
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.fg_awayTeamScore = m_srlmanager.getAwayScore();
			}

			if (m_srlmanager.getHomeScore() > m_srlmanager.getAwayScore())
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam;
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].LosingTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam;
			}
			else if (m_srlmanager.getHomeScore() < m_srlmanager.getAwayScore())
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam;
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].LosingTeam = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam;
			}
			else
			{
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].tiedGame = true;
			}
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].ResultPlayByPlay = m_srlmanager.getPlayByPlay();
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].SummaryPlayByPlay = m_srlmanager.getSummary();

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
				m_Season.m_TopSinBin.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getSinBins());
				m_Season.m_TopSendOff.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getSendOffs());
				m_Season.m_TopInjuries.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getInjuries());
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
				m_Season.m_TopSinBin.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getSinBins());
				m_Season.m_TopSendOff.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getSendOffs());
				m_Season.m_TopInjuries.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getInjuries());
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
			m_Season.m_TopSinBin.orderShortlist();
			m_Season.m_TopSendOff.orderShortlist();
			m_Season.m_TopInjuries.orderShortlist();

			for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets.size(); ii++)
			{
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam)
				{
					m_BetMoney.addBetPrice(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].ReturnBetWinnings());
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].betState = Bet_Won;
				}
				else if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].LosingTeam)
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].betState = Bet_Lost;
				}
				else if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].tiedGame)
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].betState = Bet_Lost;
				}
				else if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].tiedGame)
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii].betState = Bet_Lost;
				}
				checkSpecificBetAchievements(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Bets[ii]);
			}

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
						else if (m_srlmanager.getHomeScore() < m_srlmanager.getAwayScore())
						{
							m_Season.m_Ladder.m_Ladder[ii].lost++;
						}
						else
						{
							m_Season.m_Ladder.m_Ladder[ii].points++;
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
						else if (m_srlmanager.getHomeScore() > m_srlmanager.getAwayScore())
						{
							m_Season.m_Ladder.m_Ladder[ii].lost++;
						}
						else
						{
							m_Season.m_Ladder.m_Ladder[ii].points++;
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
		m_roundToSimulate++;

		//NEWS STORIES
		if (m_SeasonEvents)
		{
			int noTrades1 = rand() % 3;
			for (int i = 0; i < noTrades1; i++)
			{
				offContractTrade();
				m_ArticlesRemaining--;
			}
			int noTrades2 = rand() % 3;
			for (int i = 0; i < noTrades2; i++)
			{
				TeamTrade();
				m_ArticlesRemaining--;
			}
		}

		if (m_roundToSimulate >= m_Season.m_Draw.m_Rounds.size())
		{
			finals = true;
			//THAT WAS GRAND FINAL, FINISH SEASON
			if (m_roundToSimulate >= BaseSeasonGames + finalsRounds)
			{
				for (int ii = 0; ii < m_Season.m_PremiershipBets.size(); ii++)
				{
					if (m_Season.m_PremiershipBets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate -1].m_Games[0].WinningTeam)
					{
						m_BetMoney.addBetPrice(m_Season.m_PremiershipBets[ii].ReturnBetWinnings());
						m_Season.m_PremiershipBets[ii].betState = Bet_Won;
						AchievementStrings.push_back("SRL_PREMIERSHIP_TIP");
					}
					else
					{
						m_Season.m_PremiershipBets[ii].betState = Bet_Lost;
						if (m_Season.m_PremiershipBets[ii].m_teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].m_Games[0].LosingTeam)
						{
							AchievementStrings.push_back("SRL_BET_CHALLENGE4");
						}
						else if (m_Season.m_PremiershipBets[ii].m_teamName == m_Season.m_Ladder.m_Ladder[m_Season.m_Ladder.m_Ladder.size() - 1].teamName)
						{
							AchievementStrings.push_back("SRL_SPOONBET");
						}
					}
				}
				SRLNewsArticle m_PremiershipArticle;
				m_PremiershipArticle.headline = m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].m_Games[0].WinningTeam + " Wins Premiership!";
				m_PremiershipArticle.newsStory = SRLNewsStoryGenerator::generatePremiershipArticle(m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].m_Games[0].WinningTeam);
				m_PremiershipArticle.type = SRLAT_Premiership;
				m_PremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Premiership.bmp", 7, 7));
				m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_PremiershipArticle);
				m_ArticlesRemaining--;
				UpdateBets();
				if (currentBetsTotalSeasonMatchOnly >= 36 && currentWonBetsSeasonMatchOnly == currentBetsTotalSeasonMatchOnly)
				{
					AchievementStrings.push_back("SRL_BET_CHALLENGE1");
				}
				else if (currentBetsTotalSeasonMatchOnly == 1 && currentWonBetsSeasonMatchOnly == 0)
				{
					AchievementStrings.push_back("SRL_BET_CHALLENGE2");
				}
				else if (currentBetsTotalSeasonMatchOnly == 100 && currentWonBetsSeasonMatchOnly == 50)
				{
					AchievementStrings.push_back("SRL_BET_CHALLENGE3");
				}
				AchievementStrings.push_back("SRL_FIRST_SEASON");
				if (seasonLength == Length_ShortSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_SHORT_SEASON");
				}
				else if (seasonLength == Length_RoundRobin && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_ROUND_ROBIN");
				}
				else if (seasonLength == Length_MediumSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_MEDIUM_SEASON");
				}
				else if (seasonLength == Length_NormalSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_NORMAL_SEASON");
				}
				else if (seasonLength == Length_LongSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_LONG_SEASON");
				}
				else if (seasonLength == Length_ExtremeSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_EXTREME_SEASON");
				}
				else if (seasonLength == Length_EnduranceSeason && BaseSeasonGames != 0)
				{
					AchievementStrings.push_back("SRL_ENDURANCE_SEASON");
				}
				checkBetAchievements();
			}
			else
			{
				if (fsType == Top8Normal)
				{
#pragma region top 8 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //1v4
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[2].teamName)); //2v3
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[4].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //5v8
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[5].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //6v7
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

						SRLNewsArticle m_MinorPremiershipArticle;
						m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
						m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
						m_MinorPremiershipArticle.type = SRLAT_Premiership;
						m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
						m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
						m_ArticlesRemaining--;

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
#pragma endregion
				}
				else if (fsType == Top4Normal)
				{
#pragma region top 4 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[1].teamName)); //1v2
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //3v4
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

						SRLNewsArticle m_MinorPremiershipArticle;
						m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
						m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
						m_MinorPremiershipArticle.type = SRLAT_Premiership;
						m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
						m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
						m_ArticlesRemaining--;

					}
					else if (m_roundToSimulate == BaseSeasonGames + 1)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam)); //2v3
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					}
					else if (m_roundToSimulate == BaseSeasonGames + 2)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam));//1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					}
#pragma endregion
				}
				else if (fsType == Top2Normal)
				{
#pragma region top 2 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[1].teamName)); //1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

						SRLNewsArticle m_MinorPremiershipArticle;
						m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
						m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
						m_MinorPremiershipArticle.type = SRLAT_Premiership;
						m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
						m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
						m_ArticlesRemaining--;

					}
#pragma endregion
				}
				else if (fsType == Top8Knockout)
				{
#pragma region top 8 knockout simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //1v8
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //2v7
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[5].teamName)); //3v6
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[3].teamName, m_Season.m_Ladder.m_Ladder[4].teamName)); //4v5
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

						SRLNewsArticle m_MinorPremiershipArticle;
						m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
						m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
						m_MinorPremiershipArticle.type = SRLAT_Premiership;
						m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
						m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
						m_ArticlesRemaining--;
					}
					else if (m_roundToSimulate == BaseSeasonGames + 1)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //1v4
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //2v3
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					}
					else if (m_roundToSimulate == BaseSeasonGames + 2)
					{
						vector<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					}
#pragma endregion
				}
				else if (fsType == Top4Knockout)
				{
#pragma region top 4 knockout simulation
				if (m_roundToSimulate == BaseSeasonGames)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[2].teamName)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

					SRLNewsArticle m_MinorPremiershipArticle;
					m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
					m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
					m_MinorPremiershipArticle.type = SRLAT_Premiership;
					m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
					m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
					m_ArticlesRemaining--;
				}
				else if (m_roundToSimulate == BaseSeasonGames + 1)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam)); //1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
#pragma endregion
				}
				else if (fsType == Top8DoubleElim)
				{
#pragma region top 8 knockout double elimination simulation
				if (m_roundToSimulate == BaseSeasonGames)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[5].teamName)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[3].teamName, m_Season.m_Ladder.m_Ladder[4].teamName)); //4v5
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));

					SRLNewsArticle m_MinorPremiershipArticle;
					m_MinorPremiershipArticle.headline = m_Season.m_Ladder.m_Ladder[0].teamName + " Wins Minor Premiership!";
					m_MinorPremiershipArticle.newsStory = SRLNewsStoryGenerator::generateMinorPremiershipArticle(m_Season.m_Ladder.m_Ladder[0].teamName);
					m_MinorPremiershipArticle.type = SRLAT_Premiership;
					m_MinorPremiershipArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\MinorPremiership.bmp", 7, 7));
					m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_MinorPremiershipArticle);
					m_ArticlesRemaining--;
				}
				else if (m_roundToSimulate == BaseSeasonGames + 1)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //2v3

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam)); //5v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam)); //6v7
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v2

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].WinningTeam));//3v5
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam));//4v6
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[2].WinningTeam));//3v4
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 4)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].WinningTeam));//2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 5)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[0].WinningTeam));//1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
#pragma endregion
				}
				else if (fsType == KnockoutTournament)
				{
#pragma region 16 Team Knockout

				/*
					games.push_back(SRLGameMatchup(AvailableTeams[0], AvailableTeams[15]));
					games.push_back(SRLGameMatchup(AvailableTeams[1], AvailableTeams[14]));
					games.push_back(SRLGameMatchup(AvailableTeams[2], AvailableTeams[13]));
					games.push_back(SRLGameMatchup(AvailableTeams[3], AvailableTeams[12]));
					games.push_back(SRLGameMatchup(AvailableTeams[4], AvailableTeams[11]));
					games.push_back(SRLGameMatchup(AvailableTeams[5], AvailableTeams[10]));
					games.push_back(SRLGameMatchup(AvailableTeams[6], AvailableTeams[9]));
					games.push_back(SRLGameMatchup(AvailableTeams[7], AvailableTeams[8]));
				*/


				if (m_roundToSimulate == BaseSeasonGames + 1)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].WinningTeam)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].WinningTeam)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].WinningTeam)); //4v5
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames+ 1].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam));//1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
#pragma endregion
				}
				else if (fsType == KnockoutTournamentDouble)
				{
#pragma region 16 Team Knockout Double Elimination

				/*
					games.push_back(SRLGameMatchup(AvailableTeams[0], AvailableTeams[15])); 1v16
					games.push_back(SRLGameMatchup(AvailableTeams[1], AvailableTeams[14])); 2v15
					games.push_back(SRLGameMatchup(AvailableTeams[2], AvailableTeams[13])); 3v14
					games.push_back(SRLGameMatchup(AvailableTeams[3], AvailableTeams[12])); 4v13
					games.push_back(SRLGameMatchup(AvailableTeams[4], AvailableTeams[11])); 5v12
					games.push_back(SRLGameMatchup(AvailableTeams[5], AvailableTeams[10])); 6v11
					games.push_back(SRLGameMatchup(AvailableTeams[6], AvailableTeams[9])); 7v10
					games.push_back(SRLGameMatchup(AvailableTeams[7], AvailableTeams[8])); 8v9
				*/


				if (m_roundToSimulate == BaseSeasonGames + 1)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].WinningTeam)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].WinningTeam)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].WinningTeam)); //4v5

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].LosingTeam)); //9v16
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].LosingTeam)); //10v15
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].LosingTeam)); //11v14
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].LosingTeam)); //12v13
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam)); //2v3

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[7].WinningTeam)); //8v12
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[6].WinningTeam)); //7v11
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[5].WinningTeam)); //6v10
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[4].WinningTeam)); //5v9

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam)); //1v2

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[5].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[2].WinningTeam)); //5v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[4].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[3].WinningTeam)); //6v7

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 4)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[2].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[1].WinningTeam)); //4v5

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 5)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[1].WinningTeam)); //3v4
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 6)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 5].m_Games[0].WinningTeam)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
				else if (m_roundToSimulate == BaseSeasonGames + 7)
				{
					vector<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 6].m_Games[0].WinningTeam)); //1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
				}
#pragma endregion
				}
			}
		}
		for (int i = 0; i < m_ArticlesRemaining; i++)
		{
			otherArticles();
		}
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
		{
			CalculateOdds();
			CalculatePremiershipOdds();
			UpdateBets();
			CalculateFeaturedGame();
		}
	}
}

void SRLGame::CalculateFeaturedGame()
{
	int featureGameNumber = 0;
	if (finals)
	{
		int difference = 10000;
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
		{
			int price1 = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamOdds.getAsCents();
			
			price1 -= m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamOdds.getAsCents();
			if (price1 < 0)
			{
				price1 = -price1;
			}
			if (price1 < difference)
			{
				difference = price1;
				featureGameNumber = i;
			}
		}
	}
	else
	{
		int ladderDifference = 10000;
		int highestPos = 10000;
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
		{
			int homeTeamPos, awayTeamPos = 0;
			for (int ii = 0; ii < m_Season.m_Ladder.m_Ladder.size(); ii++)
			{
				if (m_Season.m_Ladder.m_Ladder[ii].teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam)
				{
					homeTeamPos = ii;
				}
				if (m_Season.m_Ladder.m_Ladder[ii].teamName == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam)
				{
					awayTeamPos = ii;
				}
			}
			int diff = homeTeamPos - awayTeamPos;
			if (diff < 0)
			{
				diff = -diff;
			}
			if (diff < ladderDifference)
			{
				ladderDifference = diff;
				if (homeTeamPos < highestPos)
				{
					highestPos = homeTeamPos;
				}
				if (awayTeamPos < highestPos)
				{
					highestPos = awayTeamPos;
				}
				featureGameNumber = i;
			}
			else if (diff == ladderDifference)
			{
				if (homeTeamPos < highestPos)
				{
					highestPos = homeTeamPos;
					featureGameNumber = i;
				}
				if (awayTeamPos < highestPos)
				{
					highestPos = awayTeamPos;
					featureGameNumber = i;
				}
			}

		}	
	}
	m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature = FeaturedGame(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam, astVars, featureGameNumber, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].homeTeamOdds, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].awayTeamOdds);
	for (int i = 0; i < m_roundToSimulate;i++)
	{
		for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[ii].m_Games.size(); ii++)
		{
			bool homeTeamInMatch = m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam || m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam;
			bool awayTeamInMatch = m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam || m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam;
			if (homeTeamInMatch && awayTeamInMatch)
			{
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory[0] == "No Match History To Show")
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.clear();
				}
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.push_back(m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam + " " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamScore) + " v " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamScore) + " " + m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam);
			}
		}
	}
	reverse(m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.begin(), m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.end());
}

void SRLGame::CalculateTipMaster()
{
	TipMasterBets.clear();
	int gameBetOn = rand() % m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size();
	int homeTeam = rand() % 50;
	if (homeTeam > 25)
	{
		TipMasterBets.push_back(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameBetOn].HomeTeam + " @ " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameBetOn].homeTeamOdds.ReturnPrice());
	}
	else
	{
		TipMasterBets.push_back(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameBetOn].AwayTeam + " @ " + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[gameBetOn].awayTeamOdds.ReturnPrice());
	}
	SRLNameGenerator::generateAndAddToVector(TipMasterBets);
}

void SRLGame::saveGameSettings()
{
	json save_file;
	//PlayerStats
	save_file["soundvolume"] = static_cast<int>(BaseSYDESoundSettings::getDefaultVolumeState());
	save_file["soundtrackon"] = static_cast<int>(soundTrackOn);
	save_file["scrollspeed"] = m_ScrollingSpeed;
	string filePath = string("EngineFiles\\Settings\\gameSettings.json");
	std::ofstream ofs(filePath);
	ofs << save_file;
}

void SRLGame::loadGameSettings()
{
	if (SYDEFileDefaults::exists("EngineFiles\\Settings\\gameSettings.json"))
	{
		try
		{
			std::ifstream ifs{ "EngineFiles\\Settings\\gameSettings.json" };
			json save_file = json::parse(ifs);
			int volume = save_file["soundvolume"];
			BaseSYDESoundSettings::changeDefaultVolume(static_cast<SYDESoundVolume>(volume));
			volume = save_file["soundtrackon"];
			soundTrackOn = static_cast<bool>(volume);
			m_ScrollingSpeed = save_file["scrollspeed"];
		}
		catch (exception e)
		{

		}
	}
}

void SRLGame::sortOutNews()
{
	m_NewsHeadlines.clear();
	for (int i = 0, j =3; i < m_Season.m_Draw.m_Rounds[m_round].newsStories.size(); i++, j+=2)
	{
		ColourClass _COLOUR = BLACK_BRIGHTWHITE_BG;
		switch (m_Season.m_Draw.m_Rounds[m_round].newsStories[i].type)
		{
		case SRLAT_Premiership:
			_COLOUR = BRIGHTWHITE_GREEN_BG;
			break;
		case SRLAT_PlayerSign:
			_COLOUR = BLACK_LIGHTPURPLE_BG;
			break;
		case SRLAT_PlayerTrade:
			_COLOUR = BLACK_BRIGHTYELLOW_BG;
			break;
		case SRLAT_DropPlayer:
			_COLOUR = BLACK_BRIGHTRED_BG;
			break;
		}
		SYDEClickableButton a_Headline = SYDEClickableButton(" " + m_Season.m_Draw.m_Rounds[m_round].newsStories[i].headline, Vector2(2, j), Vector2(m_Season.m_Draw.m_Rounds[m_round].newsStories[i].headline.length() + 2, 1), _COLOUR, false);
		a_Headline.SetFunc(ArticleClick);
		a_Headline.setTag(to_string(i));
		m_NewsHeadlines.push_back(a_Headline);
	}
}

void SRLGame::checkSpecificBetAchievements(SRLGameBet _bet)
{
	if (_bet.betAmount.dollars >= 1000)
	{
		if (_bet.betOdds.dollars > 3 && _bet.betState == Bet_Won)
		{
			AchievementStrings.push_back("SRL_NO_DOUBT");
		}
		if (_bet.betOdds.dollars = 1 && _bet.betOdds.cents < 40 && _bet.betState == Bet_Lost)
		{
			AchievementStrings.push_back("SRL_ALWAYS_DOUBT");
		}
	}
}

void SRLGame::checkBetAchievements()
{
	if (m_BetMoney.dollars == 0 && m_BetMoney.cents == 0)
	{
		AchievementStrings.push_back("SRL_BANKRUPT");
	}
	if (m_BetMoney.dollars >= 10000)
	{
		AchievementStrings.push_back("SRL_HIGH_ROLLER");
	}
	if (m_BetMoney.dollars == 0 && m_BetMoney.cents == 1)
	{
		AchievementStrings.push_back("SRL_HANGING_ON");
	}
}

void SRLGame::offContractTrade()
{
	//TRADE OFF CONTRACT
	SRLTeam offContract;
	offContract.loadTeamOffContract("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json");
	int team1 = rand() % 16;
	SRLTeam MainTeam;
	MainTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team1].teamName + ".json");
	int player1 = MainTeam.getRandomPlayerInt();
	int player2 = offContract.getRandomPlayerInt();
	SRLPlayer Player1Character = MainTeam.getPlayers()[player1];
	SRLPlayer Player2Character = offContract.getPlayers()[player2];
	for (int i = 0; i < MainTeam.getPlayers().size(); i++)
	{
		//DO NOT ALLOW TRADE IF MAIN TEAM HAS A PLAYER WITH THE SAME NAME, THIS WILL CAUSE CONFUSION WITH LEADERBOARD
		if (MainTeam.getPlayers()[i].getName() == Player2Character.getName())
		{
			return;
		}
	}

	MainTeam.setPlayer(player1, Player2Character);
	offContract.setPlayer(player2, Player1Character);
	SRLNewsArticle m_SigningArticle;
	m_SigningArticle.headline = m_Season.m_Ladder.m_Ladder[team1].teamName + " Sign " + Player2Character.getName();
	m_SigningArticle.newsStory = SRLNewsStoryGenerator::generateOffContractTradeArticle(m_Season.m_Ladder.m_Ladder[team1].teamName, Player2Character.getName(), Player1Character.getName());
	m_SigningArticle.type = SRLAT_PlayerSign;
	m_SigningArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
	m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_SigningArticle);

	m_Season.m_TopPlayers.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_Top4020.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());

	m_Season.m_TopPlayers.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_Top4020.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());

	MainTeam.saveTeam();
	offContract.saveTeamOffContract();
}

bool SRLGame::offContractTrade(int team1, int player1)
{
	//TRADE OFF CONTRACT
	SRLTeam offContract;
	offContract.loadTeamOffContract("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json");
	SRLTeam MainTeam;
	MainTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team1].teamName + ".json");
	int player2 = offContract.getRandomPlayerInt();
	SRLPlayer Player1Character = MainTeam.getPlayers()[player1];
	SRLPlayer Player2Character = offContract.getPlayers()[player2];
	for (int i = 0; i < MainTeam.getPlayers().size(); i++)
	{
		//DO NOT ALLOW TRADE IF MAIN TEAM HAS A PLAYER WITH THE SAME NAME, THIS WILL CAUSE CONFUSION WITH LEADERBOARD
		if (MainTeam.getPlayers()[i].getName() == Player2Character.getName())
		{
			return false;
		}
	}
	MainTeam.setPlayer(player1, Player2Character);
	offContract.setPlayer(player2, Player1Character);

	m_Season.m_TopPlayers.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_Top4020.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());

	m_Season.m_TopPlayers.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_Top4020.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());

	MainTeam.saveTeam();
	offContract.saveTeamOffContract();
	return true;
}

void SRLGame::TeamTrade()
{
	//TRADE OFF
	int team1 = rand() % 16;
	int team2 = rand() % 16;
	if (team1 == team2)
	{
		return;
	}
	SRLTeam MainTeam;
	MainTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team1].teamName + ".json");
	SRLTeam offContract;
	offContract.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team2].teamName + ".json");
	int player1 = MainTeam.getRandomPlayerInt();
	int player2 = offContract.getRandomPlayerInt();
	SRLPlayer Player1Character = MainTeam.getPlayers()[player1];
	SRLPlayer Player2Character = offContract.getPlayers()[player2];
	for (int i = 0; i < MainTeam.getPlayers().size(); i++)
	{
		//DO NOT ALLOW TRADE IF MAIN TEAM HAS A PLAYER WITH THE SAME NAME, THIS WILL CAUSE CONFUSION WITH LEADERBOARD
		if (MainTeam.getPlayers()[i].getName() == Player2Character.getName())
		{
			return;
		}
		else if (offContract.getPlayers()[i].getName() == Player1Character.getName())
		{
			return;
		}
	}
	MainTeam.setPlayer(player1, Player2Character);
	offContract.setPlayer(player2, Player1Character);
	SRLNewsArticle m_SigningArticle;
	m_SigningArticle.headline = m_Season.m_Ladder.m_Ladder[team1].teamName + " Sign " + Player2Character.getName();
	m_SigningArticle.newsStory = SRLNewsStoryGenerator::generateTradeArticle(m_Season.m_Ladder.m_Ladder[team1].teamName, m_Season.m_Ladder.m_Ladder[team2].teamName, Player1Character.getName(), Player2Character.getName());
	m_SigningArticle.type = SRLAT_PlayerTrade;
	m_SigningArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
	m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_SigningArticle);

	m_Season.m_TopPlayers.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_Top4020.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player1Character.getName(), MainTeam.getName(), offContract.getName());

	m_Season.m_TopPlayers.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPoints.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopFieldGoals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_Top4020.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopTackles.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopKickMetres.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopPenalty.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSteals.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopNoTries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopRuckErrors.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSinBin.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopSendOff.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());
	m_Season.m_TopInjuries.changePlayerTeam(Player2Character.getName(), offContract.getName(), MainTeam.getName());

	MainTeam.saveTeam();
	offContract.saveTeam();
}

void SRLGame::UpdateBets()
{
	m_GameBetsWriteUp.clear();
	m_PremiershipBetsWriteUp.clear();
	currentWonBetsSeason = 0;
	currentLostBetsSeason = 0;
	currentBetsTotalSeason = 0;
	currentWonBetsSeasonMatchOnly = 0;
	currentLostBetsSeasonMatchOnly = 0;
	currentBetsTotalSeasonMatchOnly = 0;
	for (int i = 0; i < m_Season.m_Draw.m_Rounds.size(); i++)
	{
		for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_Bets.size(); ii++)
		{
			SRLGameBetsWriting writeUp;
			writeUp.name = "Round " + to_string(i + 1) + ": " + m_Season.m_Draw.m_Rounds[i].m_Bets[ii].m_teamName + " " + m_Season.m_Draw.m_Rounds[i].m_Bets[ii].originalBetAmount.ReturnPrice() + " @ " + m_Season.m_Draw.m_Rounds[i].m_Bets[ii].betOdds.ReturnPrice();
			switch (m_Season.m_Draw.m_Rounds[i].m_Bets[ii].betState)
			{
			case Bet_Won:
				currentWonBetsSeason++;
				currentWonBetsSeasonMatchOnly++;
				writeUp.colour = GREEN;
				break;
			case Bet_Lost:
				currentLostBetsSeason++;
				currentLostBetsSeasonMatchOnly++;
				writeUp.colour = RED;
				break;
			default:
				writeUp.colour = BRIGHTWHITE;
				break;
			}
			currentBetsTotalSeason++;
			currentBetsTotalSeasonMatchOnly++;
			m_GameBetsWriteUp.push_back(writeUp);
		}
	}
	for (int ii = 0; ii < m_Season.m_PremiershipBets.size(); ii++)
	{
		SRLGameBetsWriting writeUp;
		writeUp.name = m_Season.m_PremiershipBets[ii].m_teamName + " " + m_Season.m_PremiershipBets[ii].originalBetAmount.ReturnPrice() + " @ " + m_Season.m_PremiershipBets[ii].betOdds.ReturnPrice();
		switch (m_Season.m_PremiershipBets[ii].betState)
		{
		case Bet_Won:
			currentWonBetsSeason++;
			writeUp.colour = GREEN;
			break;
		case Bet_Lost:
			currentLostBetsSeason++;
			writeUp.colour = RED;
			break;
		default:
			writeUp.colour = BRIGHTWHITE;
			break;
		}
		currentBetsTotalSeason++;
		m_PremiershipBetsWriteUp.push_back(writeUp);
	}
	if (currentBetsTotalSeason >= 100)
	{
		AchievementStrings.push_back("SRL_GAMBLING_ADDICT");
	}
	if (currentWonBetsSeason >= 100)
	{
		AchievementStrings.push_back("SRL_NOT_PROBLEM");
	}
	if (currentLostBetsSeason >= 100)
	{
		AchievementStrings.push_back("SRL_BIG_PROBLEM");
	}
}

void SRLGame::setUpTeamInDepthView(int teamViewing)
{
	m_TeamViewing = teamViewing;
	string teamLoad = SYDEFileDefaults::getAllFileNamesInFolder("EngineFiles\\GameResults\\Teams", ".json", true, true)[m_TeamViewing];
	m_InDepthTeamView.clearTeam();
	m_InDepthTeamView.loadTeam("EngineFiles\\GameResults\\Teams\\" + teamLoad + ".json");
	string JerseyBmp = "EngineFiles\\JerseyFeatures\\jersey" + to_string(m_InDepthTeamView.getJerseryType()) + ".bmp";
	wstring wJerseyBmp = wstring(JerseyBmp.begin(), JerseyBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_JerseyView = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	m_JerseyView.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	m_JerseyView.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	m_JerseyView.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	m_JerseyView.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, m_InDepthTeamView.getPrimary());
	m_JerseyView.changeAllInstancesOfColour(BLACK_WHITE_BG, m_InDepthTeamView.getSecondary());
	m_JerseyView.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, m_InDepthTeamView.getBadge());

	m_InDepthTeamView.CalculateAverages();
}

void SRLGame::setUpPlayer()
{
	m_PlayerView = m_InDepthTeamView.getPlayers()[playerClicked];

	string PlayerBmp = "EngineFiles\\PlayerFeatures\\playerstyle" + to_string(m_PlayerView.getStyleType()) + ".bmp";
	wstring wPlayerBmp = wstring(PlayerBmp.begin(), PlayerBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_PlayerAsset = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wPlayerBmp.c_str(), 15, 15));
	m_PlayerAsset.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	m_PlayerAsset.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	m_PlayerAsset.changeAllInstancesOfColour(BLACK_WHITE_BG, m_PlayerView.getPrimary());
	m_PlayerAsset.changeAllInstancesOfColour(BLACK, m_PlayerView.getSecondary());
	m_PlayerAsset.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, m_PlayerView.getTertiary());
}
void SRLGame::otherArticles()
{
	SRLNewsArticle m_Article;
	int articleType = rand() % 1000;
	int team = rand() % 16;
	int team2 = rand() % 16;
	while (team2 == team)
	{
		team2 = rand() % 16;
	}
	SRLTeam MainTeam;
	MainTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team].teamName + ".json");
	int player = MainTeam.getRandomPlayerInt();
	SRLPlayer playerStory = MainTeam.getPlayers()[player];
	SRLTeam OtherTeam;
	OtherTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team2].teamName + ".json");
	int player2 = OtherTeam.getRandomPlayerInt();
	SRLPlayer playerOther = OtherTeam.getPlayers()[player2];

	switch (articleType)
	{
#pragma region Articles
	case 0:
		if (m_SeasonEvents)
		{
			if (offContractTrade(team, player))
			{
				m_Article.headline = MainTeam.getName() + " Drop " + playerStory.getName();
				m_Article.newsStory = SRLNewsStoryGenerator::generateArticleDropControversialPlayer(MainTeam.getName(), playerStory.getName(), team, player);
				m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
				m_Article.type = SRLAT_DropPlayer;
			}
		}
		else
		{
			return;
		}
		break;
		break;
	case 10:
		if (m_SeasonEvents)
		{
			if (offContractTrade(team, player))
			{
				m_Article.headline = playerStory.getName() + " Walks Out On " + MainTeam.getName();
				m_Article.newsStory = SRLNewsStoryGenerator::generateArticleWalksOutOnClub(MainTeam.getName(), playerStory.getName(), team, player);
				m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
				m_Article.type = SRLAT_DropPlayer;
			}
		}
		else
		{
			return;
		}
		break;
	default:
		m_Article = SRLNewsStoryGenerator::getRandomStory(MainTeam, playerStory,OtherTeam, playerOther, astVars);
		break;
#pragma endregion
	}
	m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(m_Article);
}

void SRLGame::addCustomStrString(string charAdd)
{
	int maxLength = 4;
	if (customAmountStr.find('.') != std::string::npos) {
		maxLength = customAmountStr.find('.') + 3;
		if (charAdd == ".")
			return;
	}
	if (charAdd != "." && customAmountStr.length() >= maxLength)
	{
		return;
	}
	customAmountStr += charAdd;
}

void SRLGame::removeCustomStrString()
{
	if (customAmountStr.length() > 0)
	{
		customAmountStr = customAmountStr.substr(0, customAmountStr.size() - 1);
	}
}

void SRLGame::sortOutResultsScreen()
{
	m_ResultsScreenVector.clear();
	m_SummaryScreenVector.clear();
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
	vector<string> temp2 = m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].SummaryPlayByPlay;
	for (int i = 0; i < temp2.size(); i++)
	{
		m_SummaryScreenVector.push_back(temp2[i]);
	}
	m_LineResults = 0;
}

#pragma endregion

#pragma region Ladder
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

void SRLBetPrice::addCents(int c)
{
	int currentBalance = (dollars * 100) + cents;
	currentBalance += c;
	dollars = currentBalance / 100;
	cents = currentBalance % 100;
}

void SRLBetPrice::addBetPrice(SRLBetPrice bet)
{
	dollars += bet.dollars;
	cents += bet.cents;
	while (cents >= 100)
	{
		dollars++;
		cents -= 100;
	}
}

void SRLBetPrice::removeBetPrice(SRLBetPrice bet)
{
	dollars -= bet.dollars;
	cents -= bet.cents;
	while (cents < 0)
	{
		dollars--;
		cents += 100;
	}
}

bool SRLBetPrice::greaterThan(SRLBetPrice bet)
{
	if (dollars > bet.dollars)
	{
		return true;
	}
	else if (dollars == bet.dollars && cents > bet.cents)
	{
		return true;
	}
	return false;
}

bool SRLBetPrice::lessThan(SRLBetPrice bet)
{
	if (dollars < bet.dollars)
	{
		return true;
	}
	else if (dollars == bet.dollars && cents < bet.cents)
	{
		return true;
	}
	return false;
}

void SRLBetPrice::absolute()
{
	if (dollars < 0)
	{
		dollars = -dollars;
	}
	if (cents < 0)
	{
		cents = -cents;
	}
}

string SRLBetPrice::ReturnPrice()
{
	if (suspended)
	{
		return "Suspended";
	}
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

void SRLLeaderboard::changePlayerTeam(string playerName, string oldTeam, string newTeam)
{
	for (int i = 0; i < shortlist.size(); i++)
	{
		if (shortlist[i].TeamName == oldTeam && shortlist[i].Player == playerName)
		{
			shortlist[i].TeamName = newTeam;
			return;
		}
	}
}

#pragma endregion

SRLBetPrice SRLGameBet::ReturnBetWinnings()
{
	float betOddsF = betOdds.dollars;
	float centsTemp = betOdds.cents;
	betOddsF += (centsTemp / 100);
	float newDollars = 0;
	float newCents = betAmount.dollars * 100;
	newCents += betAmount.cents;
	newCents *= betOddsF;
	while (newCents >= 100)
	{
		newDollars++;
		newCents -= 100;
	}
	betAmount.dollars = newDollars;
	betAmount.cents = newCents;
	return betAmount;
}

FeaturedGame::FeaturedGame(string home, string away, AssetsClass astVars, int gameNo, SRLBetPrice homeOdds, SRLBetPrice awayOdds)
{	
	gameNumber = gameNo;
	fg_homeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + home + ".json");

	string JerseyBmp = "EngineFiles\\JerseyFeatures\\jersey" + to_string(fg_homeTeam.getJerseryType()) + ".bmp";
	wstring wJerseyBmp = wstring(JerseyBmp.begin(), JerseyBmp.end());
	fg_homeTeamJersey = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	fg_homeTeamJersey.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	fg_homeTeamJersey.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	fg_homeTeamJersey.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, fg_homeTeam.getPrimary());
	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_WHITE_BG, fg_homeTeam.getSecondary());
	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, fg_homeTeam.getBadge());

	fg_awayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + away + ".json");

	JerseyBmp = "EngineFiles\\JerseyFeatures\\jersey" + to_string(fg_awayTeam.getJerseryType()) + ".bmp";
	wJerseyBmp = wstring(JerseyBmp.begin(), JerseyBmp.end());
	fg_awayTeamJersey = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	fg_awayTeamJersey.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	fg_awayTeamJersey.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	fg_awayTeamJersey.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	fg_awayTeamJersey.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, fg_awayTeam.getPrimary());
	fg_awayTeamJersey.changeAllInstancesOfColour(BLACK_WHITE_BG, fg_awayTeam.getSecondary());
	fg_awayTeamJersey.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, fg_awayTeam.getBadge());

	featuredGameAvail = true;

	fg_homeOdds = homeOdds;
	fg_awayOdds = awayOdds;

	homeTeamKeyPlayers.clear();
	fg_homeTeam.addBestPlayers(homeTeamKeyPlayers, 5);
	awayTeamKeyPlayers.clear();
	fg_awayTeam.addBestPlayers(awayTeamKeyPlayers, 5);

}
