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
CoachingViewDrawState SRLGame::coachDrawState = CoachingMain_STATE;
SRLSeasonLength SRLGame::seasonLength = Length_NormalSeason;
SeasonConfigState SRLGame::seasCfgState = SelectSeasonTypeState;
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
bool SRLGame::RepRoundsOn = false;
//WOULD PREFER TO BE OFF BUT FOR SOME REASON MAIN BG DOESN"T LOAD WHEN IT IS SO RIP
bool SRLGame::m_ExtraTime = true;
bool SRLGame::m_Injuries = true;
bool SRLGame::m_SinBins = true;
bool SRLGame::m_ResultsTabCall = false;
bool SRLGame::soundTrackOn = true;
bool SRLGame::homeTeamBet = false;
bool SRLGame::betPlaceCall = false;
bool SRLGame::premiershipBet = false;
bool SRLGame::homeTeamTryBet = false;
bool SRLGame::m_SeasonEvents = true;
bool SRLGame::headlineCall = false;
bool SRLGame::keyPadCall = false;
bool SRLGame::playerCall = false;
bool SRLGame::performTradeCall = false;
bool SRLGame::performTradeConfirmedCall = false;
bool SRLGame::performTrainCall = false;
bool SRLGame::performTrainConfirmedCall = false;
bool SRLGame::setUpPosShowcaseCall = false;
bool SRLGame::TeamInDepthViewingJerseyAsset = true;
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
bool SRLGame::coachingMode = false;
bool SRLGame::selectedTeamCall = false;
bool SRLGame::performRefreshOptionsCall = false;
bool SRLGame::allowJsonExportingSeason = false;
string SRLGame::posToSwap = "";
bool SRLGame::posSwapCall = false;
SRLTrainingType SRLGame::trainType = Training_Attack;
int SRLGame::playerMainTeamTrade = 0;
int SRLGame::playerOtherTeamTrade = 0;
int SRLGame::exhibitionTeam1Num = 0;
int SRLGame::exhibitionTeam2Num = 1;
bool SRLGame::setUpExhibitionDisplayCall = false;
SRLSponsorTypeState SRLGame::sponsorState = SponsorState_Casino;
SRLPositionShowcaseState SRLGame::posSwapState = SRLPS_Backline;
SRLTeam SRLGame::otherTeamTrade = SRLTeam();
SRLTeamListViewState SRLGame::tlViewState = TLV_GeneralStats;

deque<string> SRLGame::AchievementStrings = deque<string>();
ArticleViewingState SRLGame::articleState = HeadlinesState;

SRLSoundtrack SRLGame::m_GamePlaySoundtrack = SRLSoundtrack();

#pragma endregion

/// <summary>
/// Split a string into a list of strings using a char as a splitter
/// </summary>
/// <param name="a_String"></param>
/// <param name="splitter"></param>
/// <returns></returns>
deque<string> Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::deque<std::string> splitString(arraySize);
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

/// <summary>
/// Convert the tag on the training button click into the static training values
/// </summary>
void DoTrainCallClick()
{
	//Acknowledge In SRLGame That Training Is Happening
	SRLGame::performTrainCall = true;
	//Get The Last Tag Of Buttons Clicked
	deque<string> training = Split(SYDEClickableButton::getLastButtonTag(), ';');
	//Convert The Tag
	if (training.size() > 4)
	{
		SRLGame::playerMainTeamTrade = stoi(training[1]);
		SRLGame::m_BetAmount.dollars = stoi(training[2]);
		SRLGame::m_BetAmount.cents = stoi(training[3]);
		SRLGame::trainType = static_cast<SRLTrainingType>(stoi(training[4]));
	}
	//ERROR, FALL BACK AND SHOW ERROR
	else
	{
		SRLGame::performTrainCall = false;
		SRLGame::errorCall = true;
		SRLGame::errorMessage = "Error whilst performing training";
	}
}

/// <summary>
/// Confirmation Click For Training
/// </summary>
void DoTrainCallOKClick()
{
	SRLGame::performTrainCall = false;
	SRLGame::performTrainConfirmedCall = true;
}

/// <summary>
/// Tell SRLGame to perform a refresh
/// </summary>
void DoPerformRefreshClick()
{
	SRLGame::performRefreshOptionsCall = true;
}

/// <summary>
/// Tell SRLGame that training was cancelled
/// </summary>
void DoTrainCallCNCLClick()
{
	SRLGame::performTrainCall = false;
}

/// <summary>
/// Convert the tag on the button to trading values
/// </summary>
void DoTradeCallClick()
{
	SRLGame::performTradeCall = true;
	deque<string> tags = Split(SYDEClickableButton::getLastButtonTag(), ';');
	//a_TradeBtn.setTag(to_string(i) + ";" + to_string(playerID) + ";" + to_string(playerID2) + ";" + offContract.getName());
	if (tags.size() > 3)
	{
		SRLGame::playerMainTeamTrade = stoi(tags[1]);
		SRLGame::playerOtherTeamTrade = stoi(tags[2]);
		string tName = tags[3];
		if (tName == "Off Contract Players")
		{
			SRLTeam newTeam;
			newTeam.loadTeamOffContract("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json");
			SRLGame::otherTeamTrade = newTeam;
		}
		else
		{
			SRLTeam newTeam;
			newTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + tName + ".json");
			SRLGame::otherTeamTrade = newTeam;
		}
	}
	else
	{
		SRLGame::errorCall = true;
		SRLGame::performTradeCall = false;
		SRLGame::errorMessage = "Error occured whilst trading";
	}
}

void DoTradeCallOKClick()
{
	SRLGame::performTradeCall = false;
	SRLGame::performTradeConfirmedCall = true;
}

void DoTradeCallCNCLClick()
{
	SRLGame::performTradeCall = false;
}

void SelectTeamCallBtnClick()
{
	SRLGame::selectedTeamCall = true;
}

void CoachingModeEnableClick()
{
	SRLGame::coachingMode = !SRLGame::coachingMode;
}

void RepRoundModeEnableClick()
{
	SRLGame::RepRoundsOn = !SRLGame::RepRoundsOn;
}

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

void PlayerProfileViewClick()
{
	SRLGame::newState = ProfileViewState;
}

