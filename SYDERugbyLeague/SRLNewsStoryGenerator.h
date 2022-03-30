#pragma once
#include <vector>
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
	vector<string> newsStory;
	CustomAsset newsPicture;
	SRLArticleType type = SRLAT_Normal;
};

class SRLNewsStoryGenerator
{
public:

	static SRLNewsArticle getRandomStory(SRLTeam MainTeam, SRLPlayer MainPlayer, SRLTeam OtherTeam, SRLPlayer OtherPlayer, AssetsClass astVars);
	static SRLNewsArticle getRandomTraining(SRLTeam MainTeam, SRLPlayer MainPlayer, AssetsClass astVars);

#pragma region FeelGood
	static vector<string> generateFeelGoodArticleSickKids(string Player1);
	static vector<string> generateFeelGoodArticleSavesDrowner(string Player1);
	static vector<string> generateFeelGoodArticleDonatesToCharity(string Player1);
	static vector<string> generateFeelGoodArticleCharityEvent(string Player1, string Player2);
#pragma endregion

#pragma region FeelBad
	static vector<string> generateFeelBadArticleSexScandal(string Player1);
	static vector<string> generateFeelBadArticlePunchUp(string Player1);
	static vector<string> generateFeelBadArticleGambling(string Player1);
	static vector<string> generateFeelBadEligibilityCrisis(string Country, string Player1);
	static vector<string> generateFeelBadRSLFight(string Player1, string Player2);
#pragma endregion

#pragma region Rumours
	static vector<string> generateRumourArticlePlayerUnrest(string Team1);
	static vector<string> generateRumourArticlePayCut(string Team1, string Player1);
	static vector<string> generateRumourArticleRetirement(string Team1, string Player1);
	static vector<string> generateRumourArticlePlayerRelease(string Team1, string Player1);
	static vector<string> generateRumourArticleContractExtension(string Team1, string Player1);
#pragma endregion

#pragma region General Stories
	static vector<string> generateGeneralArticle_PassedAway(string Player);
	static vector<string> generateGeneralArticle_TalksRetirement(string Player);

#pragma region Opinion
	static vector<string> generateOpinionArticlePlayerShouldSwap(string Team1, string Player1);
	static vector<string> generateOpinionArticlePlayerOfYear(string Team1, string Player1);
	static vector<string> generateOpinionArticlePlayerShouldCaptain(string Country, string Player1);
	static vector<string> generateOpinionArticleCoachWantsFinalsSystem(string Team1);
#pragma endregion

#pragma region SeasonEvents
	static vector<string> generateArticleDropControversialPlayer(string Team1, string Player1, int team1, int player1);
	static vector<string> generateArticleWalksOutOnClub(string Team1, string Player1, int team1, int player1);
	static vector<string> generateMinorPremiershipArticle(string teamName);
	static vector<string> generatePremiershipArticle(string teamName);
	static vector<string> generateOffContractTradeArticle(string teamName, string newPlayer, string oldPlayer);
	static vector<string> generateTradeArticle(string teamName1, string teamName2, string Player1, string Player2);

	static vector<string> generateGeneralArticle_ToRetire(string Player);
#pragma endregion

#pragma region Training
	static vector<string> generateTrainingArticle(string teamName1, string Player1);
	static vector<string> generateTrainingArticle_Unleashed(string teamName1, string Player1);
	static vector<string> generateTrainingArticle_AimsToProve(string teamName1, string Player1);
#pragma endregion
};
