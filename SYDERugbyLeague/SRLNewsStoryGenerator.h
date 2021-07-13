#pragma once
#include <deque>
#include <string>
#include "SRLTeam.h"
#include "CustomAsset.h"
#include "AssetsClass.h"
#include "SRLNameGenerator.h"
using namespace std;

enum SRLArticleType
{
	SRLAT_Premiership,
	SRLAT_PlayerTrade,
	SRLAT_PlayerSign,
	SRLAT_Normal,
	SRLAT_DropPlayer,
	SRLAT_Training
};


struct SRLNewsArticle
{
	SRLNewsArticle() {}
	string headline;
	deque<string> newsStory;
	CustomAsset newsPicture;
	SRLArticleType type = SRLAT_Normal;
};

class SRLNewsStoryGenerator
{
public:

	static SRLNewsArticle getRandomStory(SRLTeam MainTeam, SRLPlayer MainPlayer, SRLTeam OtherTeam, SRLPlayer OtherPlayer, AssetsClass astVars);
	static SRLNewsArticle getRandomTraining(SRLTeam MainTeam, SRLPlayer MainPlayer, AssetsClass astVars);

#pragma region FeelGood
	static deque<string> generateFeelGoodArticleSickKids(string Player1);
	static deque<string> generateFeelGoodArticleSavesDrowner(string Player1);
	static deque<string> generateFeelGoodArticleDonatesToCharity(string Player1);
	static deque<string> generateFeelGoodArticleCharityEvent(string Player1, string Player2);
#pragma endregion

#pragma region FeelBad
	static deque<string> generateFeelBadArticleSexScandal(string Player1);
	static deque<string> generateFeelBadArticlePunchUp(string Player1);
	static deque<string> generateFeelBadArticleGambling(string Player1);
	static deque<string> generateFeelBadEligibilityCrisis(string Country, string Player1);
	static deque<string> generateFeelBadRSLFight(string Player1, string Player2);
#pragma endregion

#pragma region Rumours
	static deque<string> generateRumourArticlePlayerUnrest(string Team1);
	static deque<string> generateRumourArticlePayCut(string Team1, string Player1);
	static deque<string> generateRumourArticleRetirement(string Team1, string Player1);
	static deque<string> generateRumourArticlePlayerRelease(string Team1, string Player1);
	static deque<string> generateRumourArticleContractExtension(string Team1, string Player1);
#pragma endregion

#pragma region General Stories
	static deque<string> generateGeneralArticle_PassedAway(string Player);

#pragma region Opinion
	static deque<string> generateOpinionArticlePlayerShouldSwap(string Team1, string Player1);
	static deque<string> generateOpinionArticlePlayerOfYear(string Team1, string Player1);
	static deque<string> generateOpinionArticlePlayerShouldCaptain(string Country, string Player1);
	static deque<string> generateOpinionArticleCoachWantsFinalsSystem(string Team1);
#pragma endregion

#pragma region SeasonEvents
	static deque<string> generateArticleDropControversialPlayer(string Team1, string Player1, int team1, int player1);
	static deque<string> generateArticleWalksOutOnClub(string Team1, string Player1, int team1, int player1);
	static deque<string> generateMinorPremiershipArticle(string teamName);
	static deque<string> generatePremiershipArticle(string teamName);
	static deque<string> generateOffContractTradeArticle(string teamName, string newPlayer, string oldPlayer);
	static deque<string> generateTradeArticle(string teamName1, string teamName2, string Player1, string Player2);
	static deque<string> generateTrainingArticle(string teamName1, string Player1);
#pragma endregion
};