void TeamAssetSwitchViewClick()
{
	SRLGame::TeamInDepthViewingJerseyAsset = !SRLGame::TeamInDepthViewingJerseyAsset;
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
		deque<string> bets = Split(SRLGame::customAmountStr, '.');
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
	SRLGame::errorMessage = "Confirm " + SRLGame::m_BetAmount.ReturnPrice() + " Bet On " + Split(SRLGame::betTag,'#')[0] + "?";
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

void TeamListViewStateChange()
{
	int statePos = static_cast<int>(SRLGame::tlViewState);
	statePos++;
	if (statePos > 5)
	{
		statePos = 0;
	}
	SRLGame::tlViewState = static_cast<SRLTeamListViewState>(statePos);
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
	deque<string> bets = Split(SRLGame::betTag, ';');
	if (bets.size() > 4)
	{
		SRLGame::betTag = bets[4];
		SRLGame::homeTeamBet = bets[3] == "H";
		SRLGame::premiershipBet = bets[3] == "P";
		SRLGame::homeTeamTryBet = bets[3] == "TH";
		SRLGame::gameNumberBet = stoi(bets[0]);
		SRLGame::keyPadCall = true;
	}
	else
	{
		SRLGame::errorCall = true;
		SRLGame::errorMessage = "Error Whilst Creating Bet";
	}
}

void BetMatchClick()
{
	SRLGame::betTag = SYDEClickableButton::getLastButtonTag();
	deque<string> bets = Split(SRLGame::betTag, ';');
	if (bets.size() > 4)
	{
		SRLGame::betTag = bets[4];
		SRLGame::m_BetAmount.dollars = stoi(bets[1]);
		SRLGame::m_BetAmount.cents = stoi(bets[2]);
		SRLGame::homeTeamBet = bets[3] == "H";
		SRLGame::premiershipBet = bets[3] == "P";
		SRLGame::homeTeamTryBet = bets[3] == "TH";
		SRLGame::gameNumberBet = stoi(bets[0]);
		SRLGame::betCall = true;

		SRLGame::errorMessage = "Confirm " + SRLGame::m_BetAmount.ReturnPrice() + " Bet On " + Split(SRLGame::betTag, '#')[0] + "?";
	}
	else
	{
		SRLGame::errorCall = true;
		SRLGame::errorMessage = "Error Whilst Creating Bet";
	}
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
	SRLGame::seasCfgState = SelectSeasonTypeState;
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
void CoachingViewClick()
{
	SRLGame::newState = CoachingViewState;
	if (SRLGame::coachDrawState == CoachingSwapPos_STATE)
	{
		SRLGame::coachDrawState = CoachingTeamList_STATE;
	}
}
void CurrentRoundViewClick()
{
	SRLGame::bettingState = CurrentRound_STATE;
}

void CoachMainViewClick()
{
	SRLGame::coachDrawState = CoachingMain_STATE;
}
void CoachTeamViewClick()
{
	SRLGame::coachDrawState = CoachingTeamList_STATE;
}
void CoachSwapPositionsViewClick()
{
	SRLGame::coachDrawState = CoachingSwapPos_STATE;
	SRLGame::posToSwap = "";
	SRLGame::setUpPosShowcaseCall = true;
	SRLGame::posSwapState = SRLPS_Backline;
}

void DoRegularSeasonCfg()
{
	SRLGame::seasCfgState = SelectSeasonTeamsState;
}
void DoWorldCupSeasonCfg()
{
	SRLGame::SeasonStartCall = true;
}

void DoExhibitionCfg()
{
	SRLGame::seasCfgState = SelectExhibitionTeamsState;
	SRLGame::setUpExhibitionDisplayCall = true;
}

void DoExhibitionSwap1Prev()
{
	SRLGame::exhibitionTeam1Num--;
	SRLGame::setUpExhibitionDisplayCall = true;
}
void DoExhibitionSwap1Next()
{
	SRLGame::exhibitionTeam1Num++;
	SRLGame::setUpExhibitionDisplayCall = true;
}
void DoExhibitionSwap2Prev()
{
	SRLGame::exhibitionTeam2Num--;
	SRLGame::setUpExhibitionDisplayCall = true;
}
void DoExhibitionSwap2Next()
{
	SRLGame::exhibitionTeam2Num++;
	SRLGame::setUpExhibitionDisplayCall = true;
}

void DoNextPosSwapStateView()
{
	SRLGame::setUpPosShowcaseCall = true;
	int statePos = static_cast<int>(SRLGame::posSwapState);
	statePos++;
	if (statePos > 2)
	{
		statePos = 0;
	}
	SRLGame::posSwapState = static_cast<SRLPositionShowcaseState>(statePos);
	
}

void DoPrevPosSwapStateView()
{
	SRLGame::setUpPosShowcaseCall = true;
	int statePos = static_cast<int>(SRLGame::posSwapState);
	statePos--;
	if (statePos < 0)
	{
		statePos = 2;
	}
	SRLGame::posSwapState = static_cast<SRLPositionShowcaseState>(statePos);
}

void CoachTradeViewClick()
{
	SRLGame::coachDrawState = CoachingTrades_STATE;
}

void CoachTrainViewClick()
{
	SRLGame::coachDrawState = CoachingTraining_STATE;
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

void SponsorButtonClick()
{
	SRLGame::newState = SponsorChallengeViewState;
	SRLGame::sponsorState = static_cast<SRLSponsorTypeState>(stoi(SYDEClickableButton::getLastButtonTag()));
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
	SRLGame::NextRoundCall = true;
}

void PrevRoundViewClick()
{
	SRLGame::PrevRoundCall = true;
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

void TryScorersViewBetClick()
{
	SRLGame::bettingState = TryScorers_STATE;
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

void TryScorerBetsViewClick()
{
	SRLGame::priorBetsState = TryScorerBets_State;
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

void SwapPositionsJerseyClick()
{
	if (SRLGame::posToSwap == "")
	{
		SRLGame::posToSwap = CustomAsset_Clickable::getLastButtonTag();
		SRLGame::posToSwap += ";";
	}
	else
	{
		SRLGame::posToSwap += CustomAsset_Clickable::getLastButtonTag();
		SRLGame::posSwapCall = true;
	}
}

#pragma endregion

/// <summary>
/// Initialize all the values for the game
/// </summary>
void SRLGame::init()
{
	CustomAnimationAsset::SetDeltatimeBasedAnimation(true);
	m_MainMenuBG.setMaxDeltatime(0.03f);
	m_MainMenuBG.setLooping(false);
	loadGameSettings();

	maxScrollTickTime = maxScrollTickTime / m_ScrollingSpeed;

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

#pragma region Coaching View
	m_SelectTeamBtn = SYDEClickableButton("Start Season", Vector2(48, 19), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_SelectTeamBtn.setHighLight(RED);
	m_SelectTeamBtn.SetFunc(SelectTeamCallBtnClick);

	m_CoachMainStateBtn = SYDEClickableButton("  Team Summary ", Vector2(0, 2), Vector2(15, 1), BRIGHTWHITE_RED_BG, false);
	m_CoachMainStateBtn.setHighLight(RED);
	m_CoachMainStateBtn.SetFunc(CoachMainViewClick);
	m_CoachTradeStateBtn = SYDEClickableButton("  Trade Offers ", Vector2(15, 2), Vector2(15, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_CoachTradeStateBtn.setHighLight(RED);
	m_CoachTradeStateBtn.SetFunc(CoachTradeViewClick);
	m_CoachTrainStateBtn = SYDEClickableButton(" Team Training ", Vector2(30, 2), Vector2(15, 1), BRIGHTWHITE_RED_BG, false);
	m_CoachTrainStateBtn.setHighLight(RED);
	m_CoachTrainStateBtn.SetFunc(CoachTrainViewClick);
	m_CoachTeamStateBtn = SYDEClickableButton(" View Team List", Vector2(45, 2), Vector2(15, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_CoachTeamStateBtn.setHighLight(RED);
	m_CoachTeamStateBtn.SetFunc(CoachTeamViewClick);

	m_CoachTeamCycleStatsViewBtn = SYDEClickableButton("Cycle Stat View", Vector2(0, 18), Vector2(15, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_CoachTeamCycleStatsViewBtn.setHighLight(RED);
	m_CoachTeamCycleStatsViewBtn.SetFunc(TeamListViewStateChange);

	m_CoachTeamSwapPositionsBtn = SYDEClickableButton(" Swap Positions ", Vector2(44, 18), Vector2(15, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_CoachTeamSwapPositionsBtn.setHighLight(RED);
	m_CoachTeamSwapPositionsBtn.SetFunc(CoachSwapPositionsViewClick);

	m_CoachTrainRefreshBtn = SYDEClickableButton("Refresh Options", Vector2(43, 17), Vector2(15, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_CoachTrainRefreshBtn.setHighLight(RED);
	m_CoachTrainRefreshBtn.SetFunc(DoPerformRefreshClick);

	m_CoachTradeConfirmOKBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_CoachTradeConfirmOKBtn.setHighLight(RED);
	m_CoachTradeConfirmOKBtn.SetFunc(DoTradeCallOKClick);

	m_CoachTradeConfirmCNCLBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_CoachTradeConfirmCNCLBtn.setHighLight(RED);
	m_CoachTradeConfirmCNCLBtn.SetFunc(DoTradeCallCNCLClick);

	m_CoachTrainConfirmOKBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_CoachTrainConfirmOKBtn.setHighLight(RED);
	m_CoachTrainConfirmOKBtn.SetFunc(DoTrainCallOKClick);
	m_CoachTrainConfirmCNCLBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_CoachTrainConfirmCNCLBtn.setHighLight(RED);
	m_CoachTrainConfirmCNCLBtn.SetFunc(DoTrainCallCNCLClick);

	m_CoachPosSwapPrev = SYDEClickableButton("<<", Vector2(0, 10), Vector2(2, 1), BLACK_RED_BG, false);
	m_CoachPosSwapPrev.setHighLight(RED);
	m_CoachPosSwapPrev.SetFunc(DoPrevPosSwapStateView);
	m_CoachPosSwapNext = SYDEClickableButton(">>", Vector2(58, 10), Vector2(2, 1), BLACK_RED_BG, false);
	m_CoachPosSwapNext.setHighLight(RED);
	m_CoachPosSwapNext.SetFunc(DoNextPosSwapStateView);
#pragma endregion

#pragma region SeasonOptions

	m_RegularSeasonCfgBtn = SYDEClickableButton("Regular Season", Vector2(5, 4), Vector2(50, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_RegularSeasonCfgBtn.setHighLight(RED);
	m_RegularSeasonCfgBtn.SetFunc(DoRegularSeasonCfg);
	m_WorldCupCfgBtn = SYDEClickableButton("World Cup Tournament", Vector2(5, 9), Vector2(50, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_WorldCupCfgBtn.setHighLight(RED);
	m_WorldCupCfgBtn.SetFunc(DoWorldCupSeasonCfg);
	m_ExhibitionCfgBtn = SYDEClickableButton("Exhibition Match", Vector2(5, 14), Vector2(50, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_ExhibitionCfgBtn.setHighLight(RED);
	m_ExhibitionCfgBtn.SetFunc(DoExhibitionCfg);

	m_ExhibitionSwap1Prev = SYDEClickableButton("<<", Vector2(2, 14), Vector2(2, 1),BLACK_RED_BG, false);
	m_ExhibitionSwap1Prev.setHighLight(RED);
	m_ExhibitionSwap1Prev.SetFunc(DoExhibitionSwap1Prev);
	m_ExhibitionSwap1Next = SYDEClickableButton(">>", Vector2(26, 14), Vector2(2, 1), BLACK_RED_BG, false);
	m_ExhibitionSwap1Next.setHighLight(RED);
	m_ExhibitionSwap1Next.SetFunc(DoExhibitionSwap1Next);
	m_ExhibitionSwap2Prev = SYDEClickableButton("<<", Vector2(32, 14), Vector2(2, 1), BLACK_RED_BG, false);
	m_ExhibitionSwap2Prev.setHighLight(RED);
	m_ExhibitionSwap2Prev.SetFunc(DoExhibitionSwap2Prev);
	m_ExhibitionSwap2Next = SYDEClickableButton(">>", Vector2(56, 14), Vector2(2, 1), BLACK_RED_BG, false);
	m_ExhibitionSwap2Next.setHighLight(RED);
	m_ExhibitionSwap2Next.SetFunc(DoExhibitionSwap2Next);

	m_SeasonViewBtn = SYDEClickableButton("   Season   ", Vector2(0, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SeasonViewBtn.setHighLight(RED);
	m_SeasonViewBtn.SetFunc(SeasonViewClick);
	m_LadderViewBtn = SYDEClickableButton("   Ladder   ", Vector2(12, 1), Vector2(12, 1), BLACK_WHITE_BG, false);
	m_LadderViewBtn.setHighLight(RED);
	m_LadderViewBtn.SetFunc(LadderViewClick);
	m_BettingViewBtn = SYDEClickableButton("   Betting   ", Vector2(24, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BettingViewBtn.setHighLight(RED);
	m_BettingViewBtn.SetFunc(BettingViewClick);
	m_CoachingViewBtn = SYDEClickableButton("  Coaching   ", Vector2(24, 1), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_CoachingViewBtn.setHighLight(RED);
	m_CoachingViewBtn.SetFunc(CoachingViewClick);
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
	m_BetBtnCurrentRound = SYDEClickableButton(" This Round ", Vector2(0, 2), Vector2(12, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnCurrentRound.setHighLight(RED);
	m_BetBtnCurrentRound.SetFunc(CurrentRoundViewClick);
	m_BetBtnFutures = SYDEClickableButton("  Futures  ", Vector2(12, 2), Vector2(12, 1), BRIGHTWHITE_BRIGHTGREEN_BG, false);
	m_BetBtnFutures.setHighLight(RED);
	m_BetBtnFutures.SetFunc(FuturesViewClick);
	m_BetTryscorers = SYDEClickableButton(" Try Scorers", Vector2(24, 2), Vector2(12, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetTryscorers.setHighLight(RED);
	m_BetTryscorers.SetFunc(TryScorersViewBetClick);
	m_BetBtnViewBets = SYDEClickableButton(" Bet History", Vector2(36, 2), Vector2(12, 1), BRIGHTWHITE_BRIGHTGREEN_BG, false);
	m_BetBtnViewBets.setHighLight(RED);
	m_BetBtnViewBets.SetFunc(PastBetViewClick);
	m_BetBtnAccount = SYDEClickableButton(" My Account ", Vector2(48, 2), Vector2(12, 1), BRIGHTWHITE_GREEN_BG, false);
	m_BetBtnAccount.setHighLight(RED);
	m_BetBtnAccount.SetFunc(AccountViewClick);

	m_BetOkViewBtn = SYDEClickableButton(" OK ", Vector2(44, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BetOkViewBtn.setHighLight(RED);
	m_BetOkViewBtn.SetFunc(betOKClick);

	m_BetCnclViewBtn = SYDEClickableButton("CNCL", Vector2(12, 12), Vector2(4, 1), BLACK_BRIGHTWHITE_BG, false);
	m_BetCnclViewBtn.setHighLight(RED);
	m_BetCnclViewBtn.SetFunc(betCNCLClick);

	m_PriorBetsGameBtn = SYDEClickableButton("  Match Bet Results ", Vector2(0, 3), Vector2(20, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_PriorBetsGameBtn.setHighLight(RED);
	m_PriorBetsGameBtn.SetFunc(GameResultsViewClick);

	m_PriorBetsPremiershipBtn = SYDEClickableButton("Premiership Results ", Vector2(20, 3), Vector2(20, 1), BRIGHTWHITE_RED_BG, false);
	m_PriorBetsPremiershipBtn.setHighLight(RED);
	m_PriorBetsPremiershipBtn.SetFunc(PremiershipResultsViewClick);

	m_PriorBetsTryScorerBtn = SYDEClickableButton(" Try Scorer Betting ", Vector2(40, 3), Vector2(20, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_PriorBetsTryScorerBtn.setHighLight(RED);
	m_PriorBetsTryScorerBtn.SetFunc(TryScorerBetsViewClick);
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

	m_TeamAssetSwitchView = SYDEClickableButton(" Switch Logo View ", Vector2(2, 18), Vector2(18, 1), BRIGHTWHITE_BRIGHTRED_BG, false);
	m_TeamAssetSwitchView.setHighLight(RED);
	m_TeamAssetSwitchView.SetFunc(TeamAssetSwitchViewClick);

	m_ProfileViewBtn = SYDEClickableButton("    Your Profile    ", Vector2(20, 19), Vector2(20, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ProfileViewBtn.setHighLight(RED);
	m_ProfileViewBtn.SetFunc(PlayerProfileViewClick);

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

	m_SettingsCoachBtn = SYDEClickableButton(" Coaching Mode:", Vector2(36, 6), Vector2(15, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsCoachBtn.setHighLight(RED);
	m_SettingsCoachBtn.SetFunc(CoachingModeEnableClick);

	m_SettingsRepRoundsBtn = SYDEClickableButton(" Rep Rounds:", Vector2(39, 8), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SettingsRepRoundsBtn.setHighLight(RED);
	m_SettingsRepRoundsBtn.SetFunc(RepRoundModeEnableClick);

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

#pragma region SoundTrack

	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\01MeetMeOneDay.mp3", "Meet Me One Day", "Rit@lin4Kidz", "", 168);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\02IThink.mp3", "I Think, Therefore I Suck", "Handsprime", "(Rit@lin4Kidz Remix)", 96);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\03Waterfall.mp3", "Waterfall", "Handsprime", "(Rit@lin4Kidz Remix)", 136);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\04LetMeShowYouARemix.mp3", "Let Me Show You A Remix", "Rit@lin4Kidz", "", 89);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\05Depression.mp3", "Depression", "Handsprime", "", 140);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\06Icebreaker.mp3", "Icebreaker", "Handsprime", "", 181);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\07MichaelsoftBinbows.mp3", "Michaelsoft Binbows", "Handsprime", "", 137);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\08Trapstar.mp3", "Trapstar", "Handsprime", "", 183);
	m_GamePlaySoundtrack.addSong("EngineFiles\\Soundtrack\\09Xnopyt.mp3", "Xnopyt", "Handsprime", "", 140);
	m_GamePlaySoundtrack.setYPos(14);
	m_GamePlaySoundtrack.setOn(soundTrackOn);
	if (soundTrackOn)
	{
		m_GamePlaySoundtrack.start();
	}
	m_GamePlaySoundtrack.shuffleSongs(true, false);

#pragma endregion

}

#pragma region Misc
/// <summary>
/// Create a random team fill with 20 random players
/// </summary>
/// <param name="prefix">Name prefix, leave as "" if none</param>
/// <returns></returns>
deque<SRLPlayer> SRLGame::createRandomTeam(string prefix)
{
	deque<SRLPlayer> m_Team = deque<SRLPlayer>();
	for (int i = 0; i < 20; i++)
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
/// <summary>
/// Create off contract players
/// </summary>
/// <param name="prefix"></param>
/// <returns></returns>
deque<SRLPlayer> SRLGame::createOffSeasonTeam(string prefix)
{
	deque<SRLPlayer> m_Team = deque<SRLPlayer>();
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

deque<SRLPlayer> SRLGame::createRandomTeam(string prefix, float multiplier)
{
	deque<SRLPlayer> m_Team = deque<SRLPlayer>();
	for (int i = 0; i < 20; i++)
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
#pragma region pop-ups
	if (performTradeCall)
	{
		return TradingPop_UP(window, windowWidth, windowHeight);
	}
	if (performTrainCall)
	{
		return TrainingPop_UP(window, windowWidth, windowHeight);
	}
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
#pragma endregion
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
			m_MainMenuBG.setFrame(0);
			AssignState(std::bind(&SRLGame::main_menu_scene, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == ProfileViewState)
		{
			AssignState(std::bind(&SRLGame::ProfileView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == Exhibition_LoadState)
		{
			AssignState(std::bind(&SRLGame::exhibition_match_settings, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == SponsorChallengeViewState)
		{
			AssignState(std::bind(&SRLGame::ChallengesView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
		else if (currentState == SelectTeamCoachingState)
		{
			setUpSelectedTeamView();
			AssignState(std::bind(&SRLGame::SelectTeamCoachingView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == CoachingViewState)
		{
			AssignState(std::bind(&SRLGame::CoachingView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (currentState == BettingViewState)
		{
			m_SelectedGame = 0;
			if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
			{
				CalculateTryScorerOdds();
			}
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
			m_SeasonTeams = deque<string>();
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
	window = m_ProfileViewBtn.draw_ui(window);
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
	if (seasCfgState == SelectSeasonTypeState)
	{
		window = m_RegularSeasonCfgBtn.draw_ui(window);
		window = m_WorldCupCfgBtn.draw_ui(window);
		window = m_ExhibitionCfgBtn.draw_ui(window);
		if (SeasonStart)
		{
			//return CreateSeason(window);
			return CreateSeason(window, true);
		}
	}
	else if (seasCfgState == SelectExhibitionTeamsState)
	{
		if (setUpExhibitionDisplayCall)
		{
			if (exhibitionTeam1Num < 0)
			{
				exhibitionTeam1Num = m_SavedTeams.size() - 1;
			}
			if (exhibitionTeam1Num > m_SavedTeams.size() - 1)
			{
				exhibitionTeam1Num = 0;
			}
			if (exhibitionTeam2Num < 0)
			{
				exhibitionTeam2Num = m_SavedTeams.size() - 1;
			}
			if (exhibitionTeam2Num > m_SavedTeams.size() - 1)
			{
				exhibitionTeam2Num = 0;
			}
			m_ExhibitionGameFeature = FeaturedGame(m_SavedTeams[exhibitionTeam1Num], m_SavedTeams[exhibitionTeam2Num], astVars, 0, SRLBetPrice(0, 0), SRLBetPrice(0, 0));
			m_ExhibitionGameFeature.fg_homeTeam.CalculateAverages();
			m_ExhibitionGameFeature.fg_awayTeam.CalculateAverages();
			setUpExhibitionDisplayCall = false;
		}
		string awayTeamText = m_ExhibitionGameFeature.fg_awayTeam.getName();
		if (m_ExhibitionGameFeature.featuredGameAvail)
		{
			int sizeText = awayTeamText.length();

			window = m_ExhibitionGameFeature.fg_homeTeamJersey.draw_asset(window, Vector2(0, 3));
			window = m_ExhibitionGameFeature.fg_awayTeamJersey.draw_asset(window, Vector2(30, 3));

			window = m_ExhibitionSwap1Prev.draw_ui(window);
			window = m_ExhibitionSwap1Next.draw_ui(window);
			window = m_ExhibitionSwap2Prev.draw_ui(window);
			window = m_ExhibitionSwap2Next.draw_ui(window);

			window.setTextAtPoint(Vector2(14, 18), to_string(m_ExhibitionGameFeature.fg_homeTeam.TeamRating()), WHITE);
			window.setTextAtPoint(Vector2(46, 18), to_string(m_ExhibitionGameFeature.fg_awayTeam.TeamRating()), WHITE);

			window.setTextAtPoint(Vector2(0, 3), m_ExhibitionGameFeature.fg_homeTeam.getName(), WHITE);
			window.setTextAtPoint(Vector2(60 - sizeText, 3), awayTeamText, WHITE);
		}
	}
	else if (seasCfgState == SelectSeasonTeamsState)
	{
		window = configTabs(window);
		if (SeasonStart)
		{
			return CreateSeason(window, false);
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
					if (SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") > 50)
					{
						m_GameProfile.completeChallenge("Have Over 50 Teams Existing", AchievementStrings);
					}
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
				m_SavedTeams.push_back(m_SeasonTeams[m_SeasonTeams.size() - 1]);
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
		window.setTextAtPoint(Vector2(0, 2), m_Season.m_Draw.m_Rounds[m_round].RoundName, WHITE);
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_round].m_Games.size(); i++)
		{
			window.setTextAtPoint(Vector2(0, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].HomeTeam, WHITE);
			window.setTextAtPoint(Vector2(26, 3 + i), std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].homeTeamScore) + " v " + std::to_string(m_Season.m_Draw.m_Rounds[m_round].m_Games[i].awayTeamScore), WHITE);
			window.setTextAtPoint(Vector2(34, 3 + i), m_Season.m_Draw.m_Rounds[m_round].m_Games[i].AwayTeam, WHITE);
		}
		try
		{
			SimulateGames();
		}
		catch (exception e)
		{
			errorCall = true;
			errorMessage = e.what();
		}
	}
	else if (drawViewState == FeaturedMatchView)
	{
		//SANITY
		SimulateCall = false;
		window.setTextAtPoint(Vector2(0, 2), m_Season.m_Draw.m_Rounds[m_round].RoundName, WHITE);
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
		window.setTextAtPoint(Vector2(0, 2), m_Season.m_Draw.m_Rounds[m_round].RoundName, WHITE);
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
				m_Season.m_PremiershipBets.push_back(SRLGameBet(betTag, m_Season.m_Ladder.m_Ladder[gameNumberBet].premiershipOdds, m_BetAmount, BetType_Premiership));
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
	else if (bettingState == TryScorers_STATE)
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
				if (homeTeamTryBet)
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.push_back(SRLGameBet(betTag, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].homeTeamTryOdds[gameNumberBet], m_BetAmount, BetType_Try));
				}
				else
				{
					m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.push_back(SRLGameBet(betTag, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].awayTeamTryOdds[gameNumberBet], m_BetAmount, BetType_Try));
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
		if (m_roundToSimulate >= BaseSeasonGames + finalsRounds)
		{
			window.setTextAtPoint(Vector2(2, 3), "TRY SCORER BETS SUSPENDED", BRIGHTWHITE);
		}
		else
		{
			if (NextRoundCall)
			{
				NextRoundCall = false;
				m_SelectedGame++;
				if (m_SelectedGame >= m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size())
				{
					m_SelectedGame = 0;
				}
				CalculateTryScorerOdds();
			}
			if (PrevRoundCall)
			{
				PrevRoundCall = false;
				m_SelectedGame--;
				if (m_SelectedGame < 0)
				{
					m_SelectedGame = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size() - 1;
				}
				CalculateTryScorerOdds();
			}

			window.setTextAtPoint(Vector2(0, 3), m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].HomeTeam, BRIGHTGREEN);
			for (int i = 0; i < AttackersHome.size(); i++)
			{
				window.setTextAtPoint(Vector2(0, 4 + i), AttackersHome[i] + " (" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].homeTeamTryOdds[i].ReturnPrice() + ")", BRIGHTWHITE);
			}
			window.setTextAtPoint(Vector2(0, 11), m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].AwayTeam, BRIGHTGREEN);
			for (int i = 0; i < AttackersAway.size(); i++)
			{
				window.setTextAtPoint(Vector2(0, 12 + i), AttackersAway[i] + " (" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].awayTeamTryOdds[i].ReturnPrice() + ")", BRIGHTWHITE);
			}

			for (int i = 0; i < m_TryScorerBetButtons.size(); i++)
			{
				window = m_TryScorerBetButtons[i].draw_ui(window);
			}
		}
	}
	else if (bettingState == ViewBets_STATE)
	{
		window = m_PriorBetsGameBtn.draw_ui(window);
		window = m_PriorBetsPremiershipBtn.draw_ui(window);
		window = m_PriorBetsTryScorerBtn.draw_ui(window);
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
		else if(priorBetsState == TryScorerBets_State)
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
				if (priorBetNumberLine < m_TryScorerBetsWriteUp.size() - 1)
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
					if (priorBetNumberLine < m_TryScorerBetsWriteUp.size() - 1)
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

			for (int i = 0; i + priorBetNumberLine < m_TryScorerBetsWriteUp.size() && i < 14; i++)
			{
				window.setTextAtPoint(Vector2(1, 4 + i), m_TryScorerBetsWriteUp[i + priorBetNumberLine].name, m_TryScorerBetsWriteUp[i + priorBetNumberLine].colour);
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

ConsoleWindow SRLGame::SelectTeamCoachingView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 1), "SELECT TEAM TO COACH", BLACK_BRIGHTWHITE_BG);
	for (int ii = 0; ii < 60; ii++)
	{
		window.setTextAtPoint(Vector2(ii, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	if (SYDEKeyCode::get_key(VK_RIGHT)._CompareState(KEYDOWN))
	{
		NextRoundCall = true;
	}
	else if (SYDEKeyCode::get_key(VK_LEFT)._CompareState(KEYDOWN))
	{
		PrevRoundCall = true;
	}
	if (NextRoundCall)
	{
		NextRoundCall = false;
		teamSelected++;
		if (teamSelected >= m_SeasonTeams.size())
		{
			teamSelected = 0;
		}
		setUpSelectedTeamView();
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
		teamSelected--;
		if (teamSelected < 0)
		{
			teamSelected = m_SeasonTeams.size() - 1;
		}
		setUpSelectedTeamView();
	}
	if (selectedTeamCall)
	{
		selectedTeamCall = false;
		sortOutTrainingOptions();
		sortOutTradingOptions();
		startingRating = teamSelectedRating;
		newState = SeasonModeState;
		m_BetMoney = SRLBetPrice(1500, 0);
		int featureGameNumber = 0;
		if (coachingMode)
		{
			for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
			{
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam == teamCoached || m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam == teamCoached)
				{
					featureGameNumber = i;
				}
			}
		}
		m_Season.m_Draw.m_Rounds[0].gameToFeature = FeaturedGame(m_Season.m_Draw.m_Rounds[0].m_Games[featureGameNumber].HomeTeam, m_Season.m_Draw.m_Rounds[0].m_Games[featureGameNumber].AwayTeam, astVars, featureGameNumber, m_Season.m_Draw.m_Rounds[0].m_Games[featureGameNumber].homeTeamOdds, m_Season.m_Draw.m_Rounds[0].m_Games[featureGameNumber].awayTeamOdds);
		return window;
	}
	window.setTextAtPoint(Vector2(0, 2), teamCoached, BRIGHTWHITE);
	window = m_SelectedTeamJerseyView.draw_asset(window, Vector2(15, 3));
	window.setTextAtPoint(Vector2(29, 18), to_string(teamSelectedRating), BRIGHTWHITE);
	window = m_SelectTeamBtn.draw_ui(window);
	window = m_NextTeamSeasonCfgBtn.draw_ui(window);
	window = m_PrevTeamSeasonCfgBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::CoachingView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (coachDrawState == CoachingMain_STATE)
	{
		window.setTextAtPoint(Vector2(0, 3), teamCoached, BRIGHTWHITE);
		window = m_SelectedTeamJerseyView.draw_asset(window, Vector2(0, 4));

		m_CoachedTeam.CalculateAverages();
		window.setTextAtPoint(Vector2(30, 4), "Remaining Budget: " + m_BetMoney.ReturnPrice(), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(30, 6), "Attack: " + to_string(m_CoachedTeam.averageAttackStat()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(30, 7), "Defence: " + to_string(m_CoachedTeam.averageDefenceStat()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(30, 8), "Speed: " + to_string(m_CoachedTeam.averageSpeedStat()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(30, 9), "Kicking: " + to_string(m_CoachedTeam.averageKickStat()), BRIGHTWHITE);
		window.setTextAtPoint(Vector2(30, 10), "Handling: " + to_string(m_CoachedTeam.averageHandlingStat()), BRIGHTWHITE);
									  
		window.setTextAtPoint(Vector2(30, 12), "Rating: " + to_string(m_CoachedTeam.TeamRating()), BRIGHTWHITE);
	}
	else if (coachDrawState == CoachingTraining_STATE)
	{
		if (performRefreshOptionsCall)
		{
			performRefreshOptionsCall = false;
			if (refreshAvailable > 0)
			{
				sortOutTrainingOptions();
				refreshAvailable--;
			}
			else
			{
				errorCall = true;
				errorMessage = "No More Refreshes Left";
			}
			return window;
		}
		else if (performTrainConfirmedCall)
		{
			performTrainConfirmedCall = false;
			//SRLGame::playerMainTeamTrade = stoi(training[1]);
			//SRLGame::m_BetAmount.dollars = stoi(training[2]);
			//SRLGame::m_BetAmount.cents = stoi(training[3]);
			//SRLGame::trainType = static_cast<SRLTrainingType>(stoi(training[4]));
			if (m_BetMoney.greaterThan(m_BetAmount) || m_BetMoney.equal(m_BetAmount))
			{
				m_BetMoney.removeBetPrice(m_BetAmount);
				int statBoost = m_BetAmount.dollars / 10;
				switch (trainType)
				{
				case Training_Attack:
					m_CoachedTeam.addPlayerAtk(m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), statBoost);
					break;
				case Training_Defence:
					m_CoachedTeam.addPlayerDef(m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), statBoost);
					break;
				case Training_Speed:
					m_CoachedTeam.addPlayerSpd(m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), statBoost);
					break;
				case Training_Handling:
					m_CoachedTeam.addPlayerHdl(m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), statBoost);
					break;
				case Training_Kick:
					m_CoachedTeam.addPlayerKck(m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), statBoost);
					break;
				}
				m_CoachedTeam.saveTeam();
				if (tradingAvailable)
				{
					sortOutTradingOptions();
				}
				m_CoachedTeam.CalculateAverages();
				if (m_CoachedTeam.averageSpeedStat() == 99)
				{
					m_GameProfile.completeChallenge("Train A Team To A 99 Speed Stat", AchievementStrings);
				}
				trainingAvailable = false;
				if (m_CoachedTeam.getPlayers()[playerMainTeamTrade].getRating() >= 99)
				{
					AchievementStrings.push_back("SRL_MAX_TRAINING");
					m_GameProfile.completeChallenge("Max Out A Player's Stats", AchievementStrings);
					if (m_CoachedTeam.TeamRating() == 99)
					{
						AchievementStrings.push_back("SRL_SALARY_CAP");
					}
				}
			}
			else
			{
				errorCall = true;
				errorMessage = "Not Enough Money To Train";
				return window;
			}
			return window;
		}
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds && trainingAvailable)
		{
			window = _trainingOptions[0].draw(window, (Vector2(5, 5)));
			window = _trainingOptions[1].draw(window, (Vector2(5, 9)));
			window = _trainingOptions[2].draw(window, (Vector2(5, 13)));
			for (int i = 0; i < m_TrainingButtons.size(); i++)
			{
				window = m_TrainingButtons[i].draw_ui(window);
			}
			window.setTextAtPoint(Vector2(45, 16), "Refreshes: " + to_string(refreshAvailable), BRIGHTWHITE);
			window = m_CoachTrainRefreshBtn.draw_ui(window);
		}

		else
		{
			window.setTextAtPoint(Vector2(0, 3), "NO TRAINING AVAILABLE AT CURRENT MOMENT", BRIGHTWHITE);
		}
	}
	else if (coachDrawState == CoachingTrades_STATE)
	{
		if (performRefreshOptionsCall)
		{
			performRefreshOptionsCall = false;
			if (refreshAvailable > 0)
			{
				sortOutTradingOptions();
				refreshAvailable--;
			}
			else
			{
				errorCall = true;
				errorMessage = "No More Refreshes Left";
			}
			return window;
		}
		else if (performTradeConfirmedCall)
		{
			performTradeConfirmedCall = false;
			SRLPlayer Player1Character = m_CoachedTeam.getPlayers()[playerMainTeamTrade];
			SRLPlayer Player2Character = otherTeamTrade.getPlayers()[playerOtherTeamTrade];
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				//DO NOT ALLOW TRADE IF MAIN TEAM HAS A PLAYER WITH THE SAME NAME, THIS WILL CAUSE CONFUSION WITH LEADERBOARD
				if (m_CoachedTeam.getPlayers()[i].getName() == Player2Character.getName())
				{
					errorCall = true;
					errorMessage = "Could Not Perform Trade With Players";
					return window;
				}
				else if (otherTeamTrade.getPlayers()[i].getName() == Player1Character.getName())
				{
					errorCall = true;
					errorMessage = "Could Not Perform Trade With Players";
					return window;
				}
			}
			m_CoachedTeam.setPlayer(playerMainTeamTrade, Player2Character);
			otherTeamTrade.setPlayer(playerOtherTeamTrade, Player1Character);
			if (otherTeamTrade.getName() == "Off Contract Players")
			{
				SRLNewsArticle m_SigningArticle;
				m_SigningArticle.headline = m_CoachedTeam.getName() + " Sign " + Player2Character.getName();
				m_SigningArticle.newsStory = SRLNewsStoryGenerator::generateOffContractTradeArticle(m_CoachedTeam.getName(), Player2Character.getName(), Player1Character.getName());
				m_SigningArticle.type = SRLAT_PlayerSign;
				m_SigningArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].newsStories.push_back(m_SigningArticle);
			}
			else
			{
				SRLNewsArticle m_SigningArticle;
				m_SigningArticle.headline = m_CoachedTeam.getName() + " Sign " + Player2Character.getName();
				m_SigningArticle.newsStory = SRLNewsStoryGenerator::generateTradeArticle(m_CoachedTeam.getName(), otherTeamTrade.getName(), Player1Character.getName(), Player2Character.getName());
				m_SigningArticle.type = SRLAT_PlayerTrade;
				m_SigningArticle.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
				m_Season.m_Draw.m_Rounds[m_roundToSimulate].newsStories.push_back(m_SigningArticle);
			}

			m_Season.m_TopPlayers.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopTries.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopGoals.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopPoints.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopMetres.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopFieldGoals.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_Top4020.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopTackles.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopKickMetres.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopErrors.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopPenalty.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopSteals.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopNoTries.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopRuckErrors.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopSinBin.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopSendOff.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());
			m_Season.m_TopInjuries.changePlayerTeam(Player1Character.getName(), m_CoachedTeam.getName(), otherTeamTrade.getName());

			m_Season.m_TopPlayers.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopTries.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopGoals.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopPoints.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopMetres.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopFieldGoals.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_Top4020.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopTackles.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopKickMetres.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopErrors.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopPenalty.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopSteals.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopNoTries.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopRuckErrors.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopSinBin.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopSendOff.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());
			m_Season.m_TopInjuries.changePlayerTeam(Player2Character.getName(), otherTeamTrade.getName(), m_CoachedTeam.getName());

			m_CoachedTeam.saveTeam();
			if (otherTeamTrade.getName() == "Off Contract Players")
			{
				otherTeamTrade.saveTeamOffContract();
			}
			else
			{
				otherTeamTrade.saveTeam();
			}
			if (trainingAvailable)
			{
				sortOutTrainingOptions();
			}
			tradingAvailable = false;
		}
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds && tradingAvailable)
		{
			window = _tradingOptions[0].draw(window, (Vector2(5, 5)));
			window = _tradingOptions[1].draw(window, (Vector2(5, 9)));
			window = _tradingOptions[2].draw(window, (Vector2(5, 13)));
			for (int i = 0; i < m_TradingButtons.size(); i++)
			{
				window = m_TradingButtons[i].draw_ui(window);
			}
			window.setTextAtPoint(Vector2(45, 16), "Refreshes: " + to_string(refreshAvailable), BRIGHTWHITE);
			window = m_CoachTrainRefreshBtn.draw_ui(window);
		}
		else
		{
			window.setTextAtPoint(Vector2(0, 3), "NO TRADING AVAILABLE AT CURRENT POINT", BRIGHTWHITE);
		}
	}
	else if (coachDrawState == CoachingTeamList_STATE)
	{
		if (tlViewState == TLV_GeneralStats)
		{
			window.setTextAtPoint(Vector2(0, 3), "GENERAL RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getRating()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getRating()) + ")", BRIGHTWHITE);
				}
			}
		}
		else if (tlViewState == TLV_Attack)
		{
			window.setTextAtPoint(Vector2(0, 3), "ATTACK RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getAttack()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getAttack()) + ")", BRIGHTWHITE);
				}
			}
		}
		else if (tlViewState == TLV_Defence)
		{
			window.setTextAtPoint(Vector2(0, 3), "DEFENCE RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getDefence()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getDefence()) + ")", BRIGHTWHITE);
				}
			}
		}
		else if (tlViewState == TLV_Speed)
		{
			window.setTextAtPoint(Vector2(0, 3), "SPEED RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getSpeed()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getSpeed()) + ")", BRIGHTWHITE);
				}
			}
		}
		else if (tlViewState == TLV_Kicking)
		{
			window.setTextAtPoint(Vector2(0, 3), "KICKING RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getKicking()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getKicking()) + ")", BRIGHTWHITE);
				}
			}
		}
		else if (tlViewState == TLV_Handling)
		{
			window.setTextAtPoint(Vector2(0, 3), "HANDLING RATINGS:", BRIGHTWHITE);
			for (int i = 0; i < m_CoachedTeam.getPlayers().size(); i++)
			{
				if (i < 10)
				{
					window.setTextAtPoint(Vector2(0, i + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getHandling()) + ")", BRIGHTWHITE);
				}
				else
				{
					window.setTextAtPoint(Vector2(30, (i - 10) + 4), to_string(i + 1) + ". " + m_CoachedTeam.getPlayers()[i].getName() + " (" + to_string(m_CoachedTeam.getPlayers()[i].getHandling()) + ")", BRIGHTWHITE);
				}
			}
		}
		window = m_CoachTeamCycleStatsViewBtn.draw_ui(window);
		window = m_CoachTeamSwapPositionsBtn.draw_ui(window);
	}
	else if (coachDrawState == CoachingSwapPos_STATE)
	{
		if (posSwapCall)
		{
			posSwapCall = false;
			setUpPosShowcaseCall = true;
			deque<string> PositionsToSwap = Split(posToSwap, ';');
			m_CoachedTeam.swapStartPositionsAndSave(stoi(PositionsToSwap[0]) - 1, stoi(PositionsToSwap[1]) - 1);

			//IF WE SWAPPED A POSITION THAT EXISTS HERE
			for (int i = 0; i < m_TrainingButtons.size(); i++)
			{
				deque<string> tags = Split(m_TrainingButtons[i].getTag(), ';');
				int playerID = stoi(tags[1]);
				if (playerID == stoi(PositionsToSwap[0]) - 1)
				{
					tags[1] = to_string(stoi(PositionsToSwap[1]) - 1);
					m_TrainingButtons[i].setTag(tags[0] + ";" + tags[1] + ";" + tags[2] + ";" + tags[3] + ";" + tags[4]);
				}
				if (playerID == stoi(PositionsToSwap[1]) - 1)
				{
					tags[1] = to_string(stoi(PositionsToSwap[0]) - 1);
					m_TrainingButtons[i].setTag(tags[0] + ";" + tags[1] + ";" + tags[2] + ";" + tags[3] + ";" + tags[4]);
				}
			}
			//OR IF WE SWAPPED A POSITION THAT EXISTS HERE
			for (int i = 0; i < m_TradingButtons.size(); i++)
			{
				deque<string> tags = Split(m_TradingButtons[i].getTag(), ';');
				int playerID = stoi(tags[1]);
				if (playerID == stoi(PositionsToSwap[0]) - 1)
				{
					tags[1] = to_string(stoi(PositionsToSwap[1]) - 1);
					m_TradingButtons[i].setTag(tags[0] + ";" + tags[1] + ";" + tags[2] + ";" + tags[3]);
				}
				if (playerID == stoi(PositionsToSwap[1]) - 1)
				{
					tags[1] = to_string(stoi(PositionsToSwap[0]) - 1);
					m_TradingButtons[i].setTag(tags[0] + ";" + tags[1] + ";" + tags[2] + ";" + tags[3]);
				}
			}
			posToSwap = "";
			for (int i = 0; i < _PositionsShowcase.size(); i++)
			{
				_PositionsShowcase[i].m_MiniJersery.clearHighlight();
			}
		}		
		if (setUpPosShowcaseCall)
		{
			setUpPositionShowcase(posSwapState);
		}
		window = m_FieldBg.draw_asset(window, Vector2(0));
		for (int i = 0; i < _PositionsShowcase.size(); i++)
		{
			window = _PositionsShowcase[i].draw_showcase(window);
		}
		if (posSwapState == SRLPS_Backline)
		{
			window.setTextAtPoint(Vector2(2, 3), "Backline:", BLACK_BRIGHTGREEN_BG);
		}
		else if (posSwapState == SRLPS_Frontline)
		{
			window.setTextAtPoint(Vector2(2, 3), "Frontline:", BLACK_BRIGHTGREEN_BG);
		}
		else if (posSwapState == SRLPS_Interchange)
		{
			window.setTextAtPoint(Vector2(2, 3), "Interchange:", BLACK_BRIGHTGREEN_BG);
		}
		window = m_CoachPosSwapPrev.draw_ui(window);
		window = m_CoachPosSwapNext.draw_ui(window);
	}
	window = drawTabs(window);
	window = drawCoachingTabs(window);
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
		for (int i = 0; i < (m_SummaryScreenVector.size()); i++)
		{
			window = m_SummaryScreenVector[i].draw(window, Vector2(5, (((i * 5) + 5)) - m_LineResults));
		}
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, 3), " ", BLACK_BRIGHTWHITE_BG);
		}
	}
	window = drawTabs(window);
	window = drawResultTabs(window);
	if (m_ResultsTabCall)
	{
		m_ResultsTabCall = false;
		m_LineResults = 0;
	}
	if (resultState == Summary_STATE)
	{
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
			if (m_LineResults < (m_SummaryScreenVector.size() * 5))
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
				if (m_LineResults < (m_SummaryScreenVector.size() * 5))
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

ConsoleWindow SRLGame::ProfileView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		window.setTextAtPoint(Vector2(i, 1), " ", WHITE_WHITE_BG);
		window.setTextAtPoint(Vector2(i, 19), " ", WHITE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 1), "Your Profile", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 3), "Seasons Complete: " + to_string((int)m_GameProfile.seasonsSimulated), BRIGHTWHITE);
	window = m_ProfileLogo.draw_asset(window, Vector2(40, 2));
	window = m_BackTeamInDepth.draw_ui(window);
	window = m_Sponsor_Clarity_CasinoBtn.draw_ui(window);
	window = m_Sponsor_Northkellion_ShoesBtn.draw_ui(window);
	window = m_Sponsor_ZeckfastBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::ChallengesView(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		window.setTextAtPoint(Vector2(i, 1), " ", WHITE_WHITE_BG);
		window.setTextAtPoint(Vector2(i, 19), " ", WHITE_WHITE_BG);
	}
	if (sponsorState == SponsorState_Casino)
	{
		window.setTextAtPoint(Vector2(0, 1), "Clarity Casino Challenges", BLACK_WHITE_BG);
		for (int i = 0; i < m_GameProfile.Sponsor_Clarity_Casino.challenges.size(); i++)
		{
			if (m_GameProfile.Sponsor_Clarity_Casino.challenges[i].Completed)
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Clarity_Casino.challenges[i].challenge, GREEN);
			}
			else
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Clarity_Casino.challenges[i].challenge, RED);
			}
		}
	}
	else if (sponsorState == SponsorState_Shoes)
	{
		window.setTextAtPoint(Vector2(0, 1), "Northkellion Shoes Challenges", BLACK_WHITE_BG);
		for (int i = 0; i < m_GameProfile.Sponsor_Northkellion_Shoes.challenges.size(); i++)
		{
			if (m_GameProfile.Sponsor_Northkellion_Shoes.challenges[i].Completed)
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Northkellion_Shoes.challenges[i].challenge, GREEN);
			}
			else
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Northkellion_Shoes.challenges[i].challenge, RED);
			}
		}
	}
	else if (sponsorState == SponsorState_Zeckfast)
	{
		window.setTextAtPoint(Vector2(0, 1), "Zeckfast Cafes Challenges", BLACK_WHITE_BG);
		for (int i = 0; i < m_GameProfile.Sponsor_Zeckfast.challenges.size(); i++)
		{
			if (m_GameProfile.Sponsor_Zeckfast.challenges[i].Completed)
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Zeckfast.challenges[i].challenge, GREEN);
			}
			else
			{
				window.setTextAtPoint(Vector2(0, i + 2), m_GameProfile.Sponsor_Zeckfast.challenges[i].challenge, RED);
			}
		}
	}
	window = m_ProfileViewBtn.draw_ui(window, Vector2(0,19));
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

	window.setTextAtPoint(Vector2(2, 11), "Goal Kicker:", BRIGHTWHITE);
	window.setTextAtPoint(Vector2(2, 12), m_InDepthTeamView.getGoalKickerNoLimit().getName(), BRIGHTWHITE);
	if (TeamInDepthViewingJerseyAsset)
	{
		window = m_JerseyView.draw_asset(window, Vector2(30, 3));
	}
	else
	{
		window = m_LogoView.draw_asset(window, Vector2(30, 3));
	}
	window = m_TeamAssetSwitchView.draw_ui(window);
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
	for (int i = 0; i < m_InDepthTeamView.getPlayers().size() && i < 17; i++)
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

ConsoleWindow SRLGame::LeaderboardPositions(ConsoleWindow window, deque<SRLLeaderboardPosition> ldrboard)
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

void SRLGame::LeaderboardOutputStrings(deque<string>& mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName)
{
	if (ldrboard.size() > 10)
	{
		for (int i = 0; i < 10; i++)
		{
			mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
		}
		if (allowJsonExportingSeason)
		{
			save_file["name"] = ldrboardName;
			vector<json> positions;
			for (int i = 0; i < ldrboard.size(); i++)
			{
				json position;
				position["playerName"] = ldrboard[i].Player;
				position["teamName"] = ldrboard[i].TeamName;
				position["points"] = ldrboard[i].points;
				positions.push_back(position);
			}
			save_file["positions"] = positions;
		}
	}
}

void SRLGame::LeaderboardOutputStringsTopScorer(deque<string>& mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName)
{
	if (ldrboard.size() > 25)
	{
		for (int i = 0; i < 25; i++)
		{
			mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
		}
		if (allowJsonExportingSeason)
		{
			save_file["name"] = ldrboardName;
			vector<json> positions;
			for (int i = 0; i < ldrboard.size(); i++)
			{
				json position;
				position["playerName"] = ldrboard[i].Player;
				position["teamName"] = ldrboard[i].TeamName;
				position["points"] = ldrboard[i].points;
				positions.push_back(position);
			}
			save_file["positions"] = positions;
		}
	}
}

void SRLGame::LeaderboardOutputStringsTopPlayer(deque<string>& mainVec, deque<SRLLeaderboardPosition> ldrboard, json& save_file, string ldrboardName)
{
	if (ldrboard.size() > 25)
	{
		for (int i = 0; i < 25; i++)
		{
			mainVec.push_back(to_string(i + 1) + ". " + ldrboard[i].Player + "-" + ldrboard[i].TeamName + " : " + to_string(ldrboard[i].points));
		}
		if (allowJsonExportingSeason)
		{
			save_file["name"] = ldrboardName;
			vector<json> positions;
			for (int i = 0; i < ldrboard.size(); i++)
			{
				json position;
				position["playerName"] = ldrboard[i].Player;
				position["teamName"] = ldrboard[i].TeamName;
				position["points"] = ldrboard[i].points;
				positions.push_back(position);
			}
			save_file["positions"] = positions;
		}
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
		window = m_SettingsCoachBtn.draw_ui(window);
		if (coachingMode)
		{
			window.setTextAtPoint(Vector2(52, 6), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(52, 6), "Off", BRIGHTWHITE);
		}
		window = m_SettingsRepRoundsBtn.draw_ui(window);
		if (RepRoundsOn)
		{
			window.setTextAtPoint(Vector2(52, 8), "On", BRIGHTWHITE);
		}
		else
		{
			window.setTextAtPoint(Vector2(52, 8), "Off", BRIGHTWHITE);
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
	window.setTextAtPoint(Vector2(0, 5), "Version: 1.0.1.0", BRIGHTWHITE);
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
		m_GameProfile.completeChallenge("Format The Teams And Start Over", AchievementStrings);
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
		if (m_PlayerView.getRating() >= 90)
		{
			m_GameProfile.completeChallenge("Randomize A Player With a 90+ Rating", AchievementStrings);
		}
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
	if (NextRoundCall)
	{
		NextRoundCall = false;
	}
	if (PrevRoundCall)
	{
		PrevRoundCall = false;
	}
	if (SYDEKeyCode::get_key(VK_RIGHT)._CompareState(KEYDOWN))
	{
		NextRoundCall = true;
	}
	else if (SYDEKeyCode::get_key(VK_LEFT)._CompareState(KEYDOWN))
	{
		PrevRoundCall = true;
	}


	window = m_SeasonViewBtn.draw_ui(window);
	window = m_LadderViewBtn.draw_ui(window);
	window = m_ResultsViewBtn.draw_ui(window);
	if (coachingMode)
	{
		window = m_CoachingViewBtn.draw_ui(window);
	}
	else
	{
		window = m_BettingViewBtn.draw_ui(window);
	}
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
	window = m_BetTryscorers.draw_ui(window);
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

ConsoleWindow SRLGame::drawCoachingTabs(ConsoleWindow window)
{
	window = m_CoachMainStateBtn.draw_ui(window);
	window = m_CoachTradeStateBtn.draw_ui(window);
	window = m_CoachTrainStateBtn.draw_ui(window);
	window = m_CoachTeamStateBtn.draw_ui(window);
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

bool SRLGame::addGame(int limit, deque<SRLRound> rounds, deque<SRLGameMatchup>& games, deque<string>& teams, deque<string>& AttemptedTeams)
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
				json season_save_file;
				deque<string> temp;
				temp.push_back("LADDER RESULTS");
				temp.push_back("--------------------------------");
				//season_save_file["ladder"]["arraySize"] = m_Season.m_Ladder.m_Ladder.size();
				vector<json> ladderPositions;
				for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
				{
					temp.push_back(to_string(i + 1) + ". " + m_Season.m_Ladder.m_Ladder[i].teamName + " Wins: " + to_string(m_Season.m_Ladder.m_Ladder[i].won) + "| Lost: " + to_string(m_Season.m_Ladder.m_Ladder[i].lost) + "| PD: " + to_string(m_Season.m_Ladder.m_Ladder[i].pointsDifference) + "| Points: " + to_string(m_Season.m_Ladder.m_Ladder[i].points));
					if (allowJsonExportingSeason)
					{
						json ladderPOS;
						ladderPOS["id"] = i;
						ladderPOS["points"] = m_Season.m_Ladder.m_Ladder[i].points;
						ladderPOS["wins"] = m_Season.m_Ladder.m_Ladder[i].won;
						ladderPOS["lost"] = m_Season.m_Ladder.m_Ladder[i].lost;
						ladderPOS["name"] = m_Season.m_Ladder.m_Ladder[i].teamName;
						ladderPOS["pointsfor"] = m_Season.m_Ladder.m_Ladder[i].pointsFor;
						ladderPOS["pointsagainst"] = m_Season.m_Ladder.m_Ladder[i].pointsAgainst;
						ladderPositions.push_back(ladderPOS);
					}
				}
				season_save_file["ladder"] = ladderPositions;
				ladderPositions.clear();
				temp.push_back("--------------------------------");
				temp.push_back("");
				vector<json> seasonRounds;
				for (int i = 0; i < m_Season.m_Draw.m_Rounds.size(); i++)
				{
					json roundJson;
					temp.push_back("Round " + to_string(i + 1) + " Results");
					temp.push_back("--------------------------------");
					//season_save_file["rounds"]["arraySize"] = m_Season.m_Draw.m_Rounds.size();
					vector<json> roundGames;
					for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_Games.size(); ii++)
					{
						//season_save_file["rounds"][to_string(i)]["arraySize"] = m_Season.m_Draw.m_Rounds[i].m_Games.size();
						temp.push_back(m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam + " " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamScore) + " v " + to_string(m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamScore) + " " + m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam);
						if (allowJsonExportingSeason)
						{
							json gameJson;
							gameJson["homeTeam"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam;
							gameJson["awayTeam"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam;
							gameJson["homeTeamScore"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamScore;
							gameJson["homeTeamTopLead"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamBiggestLead;
							gameJson["awayTeamScore"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamScore;
							gameJson["awayTeamTopLead"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamBiggestLead;
							gameJson["homeTeamOdds"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].homeTeamOdds.ReturnPrice();
							gameJson["awayTeamOdds"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].awayTeamOdds.ReturnPrice();
							gameJson["playersent"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].playerSentInGame;
							gameJson["plays"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].ResultPlayByPlay;
							gameJson["summaries"] = m_Season.m_Draw.m_Rounds[i].m_Games[ii].SummaryPlayByPlay;
							roundGames.push_back(gameJson);
						}
					}
					roundJson["games"] = roundGames;
					//roundJson["newstories"] = m_Season.m_Draw.m_Rounds[i].newsStories.;
					seasonRounds.push_back(roundJson);
					temp.push_back("--------------------------------");
					temp.push_back("");
				}
				season_save_file["rounds"] = seasonRounds;
				seasonRounds.clear();
				vector<json> Leaderboards;
				json tempLdr;
				temp.push_back("Top Try Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopTries.shortlist, tempLdr, "tryscorers");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Goal Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopGoals.shortlist, tempLdr, "topgoals");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Field Goal Scorers");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopFieldGoals.shortlist, tempLdr, "topfieldgoals");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Metres Ran");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopMetres.shortlist, tempLdr, "topmetres");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Tackles Made");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopTackles.shortlist, tempLdr, "toptackles");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most 40/20's Kicked");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_Top4020.shortlist, tempLdr, "top4020");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Kicking Metres");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopKickMetres.shortlist, tempLdr, "topkickmetres");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Steals");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSteals.shortlist, tempLdr, "topsteals");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most No Tries");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopNoTries.shortlist, tempLdr, "topnotries");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Errors");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopErrors.shortlist, tempLdr, "toperrors");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Penalties");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopPenalty.shortlist, tempLdr, "toppenalties");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Ruck Infringements");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopRuckErrors.shortlist, tempLdr, "topruckerrors");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Sin Bins");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSinBin.shortlist, tempLdr, "topsinbins");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Send Offs");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopSendOff.shortlist, tempLdr, "topsendoffs");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Most Injuries");
				temp.push_back("--------------------------------");
				LeaderboardOutputStrings(temp, m_Season.m_TopInjuries.shortlist, tempLdr, "topinjuries");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Point Scores");
				temp.push_back("--------------------------------");
				LeaderboardOutputStringsTopScorer(temp, m_Season.m_TopPoints.shortlist, tempLdr, "topscorers");
				Leaderboards.push_back(tempLdr);
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("Top Players Of The Season");
				temp.push_back("--------------------------------");
				LeaderboardOutputStringsTopPlayer(temp, m_Season.m_TopPlayers.shortlist, tempLdr, "topplayers");
				Leaderboards.push_back(tempLdr);
				season_save_file["leaderboards"] = Leaderboards;
				temp.push_back("--------------------------------");
				temp.push_back("");
				temp.push_back("News Stories");
				temp.push_back("--------------------------------");
				for (int i = 0; i < m_Season.m_Draw.m_Rounds.size(); i++)
				{
					temp.push_back("");
					temp.push_back("Round " + to_string(i+1) + " News Stories");
					temp.push_back("--------------------------------");
					//season_save_file["rounds"][to_string(i)]["newstories"]["arraySize"] = m_Season.m_Draw.m_Rounds[i].newsStories.size();
					for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].newsStories.size(); ii++)
					{
						temp.push_back(m_Season.m_Draw.m_Rounds[i].newsStories[ii].headline);
						//season_save_file["rounds"][to_string(i)]["newstories"][to_string(ii)] = m_Season.m_Draw.m_Rounds[i].newsStories[ii].headline;
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

				if (allowJsonExportingSeason)
				{
					string filePath = string("EngineFiles\\SavedSeasonData\\Season_" + time + ".json");
					filePath.erase(std::remove(filePath.begin(), filePath.end(), ':'), filePath.end());
					filePath.erase(std::remove(filePath.begin(), filePath.end(), ' '), filePath.end());
					std::ofstream ofs(filePath);
					ofs << season_save_file.dump(1);
				}

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

ConsoleWindow SRLGame::TradingPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 4; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", GREEN_GREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Confirm Trade With " + otherTeamTrade.getName() + "?", BRIGHTWHITE_GREEN_BG);
	window.setTextAtPoint(Vector2(6, 7), "In: " + otherTeamTrade.getPlayers()[playerOtherTeamTrade].getName(), BRIGHTWHITE_GREEN_BG);
	window.setTextAtPoint(Vector2(6, 8), "Out: " + m_CoachedTeam.getPlayers()[playerMainTeamTrade].getName(), BRIGHTWHITE_GREEN_BG);
	window = m_CoachTradeConfirmOKBtn.draw_ui(window);
	window = m_CoachTradeConfirmCNCLBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::TrainingPop_UP(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 5; i < windowWidth - 5; i++)
	{
		for (int ii = 5; ii < windowHeight - 4; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", GREEN_GREEN_BG);
		}
	}
	window.setTextAtPoint(Vector2(6, 6), "Confirm Training", BRIGHTWHITE_GREEN_BG);
	window = m_CoachTrainConfirmOKBtn.draw_ui(window);
	window = m_CoachTrainConfirmCNCLBtn.draw_ui(window);
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
		SRLTeam oddsAwayTeam;
		if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound || m_Season.isWorldCup)
		{
			for (int j = 0; j < repTeams.size(); j++)
			{
				if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam)
				{
					oddsHomeTeam = repTeams[j];
				}
				else if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam)
				{
					oddsAwayTeam = repTeams[j];
				}
			}
		}
		else
		{
			oddsHomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
			oddsAwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
		}

		//SRLTeam oddsHomeTeam;
		//oddsHomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
		SYDEClickableButton a_BetBtnH = SYDEClickableButton("Bet $10",Vector2(42, j+1), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnH.SetFunc(BetMatchClick);
		a_BetBtnH.setTag(to_string(i) + ";10;0;" + "H;" + oddsHomeTeam.getName());
		m_BetButtons.push_back(a_BetBtnH);
		SYDEClickableButton a_BetBtnHCustom = SYDEClickableButton("$Custom", Vector2(51, j + 1), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnHCustom.SetFunc(CustomBetClick);
		a_BetBtnHCustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "H;" + oddsHomeTeam.getName());
		m_BetButtons.push_back(a_BetBtnHCustom);
		//SRLTeam oddsAwayTeam;
		//oddsAwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
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
		int gamesPlayed = m_Season.m_Ladder.m_Ladder[i].won + m_Season.m_Ladder.m_Ladder[i].lost + m_Season.m_Ladder.m_Ladder[i].tied;
		int maxPointsCurrent = gamesPlayed * 2;
		int maxPointsPotential = m_Season.m_Ladder.m_Ladder[i].points + ((seasonLength - gamesPlayed) * 2);
		if (m_roundToSimulate >= BaseSeasonGames)
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

void SRLGame::CalculateTryScorerOdds()
{
	m_TryScorerBetButtons.clear();


	SRLTeam oddsHomeTeam;
	SRLTeam oddsAwayTeam;
	if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound || m_Season.isWorldCup)
	{
		for (int j = 0; j < repTeams.size(); j++)
		{
			if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].HomeTeam)
			{
				oddsHomeTeam = repTeams[j];
			}
			else if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].AwayTeam)
			{
				oddsAwayTeam = repTeams[j];
			}
		}
	}
	else
	{
		oddsHomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].HomeTeam + ".json");
		oddsAwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].HomeTeam + ".json");
	}
	//12 TryScorer Bets For Each Game
	AttackersHome.clear();
	AttackersAway.clear();

	deque<SRLPlayer> homePlayers = oddsHomeTeam.addBestAttackers(AttackersHome, 6);
	deque<SRLPlayer> awayPlayers = oddsAwayTeam.addBestAttackers(AttackersAway, 6);
	for (int i = 0; i < AttackersHome.size(); i++)
	{
		SYDEClickableButton a_BetBtn = SYDEClickableButton("Bet $10", Vector2(42, i + 4), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtn.SetFunc(BetMatchClick);
		a_BetBtn.setTag(to_string(i) + ";10;0;" + "T;" + AttackersHome[i] + "#" + oddsHomeTeam.getName());
		SYDEClickableButton a_BetBtnCustom = SYDEClickableButton("$Custom", Vector2(51, i + 4), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnCustom.SetFunc(CustomBetClick);
		a_BetBtnCustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "T;" + AttackersHome[i] + "#" + oddsHomeTeam.getName());
		m_TryScorerBetButtons.push_back(a_BetBtn);
		m_TryScorerBetButtons.push_back(a_BetBtnCustom);

		SRLPlayer playerOdds = homePlayers[i];
		int oddsCents = 200;
		int additionCents = 10520 / playerOdds.getAttack();
		oddsCents += additionCents;
		
		m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].homeTeamTryOdds.push_back(SRLBetPrice(oddsCents / 100, oddsCents % 100));
	}
	for (int i = 0; i < AttackersAway.size(); i++)
	{
		SYDEClickableButton a_BetBtn = SYDEClickableButton("Bet $10", Vector2(42, i + 12), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtn.SetFunc(BetMatchClick);
		a_BetBtn.setTag(to_string(i) + ";10;0;" + "T;" + AttackersAway[i] + "#" + oddsAwayTeam.getName());
		SYDEClickableButton a_BetBtnCustom = SYDEClickableButton("$Custom", Vector2(51, i + 12), Vector2(7, 1), BLACK_BRIGHTWHITE_BG, false);
		a_BetBtnCustom.SetFunc(CustomBetClick);
		a_BetBtnCustom.setTag(to_string(i) + ";" + to_string(m_CustomBet.dollars) + ";" + to_string(m_CustomBet.cents) + ";" + "T;" + AttackersAway[i] + "#" + oddsAwayTeam.getName());
		m_TryScorerBetButtons.push_back(a_BetBtn);
		m_TryScorerBetButtons.push_back(a_BetBtnCustom);

		SRLPlayer playerOdds = awayPlayers[i];
		int oddsCents = 200;
		int additionCents = 10520 / playerOdds.getAttack();
		oddsCents += additionCents;

		m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[m_SelectedGame].awayTeamTryOdds.push_back(SRLBetPrice(oddsCents / 100, oddsCents % 100));
	}
}

void SRLGame::SimulateGames()
{
	int roundsSimulated = 0;
	while (Simulate)
	{
		int articleReduction = 0;
		if (m_roundToSimulate < BaseSeasonGames + finalsRounds)
		{
			articleReduction = m_Season.m_Draw.m_Rounds[m_roundToSimulate].newsStories.size();
		}
		int m_ArticlesRemaining = newsArticlesPerRound - articleReduction;
		if (m_Season.isWorldCup)
		{
			//TODO: REPLACE WITH VERY SPECIFIC NEWS TO THE WORLD CUP
			m_ArticlesRemaining = 0;
		}
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
			SRLTeam AwayTeam;
			if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound || m_Season.isWorldCup)
			{
				for (int j = 0; j < repTeams.size(); j++)
				{
					if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam)
					{
						HomeTeam = repTeams[j];
					}
					else if (repTeams[j].getName() == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam)
					{
						AwayTeam = repTeams[j];
					}
				}
			}
			else
			{
				HomeTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam + ".json");
				AwayTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam + ".json");
			}
			HomeTeam.cutToSeventeen();
			AwayTeam.cutToSeventeen();
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
					try
					{
						m_srlmanager.play();
						m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].calculateBiggestLeads(m_srlmanager.getHomeScore(), m_srlmanager.getAwayScore());
					}
					catch (exception ex)
					{

					}
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
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].playerSentInGame = m_srlmanager.getPlayerWasSentInGame();
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
				m_GameProfile.completeChallenge("Simulate A Tied Game", AchievementStrings);
			}
			if (coachingMode)
			{
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached && m_srlmanager.getMinutesPassed() > 80 && m_roundToSimulate >= BaseSeasonGames)
				{
					m_GameProfile.completeChallenge("Win A Finals Game In Extra Time", AchievementStrings);
				}
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached && m_srlmanager.getHomeScore() + m_srlmanager.getAwayScore() <= 10)
				{
					m_GameProfile.completeChallenge("Win A Game With 10 Or Less Total Points", AchievementStrings);
				}
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached && m_srlmanager.getHomeScore() + m_srlmanager.getAwayScore() >= 60)
				{
					m_GameProfile.completeChallenge("Win A Game With 60 Or More Total Points", AchievementStrings);
				}
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam == teamCoached)
				{
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamBiggestLead >= 12 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached)
					{
						AchievementStrings.push_back("SRL_CHOKE");
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamBiggestLead >= 12 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached)
					{
						m_GameProfile.completeChallenge("Comeback From A 12 Point Deficit", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamBiggestLead >= 1 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached && m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
					{
						m_GameProfile.completeChallenge("Win A Grand Final Having Been Down At Anytime", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamBiggestLead >= 1 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached && m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
					{
						m_GameProfile.completeChallenge("Lose A Grand Final After Having Been Up At Anytime", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamBiggestLead >= 16 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached)
					{
						m_GameProfile.completeChallenge("Throw A 16 Point Lead In A Match", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore >= 50)
					{
						m_GameProfile.completeChallenge("Win A Game By 50+ Points", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore <= -50)
					{
						m_GameProfile.completeChallenge("Lose A Game By 50+ Points", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore == 1)
					{
						m_GameProfile.completeChallenge("Win A Game By A Point", AchievementStrings);
						if (m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
						{
							m_GameProfile.completeChallenge("Win A Grand Final By A Point", AchievementStrings);
						}
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore >= 100)
					{
						m_GameProfile.completeChallenge("Score 100 Points In A Game", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore == 0)
					{
						m_GameProfile.completeChallenge("Hold The Other Team To 0", AchievementStrings);
					}
				}
				else if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam == teamCoached)
				{
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamBiggestLead >= 12 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached)
					{
						AchievementStrings.push_back("SRL_CHOKE");
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamBiggestLead >= 12 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached)
					{
						m_GameProfile.completeChallenge("Comeback From A 12 Point Deficit", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamBiggestLead >= 1 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam == teamCoached && m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
					{
						m_GameProfile.completeChallenge("Win A Grand Final Having Been Down At Anytime", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamBiggestLead >= 1 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached && m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
					{
						m_GameProfile.completeChallenge("Lose A Grand Final After Having Been Up At Anytime", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamBiggestLead >= 16 && m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].WinningTeam != teamCoached)
					{
						m_GameProfile.completeChallenge("Throw A 16 Point Lead In A Match", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore >= 50)
					{
						m_GameProfile.completeChallenge("Win A Game By 50+ Points", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore <= -50)
					{
						m_GameProfile.completeChallenge("Lose A Game By 50+ Points", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore - m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore == 1)
					{
						m_GameProfile.completeChallenge("Win A Game By A Point", AchievementStrings);
						if (m_roundToSimulate == (BaseSeasonGames + finalsRounds - 1))
						{
							m_GameProfile.completeChallenge("Win A Grand Final By A Point", AchievementStrings);
						}
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].awayTeamScore >= 100)
					{
						m_GameProfile.completeChallenge("Score 100 Points In A Game", AchievementStrings);
					}
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].homeTeamScore == 0)
					{
						m_GameProfile.completeChallenge("Hold The Other Team To 0", AchievementStrings);
					}
				}
			}
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].ResultPlayByPlay = m_srlmanager.getPlayByPlay();
			m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].SummaryPlayByPlay = m_srlmanager.getSummary();

			if (!m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound)
			{
				for (int i = 0; i < m_srlmanager.getHomeTeam().getPlayers().size(); i++)
				{
					m_Season.m_TopPlayers.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getDallyMPointsWorth());
					m_Season.m_TopTries.addToShortlist(m_srlmanager.getHomeTeam().getPlayers()[i].getName(), m_srlmanager.getHomeTeam().getName(), m_srlmanager.getHomeTeam().getPlayers()[i].getTries());
					if (m_srlmanager.getHomeTeam().getPlayers()[i].getTries() > 0)
					{
						if (coachingMode)
						{
							if (m_srlmanager.getHomeTeam().getName() == teamCoached)
							{
								if (m_srlmanager.getHomeTeam().getPlayers()[i].getTries() >= 3)
								{
									m_GameProfile.completeChallenge("Have A Player Score 3 Tries In A Match", AchievementStrings);
								}
							}
						}
						for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size(); ii++)
						{
							deque<string> betTemp = Split(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].m_teamName, '#');
							if (betTemp.size() >= 2)
							{
								if (betTemp[0] == m_srlmanager.getHomeTeam().getPlayers()[i].getName())
								{
									if (betTemp[1] == m_srlmanager.getHomeTeam().getName())
									{
										m_BetMoney.addBetPrice(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].ReturnBetWinnings());
										m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState = Bet_Won;
										AchievementStrings.push_back("SRL_TRYSCORER");
									}
								}
							}
						}
					}
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
				for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size(); ii++)
				{
					deque<string> betTemp = Split(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].m_teamName, '#');
					if (betTemp.size() >= 2)
					{
						if (betTemp[1] == m_srlmanager.getHomeTeam().getName())
						{
							if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState != Bet_Won)
							{
								m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState = Bet_Lost;
							}
						}
					}
				}
				for (int i = 0; i < m_srlmanager.getAwayTeam().getPlayers().size(); i++)
				{
					m_Season.m_TopPlayers.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getDallyMPointsWorth());
					m_Season.m_TopTries.addToShortlist(m_srlmanager.getAwayTeam().getPlayers()[i].getName(), m_srlmanager.getAwayTeam().getName(), m_srlmanager.getAwayTeam().getPlayers()[i].getTries());
					if (m_srlmanager.getAwayTeam().getPlayers()[i].getTries() > 0)
					{
						if (coachingMode)
						{
							if (m_srlmanager.getAwayTeam().getName() == teamCoached)
							{
								if (m_srlmanager.getAwayTeam().getPlayers()[i].getTries() >= 3)
								{
									m_GameProfile.completeChallenge("Have A Player Score 3 Tries In A Match", AchievementStrings);
								}
							}
						}
						for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size(); ii++)
						{
							deque<string> betTemp = Split(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].m_teamName, '#');
							if (betTemp.size() >= 2)
							{
								if (betTemp[0] == m_srlmanager.getAwayTeam().getPlayers()[i].getName())
								{
									if (betTemp[1] == m_srlmanager.getAwayTeam().getName())
									{
										m_BetMoney.addBetPrice(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].ReturnBetWinnings());
										m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState = Bet_Won;
										AchievementStrings.push_back("SRL_TRYSCORER");
									}
								}
							}
						}
					}
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
				for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size(); ii++)
				{
					deque<string> betTemp = Split(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].m_teamName, '#');
					if (betTemp.size() >= 2)
					{
						if (betTemp[1] == m_srlmanager.getAwayTeam().getName())
						{
							if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState != Bet_Won)
							{
								m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[ii].betState = Bet_Lost;
							}
						}
					}
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

				if (m_roundToSimulate == BaseSeasonGames + finalsRounds && coachingMode)
				{
					if (m_Season.m_TopPlayers.shortlist[0].TeamName == teamCoached)
					{
						m_GameProfile.completeChallenge("Coach The Player Of The Season", AchievementStrings);
					}
				}
			}

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

			if (!finals && !m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound)
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
							m_Season.m_Ladder.m_Ladder[ii].tied++;
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
		if (!finals && !m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound)
		{
			m_Season.m_Ladder.sortLadder();
		}
		bool blacklistAchievement = m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size() >= 6;
		for (int j = 0; j < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets.size(); j++)
		{
			if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_TryScorerBets[j].betState == Bet_Won)
			{
				blacklistAchievement = false;
			}
		}
		if (blacklistAchievement)
		{
			AchievementStrings.push_back("SRL_BLACKLIST");
		}
		m_roundToSimulate++;

		//NEWS STORIES
		if (m_SeasonEvents)
		{
			//TRAINING ARTICLE
			int team = rand() % 16;
			SRLTeam MainTeam;
			MainTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team].teamName + ".json");
			int player = MainTeam.getRandomPlayerInt();
			m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].newsStories.push_back(SRLNewsStoryGenerator::getRandomTraining(MainTeam, MainTeam.getPlayers()[player],astVars));
			m_ArticlesRemaining--;
			int statBoost = rand() % 9 + 1;
			int trainingBoost = rand() % 5;
			switch (trainingBoost)
			{
			case 0:
				MainTeam.addPlayerAtk(MainTeam.getPlayers()[player].getName(), statBoost);
				break;
			case 1:
				MainTeam.addPlayerDef(MainTeam.getPlayers()[player].getName(), statBoost);
				break;
			case 2:
				MainTeam.addPlayerSpd(MainTeam.getPlayers()[player].getName(), statBoost);
				break;
			case 3:
				MainTeam.addPlayerHdl(MainTeam.getPlayers()[player].getName(), statBoost);
				break;
			case 4:
				MainTeam.addPlayerKck(MainTeam.getPlayers()[player].getName(), statBoost);
				break;
			}
			MainTeam.saveTeam();
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
				m_GameProfile.addSeasonSimulated(AchievementStrings);
				if (coachingMode)
				{
					if (teamCoached == m_Season.m_Draw.m_Rounds[m_roundToSimulate - 1].m_Games[0].WinningTeam)
					{
						AchievementStrings.push_back("SRL_BEST_COACH");
						m_GameProfile.completeChallenge("Coach A Team To A Premiership", AchievementStrings);
						for (int j = 0; j < m_Season.m_Ladder.m_Ladder.size(); j++)
						{
							if (teamCoached == m_Season.m_Ladder.m_Ladder[j].teamName)
							{
								if (j >= 6)
								{
									m_GameProfile.completeChallenge("Win The Premiership From Lower Than 6th", AchievementStrings);
								}
							}
						}
					}
				}
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
				checkCoachingAchievements();
			}
			else
			{
				if (fsType == Top8Normal)
				{
#pragma region top 8 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //1v4
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[2].teamName)); //2v3
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[4].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //5v8
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[5].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //6v7
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Quarter-Finals";
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
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //4v5
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //3v6
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
					}
					else if (m_roundToSimulate == BaseSeasonGames + 2)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v3
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam));//2v4
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Preliminary-Finals";
					}
					else if (m_roundToSimulate == BaseSeasonGames + 3)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam));//1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
					}
