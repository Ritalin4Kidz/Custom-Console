#pragma once
#include <vector>
#include <string>


using namespace std;

class SRLNewsStoryGenerator
{
public:
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
#pragma endregion

#pragma region Rumours
	static vector<string> generateRumourArticlePlayerUnrest(string Team1);
	static vector<string> generateRumourArticlePayCut(string Team1, string Player1);
	static vector<string> generateRumourArticleRetirement(string Team1, string Player1);
	static vector<string> generateRumourArticlePlayerRelease(string Team1, string Player1);
	static vector<string> generateRumourArticleContractExtension(string Team1, string Player1);
#pragma endregion

#pragma region Opinion
	static vector<string> generateOpinionArticlePlayerShouldSwap(string Team1, string Player1);
	static vector<string> generateOpinionArticlePlayerOfYear(string Team1, string Player1);
#pragma endregion

#pragma region SeasonEvents
	static vector<string> generateArticleDropControversialPlayer(string Team1, string Player1, int team1, int player1);
	static vector<string> generateArticleWalksOutOnClub(string Team1, string Player1, int team1, int player1);
	static vector<string> generateMinorPremiershipArticle(string teamName);
	static vector<string> generatePremiershipArticle(string teamName);
	static vector<string> generateOffContractTradeArticle(string teamName, string newPlayer, string oldPlayer);
	static vector<string> generateTradeArticle(string teamName1, string teamName2, string Player1, string Player2);
#pragma endregion
};
