#pragma once
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

enum LadderStatsViewState {
	LSV_DefaultView,
	LSV_ExtraStatsView
};

enum JerseySelectViewOptions
{
	JSV_Jersey,
	JSV_Logo
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
	PlayerViewState,
	JerseySelectState

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
	NormalSettings_STATE,
	SummarySettings_STATE
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

enum SRLMatchUpState
{
	SMUS_GameInfo = 0,
	SMUS_History
};

enum SRLSingleSimulationViewState
{
	SSV_SummaryViewState = 0,
	SSV_PlayerMatchUpViewState
};

#pragma endregion