#pragma endregion
				}
				else if (fsType == Top4Normal)
				{
#pragma region top 4 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[1].teamName)); //1v2
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //3v4
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";

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
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam)); //2v3
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Consolidation Final";
					}
					else if (m_roundToSimulate == BaseSeasonGames + 2)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam));//1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
					}
#pragma endregion
				}
				else if (fsType == Top2Normal)
				{
#pragma region top 2 normal simulation
					if (m_roundToSimulate == BaseSeasonGames)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[1].teamName)); //1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
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
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //1v8
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //2v7
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[5].teamName)); //3v6
						games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[3].teamName, m_Season.m_Ladder.m_Ladder[4].teamName)); //4v5
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Quarter-Finals";
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
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //1v4
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //2v3
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
					}
					else if (m_roundToSimulate == BaseSeasonGames + 2)
					{
						deque<SRLGameMatchup> games;
						games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v2
						m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
						m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
					}
#pragma endregion
				}
				else if (fsType == Top4Knockout)
				{
#pragma region top 4 knockout simulation
				if (m_roundToSimulate == BaseSeasonGames)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[3].teamName)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[2].teamName)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
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
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam)); //1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
				}
#pragma endregion
				}
				else if (fsType == Top8DoubleElim)
				{
#pragma region top 8 knockout double elimination simulation
				if (m_roundToSimulate == BaseSeasonGames)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[0].teamName, m_Season.m_Ladder.m_Ladder[7].teamName)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[1].teamName, m_Season.m_Ladder.m_Ladder[6].teamName)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[2].teamName, m_Season.m_Ladder.m_Ladder[5].teamName)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Ladder.m_Ladder[3].teamName, m_Season.m_Ladder.m_Ladder[4].teamName)); //4v5
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Qualifying Finals";
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
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam)); //2v3

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam)); //5v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam)); //6v7
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Quarter-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam));//1v2

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].WinningTeam));//3v5
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam));//4v6
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[2].WinningTeam));//3v4
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Consolidation Final 1";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 4)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].WinningTeam));//2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Consolidation Final 2";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 5)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[0].WinningTeam));//1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
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
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].WinningTeam)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].WinningTeam)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].WinningTeam)); //4v5
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Quarter-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames+ 1].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam));//1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand-Finals";
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
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].WinningTeam)); //1v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].WinningTeam)); //2v7
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].WinningTeam)); //4v5

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[7].LosingTeam)); //9v16
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[6].LosingTeam)); //10v15
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[5].LosingTeam)); //11v14
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames].m_Games[4].LosingTeam)); //12v13
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Knockout Round 2";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 2)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].WinningTeam)); //1v4
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].WinningTeam)); //2v3

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[7].WinningTeam)); //8v12
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[6].WinningTeam)); //7v11
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[2].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[5].WinningTeam)); //6v10
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[3].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 1].m_Games[4].WinningTeam)); //5v9

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Qualifying-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 3)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].WinningTeam)); //1v2

					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[5].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[2].WinningTeam)); //5v8
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[4].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[3].WinningTeam)); //6v7

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Quarter-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 4)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[1].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[2].WinningTeam)); //3v6
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 2].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[1].WinningTeam)); //4v5

					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Semi-Finals";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 5)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 4].m_Games[1].WinningTeam)); //3v4
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Consolidation Final";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 6)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].LosingTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 5].m_Games[0].WinningTeam)); //2v3
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Preliminary Final";
				}
				else if (m_roundToSimulate == BaseSeasonGames + 7)
				{
					deque<SRLGameMatchup> games;
					games.push_back(SRLGameMatchup(m_Season.m_Draw.m_Rounds[BaseSeasonGames + 3].m_Games[0].WinningTeam, m_Season.m_Draw.m_Rounds[BaseSeasonGames + 6].m_Games[0].WinningTeam)); //1v2
					m_Season.m_Draw.m_Rounds.push_back(SRLRound(games));
					m_Season.m_Draw.m_Rounds[m_Season.m_Draw.m_Rounds.size() - 1].RoundName = "Grand Final";
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
			if (coachingMode)
			{
				sortOutTrainingOptions();
				sortOutTradingOptions();
			}
		}
	}
}

void SRLGame::CalculateFeaturedGame()
{
	int featureGameNumber = 0;
	if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].isRepRound || m_Season.isWorldCup)
	{
		featureGameNumber = rand() % m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size();
		//PROBS NEED TO CREATE PROPER FEATURE GAMES FOR THIS
		m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature = FeaturedGame(m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam, astVars, featureGameNumber, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].homeTeamOdds, m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].awayTeamOdds, repTeams);
		return;
	}
	if (coachingMode)
	{
		bool foundGame = false;
		for (int i = 0; i < m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games.size(); i++)
		{
			if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].HomeTeam == teamCoached || m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[i].AwayTeam == teamCoached)
			{
				featureGameNumber = i;
				foundGame = true;
			}
		}
		if (!foundGame)
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
	}
	else if (finals)
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
		for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_Games.size(); ii++)
		{
			bool homeTeamInMatch = m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam || m_Season.m_Draw.m_Rounds[i].m_Games[ii].HomeTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam;
			bool awayTeamInMatch = m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].HomeTeam || m_Season.m_Draw.m_Rounds[i].m_Games[ii].AwayTeam == m_Season.m_Draw.m_Rounds[m_roundToSimulate].m_Games[featureGameNumber].AwayTeam;
			if (homeTeamInMatch && awayTeamInMatch)
			{
				if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.size() > 0)
				{
					if (m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory[0] == "No Match History To Show")
					{
						m_Season.m_Draw.m_Rounds[m_roundToSimulate].gameToFeature.MatchHistory.clear();
					}
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
		case SRLAT_Training:
			_COLOUR = BLACK_LIGHTBLUE_BG;
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
	if (coachingMode)
	{
		return;
	}
	if (_bet.betState == Bet_Won)
	{
		if (_bet.betAmount.dollars >= 10000)
		{
			m_GameProfile.completeChallenge("Place a $10k Bet And Win It", AchievementStrings);
		}
		if (_bet.ReturnBetWinningsSafe().dollars >= 1000)
		{
			m_GameProfile.completeChallenge("Win Over $1k On A Single Bet", AchievementStrings);
		}
	}
	if (_bet.betAmount.dollars >= 1000)
	{
		if (_bet.betOdds.dollars >= 3 && _bet.betState == Bet_Won)
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
	if (coachingMode)
	{
		return;
	}
	if (m_BetMoney.dollars == 0 && m_BetMoney.cents == 0)
	{
		AchievementStrings.push_back("SRL_BANKRUPT");
	}
	if (m_BetMoney.dollars >= 10000)
	{
		AchievementStrings.push_back("SRL_HIGH_ROLLER");
	}
	if (m_BetMoney.dollars >= 100000)
	{
		m_GameProfile.completeChallenge("End A Season With $100k+", AchievementStrings);
	}
	if (m_BetMoney.dollars == 0 && m_BetMoney.cents == 1)
	{
		AchievementStrings.push_back("SRL_HANGING_ON");
	}
	if (m_BetMoney.dollars == 36 && m_BetMoney.cents == 36)
	{
		m_GameProfile.completeChallenge("End The Season With $36.36 In Your Account", AchievementStrings);
	}

	if (currentBetsTotalSeason >= 50)
	{
		m_GameProfile.completeChallenge("Bet At Least 50 Times In A Completed Season", AchievementStrings);
	}
	if (currentBetsTotalSeason >= 100)
	{
		m_GameProfile.completeChallenge("Bet At Least 100 Times In A Completed Season", AchievementStrings);
	}
	if (currentBetsTotalSeason >= 500)
	{
		m_GameProfile.completeChallenge("Bet At Least 500 Times In A Completed Season", AchievementStrings);
	}
	if (currentWonBetsSeason >= 100)
	{
		m_GameProfile.completeChallenge("Win Over 100 Bets In A Season", AchievementStrings);
	}
	if (currentWonBetsSeason >= 500)
	{
		m_GameProfile.completeChallenge("Win Over 500 Bets In A Season", AchievementStrings);
	}
}

void SRLGame::checkCoachingAchievements()
{
	if (coachingMode)
	{
		m_CoachedTeam.CalculateAverages();
		if (startingRating <= 40 && m_CoachedTeam.TeamRating() >= 60)
		{
			m_GameProfile.completeChallenge("Go From A Team Rating Of < 40 to 60+", AchievementStrings);
		}
		bool undefeated = true;
		bool NoWins = true;
		bool grandFinalLoss = false;
		for (int i = 0; i < m_Season.m_Ladder.m_Ladder.size(); i++)
		{
			if (m_Season.m_Ladder.m_Ladder[i].teamName == teamCoached)
			{
				undefeated = m_Season.m_Ladder.m_Ladder[i].lost == 0;
				if (i < finalsThreshold)
				{
					if (startingRating <= 50)
					{
						AchievementStrings.push_back("SRL_UNDERDOGS");
					}
				}
				if (i == m_Season.m_Ladder.m_Ladder.size() - 1)
				{
					AchievementStrings.push_back("SRL_SACKED");
					if (startingRating >= 60)
					{
						AchievementStrings.push_back("SRL_IMPLOSION");
					}
				}
			}

		}
		if (undefeated)
		{
			for (int i = BaseSeasonGames; i < BaseSeasonGames + finalsRounds; i++)
			{
				for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_Games.size(); ii++)
				{
					if (undefeated)
					{
						if (i = BaseSeasonGames + finalsRounds - 1)
						{
							if (m_Season.m_Draw.m_Rounds[i].m_Games[ii].LosingTeam == teamCoached)
							{
								grandFinalLoss = true;
							}
						}
					}
					if (m_Season.m_Draw.m_Rounds[i].m_Games[ii].LosingTeam == teamCoached)
					{
						undefeated = false;
					}
					if (m_Season.m_Draw.m_Rounds[i].m_Games[ii].WinningTeam == teamCoached)
					{
						NoWins = false;
					}
				}
			}
		}
		if (undefeated)
		{
			AchievementStrings.push_back("SRL_COACHING_MASTERCLASS");
		}
		if (NoWins)
		{
			m_GameProfile.completeChallenge("Lose Every Game In A Season", AchievementStrings);
		}
		if (grandFinalLoss)
		{
			m_GameProfile.completeChallenge("Win Every Game In A Season But The Grand Final", AchievementStrings);
		}
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
	if (coachingMode)
	{
		//CANNOT AUTOMATICALLY TRADE IF COACHING MODE
		if (m_Season.m_Ladder.m_Ladder[team1].teamName == teamCoached)
		{
			return;
		}
	}
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
	if (coachingMode)
	{
		//CANNOT AUTOMATICALLY TRADE IF COACHING MODE
		if (m_Season.m_Ladder.m_Ladder[team1].teamName == teamCoached)
		{
			return false;
		}
	}
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
	if (coachingMode)
	{
		//CANNOT AUTOMATICALLY TRADE IF COACHING MODE
		if (m_Season.m_Ladder.m_Ladder[team2].teamName == teamCoached || m_Season.m_Ladder.m_Ladder[team1].teamName == teamCoached)
		{
			return;
		}
	}
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
	m_TryScorerBetsWriteUp.clear();
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
		for (int ii = 0; ii < m_Season.m_Draw.m_Rounds[i].m_TryScorerBets.size(); ii++)
		{
			SRLGameBetsWriting writeUp;
			writeUp.name = "Round " + to_string(i + 1) + ": " + Split(m_Season.m_Draw.m_Rounds[i].m_TryScorerBets[ii].m_teamName, '#')[0] + " " + m_Season.m_Draw.m_Rounds[i].m_TryScorerBets[ii].originalBetAmount.ReturnPrice() + " @ " + m_Season.m_Draw.m_Rounds[i].m_TryScorerBets[ii].betOdds.ReturnPrice();
			switch (m_Season.m_Draw.m_Rounds[i].m_TryScorerBets[ii].betState)
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
			m_TryScorerBetsWriteUp.push_back(writeUp);
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
	string LogoBmp = "EngineFiles\\TeamLogos\\TeamLogo" + to_string(m_InDepthTeamView.getLogoType()) + ".bmp";
	if (m_InDepthTeamView.getLogoCustom() != "")
	{
		LogoBmp = "EngineFiles\\CustomLogos\\" + m_InDepthTeamView.getLogoCustom() + ".bmp";
	}
	wstring wLogoBmp = wstring(LogoBmp.begin(), LogoBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_JerseyView = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	m_JerseyView.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	m_JerseyView.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	m_JerseyView.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	m_JerseyView.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, m_InDepthTeamView.getPrimary());
	m_JerseyView.changeAllInstancesOfColour(BLACK_WHITE_BG, m_InDepthTeamView.getSecondary());
	m_JerseyView.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, m_InDepthTeamView.getBadge());

	m_LogoView = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wLogoBmp.c_str(), 15, 15));
	if (m_InDepthTeamView.getLogoCustom() == "")
	{
		m_LogoView.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
		m_LogoView.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
		m_LogoView.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

		m_LogoView.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, m_InDepthTeamView.getPrimary());
		m_LogoView.changeAllInstancesOfColour(BLACK_WHITE_BG, m_InDepthTeamView.getSecondary());
		m_LogoView.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, m_InDepthTeamView.getBadge());
	}

	m_InDepthTeamView.CalculateAverages();
}

void SRLGame::setUpSelectedTeamView()
{
	SRLTeam a_selectedTeamView;
	a_selectedTeamView.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_SeasonTeams[teamSelected] + ".json");
	string JerseyBmp = "EngineFiles\\JerseyFeatures\\jersey" + to_string(a_selectedTeamView.getJerseryType()) + ".bmp";
	wstring wJerseyBmp = wstring(JerseyBmp.begin(), JerseyBmp.end());
	//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
	m_SelectedTeamJerseyView = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	m_SelectedTeamJerseyView.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	m_SelectedTeamJerseyView.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	m_SelectedTeamJerseyView.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	m_SelectedTeamJerseyView.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, a_selectedTeamView.getPrimary());
	m_SelectedTeamJerseyView.changeAllInstancesOfColour(BLACK_WHITE_BG, a_selectedTeamView.getSecondary());
	m_SelectedTeamJerseyView.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, a_selectedTeamView.getBadge());
	a_selectedTeamView.CalculateAverages();
	teamSelectedRating = a_selectedTeamView.TeamRating();
	m_CoachedTeam = a_selectedTeamView;
	teamCoached = m_SeasonTeams[teamSelected];
}

void SRLGame::setUpPositionShowcase(SRLPositionShowcaseState _state)
{
	setUpPosShowcaseCall = false;
	CustomAsset_Clickable newJersey = m_MiniJersery;
	newJersey.changeAllInstancesOfColour(WHITE_WHITE_BG, m_CoachedTeam.getPrimary());
	newJersey.changeAllInstancesOfColour(BRIGHTGREEN_BRIGHTGREEN_BG, GREEN_GREEN_BG);
	newJersey.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, WHITE_WHITE_BG);
	newJersey.changeAllInstancesOfColour(BLUE_BLUE_BG,LIGHTBLUE_LIGHTBLUE_BG);
	_PositionsShowcase.clear();
	if (_state == SRLPS_Backline)
	{
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[0].getName(), 1,Vector2(4, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[1].getName(), 2, Vector2(18, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[2].getName(), 3, Vector2(32, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[3].getName(), 4, Vector2(46, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[4].getName(), 5, Vector2(10, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[5].getName(), 6, Vector2(24, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[6].getName(), 7, Vector2(38, 12)));
	}
	else if (_state == SRLPS_Frontline)
	{
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[7].getName(), 8, Vector2(10, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[8].getName(), 9, Vector2(24, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[9].getName(), 10, Vector2(38, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[10].getName(), 11, Vector2(10, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[11].getName(), 12, Vector2(24, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[12].getName(), 13, Vector2(38, 12)));
	}
	else if (_state == SRLPS_Interchange)
	{
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[13].getName(), 14, Vector2(4, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[14].getName(), 15, Vector2(18, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[15].getName(), 16, Vector2(32, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[16].getName(), 17, Vector2(46, 5)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[17].getName(), 18, Vector2(10, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[18].getName(), 19, Vector2(24, 12)));
		_PositionsShowcase.push_back(SRLPositionShowcase(newJersey, m_CoachedTeam.getPlayers()[19].getName(), 20, Vector2(38, 12)));

	}
	for (int i = 0; i < _PositionsShowcase.size(); i++)
	{
		_PositionsShowcase[i].m_MiniJersery.SetFunc(SwapPositionsJerseyClick);
		_PositionsShowcase[i].m_MiniJersery.setTag(_PositionsShowcase[i].positionNumber.m_Text.substr(0, _PositionsShowcase[i].positionNumber.m_Text.size() - 1));
		if (CustomAsset_Clickable::getLastButtonTag() == _PositionsShowcase[i].m_MiniJersery.getTag() && posToSwap != "")
		{
			_PositionsShowcase[i].m_MiniJersery.ForceHighlight();
		}
	}
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

ConsoleWindow SRLGame::DoState(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_State(window, windowWidth, windowHeight);
	return window;
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
	deque<string> temp = m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].ResultPlayByPlay;
	for (int i = 0; i < temp.size(); i++)
	{
		while (temp[i].length() > 55)
		{
			m_ResultsScreenVector.push_back(temp[i].substr(0,55));
			temp[i].erase(temp[i].begin(), temp[i].begin() + 55);
		}
		m_ResultsScreenVector.push_back(temp[i]);
	}
	temp.clear();
	deque<string> temp2 = m_Season.m_Draw.m_Rounds[m_round].m_Games[m_SelectedGame].SummaryPlayByPlay;
	for (int i = 0; i < temp2.size(); i++)
	{
		deque<string> temp3 = Split(temp2[i], '#');
		if (temp3.size() < 4)
		{
			m_SummaryScreenVector.push_back(GameSummaryText("Error In Summary", temp2[i], " ", " "));
		}
		else
		{
			m_SummaryScreenVector.push_back(GameSummaryText(temp3[0], temp3[2], temp3[1], temp3[3]));
		}
		temp3.clear();
	}
	temp2.clear();
	m_LineResults = 0;
}

void SRLGame::sortOutTrainingOptions()
{
	_trainingOptions.clear();
	m_TrainingButtons.clear();
	for (int i = 0; i < 3; i++)
	{
		int trainingType = rand() % 5;
		int playerID = rand() % m_CoachedTeam.getPlayers().size();
		int stat = 0;
		switch (trainingType)
		{
			case 0:
				stat = m_CoachedTeam.getPlayers()[playerID].getAttack();
				break;
			case 1:
				stat = m_CoachedTeam.getPlayers()[playerID].getDefence();
				break;
			case 2:
				stat = m_CoachedTeam.getPlayers()[playerID].getSpeed();
				break;
			case 3:
				stat = m_CoachedTeam.getPlayers()[playerID].getKicking();
				break;
			case 4:
				stat = m_CoachedTeam.getPlayers()[playerID].getHandling();
				break;
		}
		_trainingOptions.push_back(SRLTrainingOption(m_CoachedTeam.getPlayers()[playerID].getName(), playerID,static_cast<SRLTrainingType>(trainingType), stat));
		SYDEClickableButton a_TradeBtn = SYDEClickableButton("Do Train", Vector2(47, (i * 4) + 7), Vector2(8, 1), BLACK_BRIGHTWHITE_BG, false);
		a_TradeBtn.SetFunc(DoTrainCallClick);
		a_TradeBtn.setTag(to_string(i) + ";" + to_string(playerID) + ";" + to_string(_trainingOptions[i]._price.dollars) + ";" + to_string(_trainingOptions[i]._price.cents) + ';' + to_string(static_cast<int>(_trainingOptions[i].training)));
		m_TrainingButtons.push_back(a_TradeBtn);
	}
	trainingAvailable = true;
}

void SRLGame::sortOutTradingOptions()
{
	//TRADE OFF
	_tradingOptions.clear();
	m_TradingButtons.clear();
	for (int i = 0; i < 3; i++)
	{
		int team = rand() % 16;
		if (m_Season.m_Ladder.m_Ladder[team].teamName == teamCoached)
		{
			SRLTeam offContract;
			offContract.loadTeamOffContract("EngineFiles\\GameResults\\\OffContract\\Off Contract Players.json");
			//CANNOT AUTOMATICALLY TRADE IF COACHING MODE
			int playerID = rand() % m_CoachedTeam.getPlayers().size();
			int playerID2 = offContract.getRandomPlayerInt();
			SRLTradingOption option = SRLTradingOption(m_CoachedTeam.getPlayers()[playerID].getName(), playerID, offContract.getPlayers()[playerID2].getName(), playerID2, offContract.getName());
			option.player1_atk = m_CoachedTeam.getPlayers()[playerID].getAttack();
			option.player1_def = m_CoachedTeam.getPlayers()[playerID].getDefence();
			option.player1_spd = m_CoachedTeam.getPlayers()[playerID].getSpeed();
			option.player1_hand = m_CoachedTeam.getPlayers()[playerID].getHandling();
			option.player1_kick = m_CoachedTeam.getPlayers()[playerID].getKicking();
			option.player2_atk = offContract.getPlayers()[playerID2].getAttack();
			option.player2_def = offContract.getPlayers()[playerID2].getDefence();
			option.player2_spd = offContract.getPlayers()[playerID2].getSpeed();
			option.player2_hand = offContract.getPlayers()[playerID2].getHandling();
			option.player2_kick = offContract.getPlayers()[playerID2].getKicking();
			_tradingOptions.push_back(option);
			SYDEClickableButton a_TradeBtn = SYDEClickableButton("Do Trade", Vector2(47, (i * 4) + 5), Vector2(8, 1), BLACK_BRIGHTWHITE_BG, false);
			a_TradeBtn.SetFunc(DoTradeCallClick);
			a_TradeBtn.setTag(to_string(i) + ";" + to_string(playerID) + ";" + to_string(playerID2) + ";" + offContract.getName());
			m_TradingButtons.push_back(a_TradeBtn);
		}
		else
		{
			SRLTeam offContract;
			offContract.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_Season.m_Ladder.m_Ladder[team].teamName + ".json");
			//CANNOT AUTOMATICALLY TRADE IF COACHING MODE
			int playerID = rand() % m_CoachedTeam.getPlayers().size();
			int playerID2 = offContract.getRandomPlayerInt();
			SRLTradingOption option = SRLTradingOption(m_CoachedTeam.getPlayers()[playerID].getName(), playerID, offContract.getPlayers()[playerID2].getName(), playerID2, offContract.getName());
			option.player1_atk = m_CoachedTeam.getPlayers()[playerID].getAttack();
			option.player1_def = m_CoachedTeam.getPlayers()[playerID].getDefence();
			option.player1_spd = m_CoachedTeam.getPlayers()[playerID].getSpeed();
			option.player1_hand = m_CoachedTeam.getPlayers()[playerID].getHandling();
			option.player1_kick = m_CoachedTeam.getPlayers()[playerID].getKicking();
			option.player2_atk = offContract.getPlayers()[playerID2].getAttack();
			option.player2_def = offContract.getPlayers()[playerID2].getDefence();
			option.player2_spd = offContract.getPlayers()[playerID2].getSpeed();
			option.player2_hand = offContract.getPlayers()[playerID2].getHandling();
			option.player2_kick = offContract.getPlayers()[playerID2].getKicking();
			_tradingOptions.push_back(option);
			SYDEClickableButton a_TradeBtn = SYDEClickableButton("Do Trade", Vector2(47, (i * 4) + 5), Vector2(8, 1), BLACK_BRIGHTWHITE_BG, false);
			a_TradeBtn.SetFunc(DoTradeCallClick);
			a_TradeBtn.setTag(to_string(i) + ";" + to_string(playerID) + ";" + to_string(playerID2) + ";" + offContract.getName());
			m_TradingButtons.push_back(a_TradeBtn);
		}
	}
	tradingAvailable = true;
}

ConsoleWindow SRLGame::CreateSeason(ConsoleWindow window, bool isWorldCup)
{
	m_Season.clear();
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

	refreshAvailable = maxRefreshes;

	BaseSeasonGames = static_cast<int>(seasonLength);
	SeasonStart = false;

	//WORLD CUP HAS AN OVERRIDE
	if (isWorldCup)
	{
		VersusLimit = 1;
		//DO NOT ALLOW COACHING IN WORLD CUP, THERE'S NO REASON TO BE ABLE TO DO SO ANYWAYS
		coachingMode = false;
		RepRoundsOn = false;
		m_SeasonEvents = false;
		seasonLength = Length_RoundRobin;
		BaseSeasonGames = 15;
		fsType = Top8DoubleElim;
		finalsSettingStr = "Top 8 Double-Elim";
		finalsThreshold = 8;
		finalsRounds = 6;
#pragma region createTeams

		m_SeasonTeams.clear();
		//CLEAR THE TEAMS
		repTeams.clear();
		deque<SRLTeam> tempTeams = deque<SRLTeam>({});
		//GET THE PLAYERS FROM EACH TEAM
		for (int i = 0; i < m_SeasonTeams.size(); i++)
		{
			SRLTeam a_selectedTeam;
			a_selectedTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_SeasonTeams[i] + ".json");
			for (int ii = 0; ii < a_selectedTeam.getPlayers().size(); ii++)
			{
				bool addedToTeam = false;
				for (int j = 0; j < tempTeams.size(); j++)
				{
					if (a_selectedTeam.getPlayers()[ii].getOrigin() == tempTeams[j].getName())
					{
						addedToTeam = true;
						tempTeams[j].AddPlayer(a_selectedTeam.getPlayers()[ii]);
					}
				}
				if (!addedToTeam)
				{
					SRLTeam newTeam = SRLTeam(a_selectedTeam.getPlayers()[ii].getOrigin());
					newTeam.AddPlayer(a_selectedTeam.getPlayers()[ii]);
					tempTeams.push_back(newTeam);
				}
			}
		}

		//GET ALL OFFSEASON PLAYERS
		SRLTeam offContract;
		offContract.loadTeamOffContract("EngineFiles\\GameResults\\OffContract\\Off Contract Players.json");
		for (int ii = 0; ii < offContract.getPlayers().size(); ii++)
		{
			bool addedToTeam = false;
			for (int j = 0; j < tempTeams.size(); j++)
			{
				if (offContract.getPlayers()[ii].getOrigin() == tempTeams[j].getName())
				{
					addedToTeam = true;
					tempTeams[j].AddPlayer(offContract.getPlayers()[ii]);
				}
			}
			if (!addedToTeam)
			{
				SRLTeam newTeam = SRLTeam(offContract.getPlayers()[ii].getOrigin());
				newTeam.AddPlayer(offContract.getPlayers()[ii]);
				tempTeams.push_back(newTeam);
			}
		}

		//ADD PLAYER IF TEAM LESS THAN 17 PLAYERS
		for (int j = 0; j < tempTeams.size(); j++)
		{
			while (tempTeams[j].getPlayers().size() < 17)
			{
				SRLPlayer newPlayer = SRLPlayer(SRLNameGenerator::generateRandomName(), tempTeams[j].getName(), (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20);
				offContract.AddPlayer(newPlayer);
				offContract.saveTeamOffContract();
				tempTeams[j].AddPlayer(newPlayer);
			}
		}

		//ADD SOME TEAMS IF WE DON'T HAVE ENOUGH
		while (tempTeams.size() < 16)
		{
			bool TeamExists = false;
			string __TeamName = SRLNameGenerator::generateRandomOriginCountry();
			for (int j = 0; j < tempTeams.size(); j++)
			{
				if (__TeamName == tempTeams[j].getName())
				{
					TeamExists = true;
				}
			}
			if (!TeamExists)
			{
				SRLTeam newTeam = SRLTeam(__TeamName);
				for (int p = 0; p < 17; p++)
				{
					SRLPlayer newPlayer = SRLPlayer(SRLNameGenerator::generateRandomName(), __TeamName, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20, (rand() % 80) + 20);
					offContract.AddPlayer(newPlayer);
					offContract.saveTeamOffContract();
				}
				tempTeams.push_back(newTeam);
			}
		}
		repTeams = tempTeams;
		//EVEN IT TO BE FACTOR OF 2
		if (repTeams.size() > 16)
		{
			repTeams.erase(repTeams.begin() + 16, repTeams.end());
		}

		//SORT OUT THE TEAMS
		for (int j = 0; j < repTeams.size(); j++)
		{
			repTeams[j].sortForRepresentativeTeam();
		}
#pragma region JerseyDetails
		//ADD JERSEY DETAILS TO THEM
		for (int j = 0; j < repTeams.size(); j++)
		{
			if (repTeams[j].getName() == "France")
			{
				repTeams[j].setJersey(RED_RED_BG, BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 100);
			}
			else if (repTeams[j].getName() == "Australia")
			{
				repTeams[j].setJersey(GREEN_GREEN_BG, YELLOW_YELLOW_BG, BLACK, 5);
			}
			else if (repTeams[j].getName() == "New Zealand")
			{
				repTeams[j].setJersey(LIGHTGREY_LIGHTGREY_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 1);
			}
			else if (repTeams[j].getName() == "England")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, 2);
			}
			else if (repTeams[j].getName() == "Wales")
			{
				repTeams[j].setJersey(RED_RED_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 2);
			}
			else if (repTeams[j].getName() == "Scotland")
			{
				repTeams[j].setJersey(BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 101);
			}
			else if (repTeams[j].getName() == "Canada")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, BLACK, 101);
			}
			else if (repTeams[j].getName() == "United States")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, 10);
			}
			else if (repTeams[j].getName() == "Papau New Guinea")
			{
				repTeams[j].setJersey(LIGHTGREY_LIGHTGREY_BG, YELLOW_YELLOW_BG, RED_RED_BG, 15);
			}
			else if (repTeams[j].getName() == "Fiji")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 101);
			}
			else if (repTeams[j].getName() == "Samoa")
			{
				repTeams[j].setJersey(BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 1);
			}
			else if (repTeams[j].getName() == "Italy")
			{
				repTeams[j].setJersey(BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 100);
			}
			else if (repTeams[j].getName() == "Lebanon")
			{
				repTeams[j].setJersey(GREEN_GREEN_BG, RED_RED_BG, BLACK, 23);
			}
			else if (repTeams[j].getName() == "Sweden")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, YELLOW_YELLOW_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 59);
			}
			else if (repTeams[j].getName() == "Suoonnia")
			{
				repTeams[j].setJersey(RED_RED_BG, YELLOW_YELLOW_BG, AQUA_AQUA_BG, 82);
			}
			else if (repTeams[j].getName() == "Kylzer Isles")
			{
				repTeams[j].setJersey(WHITE_WHITE_BG, BLUE_BLUE_BG, YELLOW_YELLOW_BG, 68);
			}
			else if (repTeams[j].getName() == "SYDE Island")
			{
				repTeams[j].setJersey(BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, 65);
			}
			else if (repTeams[j].getName() == "Turniostan")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, WHITE_WHITE_BG, LIGHTGREY_LIGHTGREY_BG, 29);
			}
			else if (repTeams[j].getName() == "Tyezyer")
			{
				repTeams[j].setJersey(BRIGHTYELLOW_BRIGHTYELLOW_BG, YELLOW_YELLOW_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 19);
			}
			else if (repTeams[j].getName() == "Xyler Union")
			{
				repTeams[j].setJersey(PURPLE_PURPLE_BG, LIGHTPURPLE_LIGHTPURPLE_BG, BLUE_BLUE_BG, 42);
			}
		}

#pragma endregion

#pragma endregion

		for (int n = 0; n < repTeams.size(); n++)
		{
			m_SeasonTeams.push_back(repTeams[n].getName());
		}

	}

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
	deque<SRLLadderPosition> ladders;
	for (int i = 0; i < m_SeasonTeams.size(); i++)
	{
		SRLLadderPosition newPosition;
		newPosition.teamName = m_SeasonTeams[i];
		ladders.push_back(newPosition);
	}
#pragma region Add Rounds
	SRLLadder Ladder = SRLLadder(ladders);
	deque<SRLRound> rounds = deque<SRLRound>();
	if (fsType == KnockoutTournament || fsType == KnockoutTournamentDouble)
	{
		deque<SRLGameMatchup> games;
		deque<string> AvailableTeams = m_SeasonTeams;
		games.push_back(SRLGameMatchup(AvailableTeams[0], AvailableTeams[15]));
		games.push_back(SRLGameMatchup(AvailableTeams[1], AvailableTeams[14]));
		games.push_back(SRLGameMatchup(AvailableTeams[2], AvailableTeams[13]));
		games.push_back(SRLGameMatchup(AvailableTeams[3], AvailableTeams[12]));
		games.push_back(SRLGameMatchup(AvailableTeams[4], AvailableTeams[11]));
		games.push_back(SRLGameMatchup(AvailableTeams[5], AvailableTeams[10]));
		games.push_back(SRLGameMatchup(AvailableTeams[6], AvailableTeams[9]));
		games.push_back(SRLGameMatchup(AvailableTeams[7], AvailableTeams[8]));
		rounds.push_back(SRLRound(games));
		rounds[0].RoundName = "Knockout Round 1";
	}
	for (int i = 0; i < BaseSeasonGames; i++)
	{
		//ROUND ROBIN
		if (BaseSeasonGames == 15 && VersusLimit == 1)
		{
			deque<SRLGameMatchup> games;
			deque<string> AvailableTeams = m_SeasonTeams;

			for (int k = 0; k < i; k++)
			{
				string tempAvailTeam = AvailableTeams[0];
				for (int a = 0; a < AvailableTeams.size() -1; a++)
				{
					int nextPos = a + 1;
					if (nextPos == 15)
					{
						AvailableTeams[a] = tempAvailTeam;
					}
					else
					{
						AvailableTeams[a] = AvailableTeams[nextPos];
					}
				}
			}

			games.push_back(SRLGameMatchup(AvailableTeams[0], AvailableTeams[15]));
			games.push_back(SRLGameMatchup(AvailableTeams[1], AvailableTeams[14]));
			games.push_back(SRLGameMatchup(AvailableTeams[2], AvailableTeams[13]));
			games.push_back(SRLGameMatchup(AvailableTeams[3], AvailableTeams[12]));
			games.push_back(SRLGameMatchup(AvailableTeams[4], AvailableTeams[11]));
			games.push_back(SRLGameMatchup(AvailableTeams[5], AvailableTeams[10]));
			games.push_back(SRLGameMatchup(AvailableTeams[6], AvailableTeams[9]));
			games.push_back(SRLGameMatchup(AvailableTeams[7], AvailableTeams[8]));

			rounds.push_back(SRLRound(games));
			rounds[i].RoundName = "Round " + to_string(i + 1);
			rounds[i].randomizeOrders();
		}
		else
		{
			bool pushBack = true;
			deque<SRLGameMatchup> games;
			deque<string> AvailableTeams = m_SeasonTeams;
			deque<string> AttemptedTeams = deque<string>();
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
					for (int j = 0; j < AttemptedTeams.size(); j++)
					{
						AvailableTeams.push_back(AttemptedTeams[j]);
					}
					AttemptedTeams.clear();
				}
			}
			if (pushBack)
			{
				rounds.push_back(SRLRound(games));
				rounds[i].RoundName = "Round " + to_string(i + 1);
			}
		}
	}
	if (RepRoundsOn)
	{
#pragma region RepRounds
		int teamsGenerated = 0;
		//CLEAR THE TEAMS
		repTeams.clear();
		deque<SRLTeam> tempTeams = deque<SRLTeam>({});
		//GET THE PLAYERS FROM EACH TEAM
		for (int i = 0; i < m_SeasonTeams.size(); i++)
		{
			SRLTeam a_selectedTeam;
			a_selectedTeam.loadTeam("EngineFiles\\GameResults\\Teams\\" + m_SeasonTeams[i] + ".json");
			for (int ii = 0; ii < a_selectedTeam.getPlayers().size(); ii++)
			{
				bool addedToTeam = false;
				for (int j = 0; j < tempTeams.size(); j++)
				{
					if (a_selectedTeam.getPlayers()[ii].getOrigin() == tempTeams[j].getName())
					{
						addedToTeam = true;
						tempTeams[j].AddPlayer(a_selectedTeam.getPlayers()[ii]);
					}
				}
				if (!addedToTeam)
				{
					SRLTeam newTeam = SRLTeam(a_selectedTeam.getPlayers()[ii].getOrigin());
					newTeam.AddPlayer(a_selectedTeam.getPlayers()[ii]);
					tempTeams.push_back(newTeam);
				}
			}
		}

		//REMOVE ALL TEAMS THAT DON'T HAVE 17 PLAYERS
		for (int j = 0; j < tempTeams.size(); j++)
		{
			if (tempTeams[j].getPlayers().size() >= 17)
			{
				repTeams.push_back(tempTeams[j]);
			}
		}

		//EVEN IT TO BE FACTOR OF 2
		if (repTeams.size() % 2 == 1)
		{
			repTeams.erase(repTeams.begin() + (repTeams.size() - 1));
		}

		//SORT OUT THE TEAMS
		for (int j = 0; j < repTeams.size(); j++)
		{
			for (int jj = 0; jj < repTeams[j].getPlayers().size(); jj++)
			{
				for (int k = 0; k < jj; k++)
				{
					if (repTeams[j].getPlayers()[jj].getRating() > repTeams[j].getPlayers()[k].getRating())
					{
						SRLPlayer tempPlayer = repTeams[j].getPlayers()[k];
						repTeams[j].getPlayers()[k] = repTeams[j].getPlayers()[jj];
						repTeams[j].getPlayers()[jj] = tempPlayer;
					}
				}
			}
			//STRIP BACK TO 17 PLAYERS PER TEAM
			if (repTeams[j].getPlayers().size() > 17)
			{
				repTeams[j].cutToSeventeen();
			}
		}
#pragma region JerseyDetails
		//ADD JERSEY DETAILS TO THEM
		for (int j = 0; j < repTeams.size(); j++)
		{
			if (repTeams[j].getName() == "France")
			{
				repTeams[j].setJersey(RED_RED_BG, BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 100);
			}
			else if (repTeams[j].getName() == "Australia")
			{
				repTeams[j].setJersey(GREEN_GREEN_BG, YELLOW_YELLOW_BG, BLACK, 5);
			}
			else if (repTeams[j].getName() == "New Zealand")
			{
				repTeams[j].setJersey(LIGHTGREY_LIGHTGREY_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 1);
			}
			else if (repTeams[j].getName() == "England")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, 2);
			}
			else if (repTeams[j].getName() == "Wales")
			{
				repTeams[j].setJersey(RED_RED_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 2);
			}
			else if (repTeams[j].getName() == "Scotland")
			{
				repTeams[j].setJersey(BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 101);
			}
			else if (repTeams[j].getName() == "Canada")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, BLACK, 101);
			}
			else if (repTeams[j].getName() == "United States")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, RED_RED_BG, 10);
			}
			else if (repTeams[j].getName() == "Papau New Guinea")
			{
				repTeams[j].setJersey(LIGHTGREY_LIGHTGREY_BG, YELLOW_YELLOW_BG, RED_RED_BG, 15);
			}
			else if (repTeams[j].getName() == "Fiji")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 101);
			}
			else if (repTeams[j].getName() == "Samoa")
			{
				repTeams[j].setJersey(BLUE_BLUE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, BLACK, 1);
			}
			else if (repTeams[j].getName() == "Italy")
			{
				repTeams[j].setJersey(BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 100);
			}
			else if (repTeams[j].getName() == "Lebanon")
			{
				repTeams[j].setJersey(GREEN_GREEN_BG, RED_RED_BG, BLACK, 23);
			}
			else if (repTeams[j].getName() == "Sweden")
			{
				repTeams[j].setJersey(LIGHTBLUE_LIGHTBLUE_BG, YELLOW_YELLOW_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 59);
			}
			else if (repTeams[j].getName() == "Suoonnia")
			{
				repTeams[j].setJersey(RED_RED_BG, YELLOW_YELLOW_BG, AQUA_AQUA_BG, 82);
			}
			else if (repTeams[j].getName() == "Kylzer Isles")
			{
				repTeams[j].setJersey(WHITE_WHITE_BG, BLUE_BLUE_BG, YELLOW_YELLOW_BG, 68);
			}
			else if (repTeams[j].getName() == "SYDE Island")
			{
				repTeams[j].setJersey(BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, 65);
			}
			else if (repTeams[j].getName() == "Turniostan")
			{
				repTeams[j].setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, WHITE_WHITE_BG, LIGHTGREY_LIGHTGREY_BG, 29);
			}
			else if (repTeams[j].getName() == "Tyezyer")
			{
				repTeams[j].setJersey(BRIGHTYELLOW_BRIGHTYELLOW_BG, YELLOW_YELLOW_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 19);
			}
			else if (repTeams[j].getName() == "Xyler Union")
			{
				repTeams[j].setJersey(PURPLE_PURPLE_BG, LIGHTPURPLE_LIGHTPURPLE_BG, BLUE_BLUE_BG, 42);
			}
		}

#pragma endregion
		deque<SRLGameMatchup> repGames;
		deque<string> AvailableTeams = m_SeasonTeams;
		for (int j = 0; j < repTeams.size(); j += 2)
		{
			repGames.push_back(SRLGameMatchup(repTeams[j].getName(), repTeams[j + 1].getName()));
		}
		SRLRound repRound(repGames);
		repRound.isRepRound = true;
		int repPeriod = BaseSeasonGames / 4;
		if (BaseSeasonGames > 9 && repGames.size() > 0)
		{
			repRound.RoundName = "Representive Round 1";
			rounds.insert(rounds.begin() + repPeriod, repRound);
			BaseSeasonGames++;

			repPeriod += BaseSeasonGames / 4;

			repRound.RoundName = "Representive Round 2";
			rounds.insert(rounds.begin() + repPeriod, repRound);
			BaseSeasonGames++;

			repPeriod += BaseSeasonGames / 4;

			repRound.RoundName = "Representive Round 3";
			rounds.insert(rounds.begin() + repPeriod, repRound);
			BaseSeasonGames++;
		}
#pragma endregion
	}
#pragma endregion
	//FEATURE A GAME
	int _HighlightedFirstGame = rand() % 8;
	if (isWorldCup)
	{
		//PROBS NEED TO CREATE PROPER FEATURE GAMES FOR THIS
		rounds[0].gameToFeature = FeaturedGame(rounds[0].m_Games[_HighlightedFirstGame].HomeTeam, rounds[0].m_Games[_HighlightedFirstGame].AwayTeam, astVars, _HighlightedFirstGame, rounds[0].m_Games[_HighlightedFirstGame].homeTeamOdds, rounds[0].m_Games[_HighlightedFirstGame].awayTeamOdds, repTeams);
	}
	else
	{
		rounds[0].gameToFeature = FeaturedGame(rounds[0].m_Games[_HighlightedFirstGame].HomeTeam, rounds[0].m_Games[_HighlightedFirstGame].AwayTeam, astVars, _HighlightedFirstGame, SRLBetPrice(0, 0), SRLBetPrice(0, 0));
	}
	SRLDraw Draw(rounds);
	m_Season = SRLSeason(Draw, Ladder);
	m_Season.m_PremiershipBets.clear();
	m_Season.isWorldCup = isWorldCup;
	m_GameBetsWriteUp.clear();
	m_PremiershipBetsWriteUp.clear();
	m_BetMoney = SRLBetPrice(500, 0);
	if (coachingMode)
	{
		newState = SelectTeamCoachingState;
	}
	else
	{
		newState = SeasonModeState;
	}
	m_round = 0;
	m_roundToSimulate = 0;
	drawViewState = SeasonDrawMainView;
	CalculateOdds();
	m_Season.m_Draw.m_Rounds[0].gameToFeature.fg_homeOdds = m_Season.m_Draw.m_Rounds[0].m_Games[_HighlightedFirstGame].homeTeamOdds;
	m_Season.m_Draw.m_Rounds[0].gameToFeature.fg_awayOdds = m_Season.m_Draw.m_Rounds[0].m_Games[_HighlightedFirstGame].awayTeamOdds;
	CalculatePremiershipOdds();
	return window;
}

void SRLGame::initSponsors()
{
	m_Sponsor_Clarity_CasinoBtn = SYDEClickableButton("                                              Sponsorship: Clarity Casino", Vector2(0, 5), Vector2(40, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_Sponsor_Clarity_CasinoBtn.setHighLight(RED);
	m_Sponsor_Clarity_CasinoBtn.SetFunc(SponsorButtonClick);
	m_Sponsor_Clarity_CasinoBtn._WrapText(true);
	m_Sponsor_Clarity_CasinoBtn.setTag("0");

	m_Sponsor_Northkellion_ShoesBtn = SYDEClickableButton("                                            Sponsorship: Northkellion Shoes", Vector2(0, 9), Vector2(40, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_Sponsor_Northkellion_ShoesBtn.setHighLight(RED);
	m_Sponsor_Northkellion_ShoesBtn.SetFunc(SponsorButtonClick);
	m_Sponsor_Northkellion_ShoesBtn._WrapText(true);
	m_Sponsor_Northkellion_ShoesBtn.setTag("1");

	m_Sponsor_ZeckfastBtn = SYDEClickableButton("                                              Sponsorship: Zeckfast Cafes", Vector2(0, 13), Vector2(40, 3), BLACK_BRIGHTYELLOW_BG, false);
	m_Sponsor_ZeckfastBtn.setHighLight(RED);
	m_Sponsor_ZeckfastBtn.SetFunc(SponsorButtonClick);
	m_Sponsor_ZeckfastBtn._WrapText(true);
	m_Sponsor_ZeckfastBtn.setTag("2");
}

#pragma endregion

#pragma region Ladder

