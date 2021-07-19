#include "pch.h"
#include "SRLNewsStoryGenerator.h"

deque<string> SRLNewsStoryGenerator::generateMinorPremiershipArticle(string teamName)
{
	deque<string> temp;
	temp.push_back(teamName + " have won the");
	temp.push_back("minor premiership after a hard fought season.");
	temp.push_back("Having confirmed a home qualifying final,");
	temp.push_back(teamName + " will be looking to");
	temp.push_back("convert this into the main premiership come");
	temp.push_back("grand final day.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generatePremiershipArticle(string teamName)
{
	deque<string> temp;
	temp.push_back(teamName + " have won the");
	temp.push_back("premiership after a hard fought grand final.");
	temp.push_back("The CEO of " + teamName);
	temp.push_back("has announced a 70% discount in the merch store");
	temp.push_back("as a celebration of this achievement.");
	temp.push_back(" ");
	temp.push_back("Congratulations " + teamName + "!");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateOffContractTradeArticle(string teamName, string newPlayer, string oldPlayer)
{
	deque<string> temp;
	int pay = (rand() % 9) + 1;
	temp.push_back(teamName + " have boosted their squad");
	temp.push_back("after the signing of the off contract " + newPlayer + ".");
	temp.push_back("Unfortunately this signing also means that");
	temp.push_back(teamName + " have let go of " + oldPlayer + ".");
	temp.push_back(oldPlayer + " is now currently looking for a new club");
	temp.push_back("Sources tell us that " + newPlayer + " has");
	temp.push_back("been signed for $" +to_string(pay) + "00k/year");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateTradeArticle(string teamName1, string teamName2, string Player1, string Player2)
{
	deque<string> temp;
	temp.push_back(teamName1 + " & " + teamName2);
	temp.push_back("have agreed to do a player swap!");
	temp.push_back("This trade sees " + Player1);
	temp.push_back("find a new home at the " + teamName2);
	temp.push_back("whilst " + Player2 + " will now have to adapt");
	temp.push_back("to their new role at " + teamName1 + ".");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateTrainingArticle(string teamName1, string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " has had a rough season");
	temp.push_back("this year, but the player says that after");
	temp.push_back("an inspiring training session, that they're");
	temp.push_back("ready to come in to the next game with a new");
	temp.push_back("attitude.");
	temp.push_back("'Yeah it's rough training here over at the");
	temp.push_back(teamName1 + ", but it's good'");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateTrainingArticle_Unleashed(string teamName1, string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " has had a slow season so far.");
	temp.push_back("But after feeling inspired by the criticism,");
	temp.push_back(Player1 + " has promised fans that");
	temp.push_back("they will be 'unleashed' in the upcoming");
	temp.push_back("games.");
	temp.push_back(teamName1 + " have backed these claims,");
	temp.push_back("stating that the player has been slowing");
	temp.push_back("down in their alcohol intake.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateTrainingArticle_AimsToProve(string teamName1, string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " is determined to prove the critics");
	temp.push_back("wrong, after an inspired training session");
	temp.push_back("has allegedly impressed the coach.");
	temp.push_back("'Yeah they really knew how'd to rugby in");
	temp.push_back("that session' said ");
	temp.push_back(teamName1 + "'s coach");
	temp.push_back("'yeah should be a good game'");
	return temp;
}

SRLNewsArticle SRLNewsStoryGenerator::getRandomStory(SRLTeam MainTeam, SRLPlayer MainPlayer, SRLTeam OtherTeam, SRLPlayer OtherPlayer, AssetsClass astVars)
{
	SRLNewsArticle m_Article;
	int articleType = rand() % 18;
	string fakePlayer = SRLNameGenerator::generateRandomName();
	switch (articleType)
	{
	case 0:
		m_Article.headline = MainPlayer.getName() + " Saves Local Man From Drowning";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelGoodArticleSavesDrowner(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Health.bmp", 7, 7));
		break;
	case 1:
		m_Article.headline = MainPlayer.getName() + " Donates To Controverisal Charity";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelGoodArticleDonatesToCharity(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Cash.bmp", 7, 7));
		break;
	case 2:
		m_Article.headline = MainPlayer.getName() + " Involved In Sexting Scandal";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelBadArticleSexScandal(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Phone.bmp", 7, 7));
		break;
	case 3:
		m_Article.headline = MainPlayer.getName() + " Assaults RSL Bouncer";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelBadArticlePunchUp(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Health.bmp", 7, 7));
		break;
	case 4:
		m_Article.headline = MainPlayer.getName() + "'s Large-Scale Gambling Problem";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelBadArticleGambling(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Coin.bmp", 7, 7));
		break;
	case 5:
		m_Article.headline = MainPlayer.getName() + " At Risk Of An Early Release!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateRumourArticlePlayerRelease(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 6:
		m_Article.headline = MainPlayer.getName() + " To Have Contract Extended!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateRumourArticleContractExtension(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Cash.bmp", 7, 7));
		break;
	case 7:
		m_Article.headline = "Player Unrest At " + MainTeam.getName();
		m_Article.newsStory = SRLNewsStoryGenerator::generateRumourArticlePlayerUnrest(MainTeam.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 8:
		m_Article.headline = MainPlayer.getName() + " Offered Pay Cut To Re-sign";
		m_Article.newsStory = SRLNewsStoryGenerator::generateRumourArticlePayCut(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Cash.bmp", 7, 7));
		break;
	case 9:
		m_Article.headline = MainPlayer.getName() + "'s Retirment Rumours!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateRumourArticleRetirement(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 10:
		m_Article.headline = "Rival Players Raise Awareness!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelGoodArticleCharityEvent(OtherPlayer.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Goalpost.bmp", 7, 7));
		break;
	case 11:
		m_Article.headline = "Opinion: " + MainPlayer.getName() + " Should Swap Teams";
		m_Article.newsStory = SRLNewsStoryGenerator::generateOpinionArticlePlayerShouldSwap(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 12:
		m_Article.headline = "Fan Poll: " + MainTeam.getName() + "'s Best Player";
		m_Article.newsStory = SRLNewsStoryGenerator::generateOpinionArticlePlayerOfYear(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 13:
		m_Article.headline = "Opinion: " + MainPlayer.getName() + " Should Captain " + MainPlayer.getOrigin();
		m_Article.newsStory = SRLNewsStoryGenerator::generateOpinionArticlePlayerShouldCaptain(MainPlayer.getOrigin(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 14:
		m_Article.headline = MainPlayer.getName() + "'s Eligibility Crisis!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelBadEligibilityCrisis(MainPlayer.getOrigin(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 15:
		m_Article.headline = "Coach Proposes New Finals System!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateOpinionArticleCoachWantsFinalsSystem(MainTeam.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 16:
		m_Article.headline = "Players Fight At Local RSL!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelBadRSLFight(OtherPlayer.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 17:
		m_Article.headline = fakePlayer +  " Passes Away After Illness";
		m_Article.newsStory = SRLNewsStoryGenerator::generateGeneralArticle_PassedAway(fakePlayer);
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Tombstone.bmp", 7, 7));
		break;
	case 18:
		m_Article.headline = fakePlayer + " Talks Retirement!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateGeneralArticle_TalksRetirement(fakePlayer);
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Health.bmp", 7, 7));
		break;
	default:
		m_Article.headline = MainPlayer.getName() + " Helps Sick Kids In Hospital";
		m_Article.newsStory = SRLNewsStoryGenerator::generateFeelGoodArticleSickKids(MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Health.bmp", 7, 7));
		break;
	}
	return m_Article;
}

SRLNewsArticle SRLNewsStoryGenerator::getRandomTraining(SRLTeam MainTeam, SRLPlayer MainPlayer, AssetsClass astVars)
{
	SRLNewsArticle m_Article;
	int articleType = rand() % 1;
	switch (articleType)
	{
	case 0:
		m_Article.headline = MainPlayer.getName() + "'s Tough Training Session";
		m_Article.newsStory = SRLNewsStoryGenerator::generateTrainingArticle(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 1:
		m_Article.headline = MainPlayer.getName() + " To Be Unleashed!";
		m_Article.newsStory = SRLNewsStoryGenerator::generateTrainingArticle_Unleashed(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	case 2:
		m_Article.headline = MainPlayer.getName() + " Aims To Prove Critics Wrong";
		m_Article.newsStory = SRLNewsStoryGenerator::generateTrainingArticle_AimsToProve(MainTeam.getName(), MainPlayer.getName());
		m_Article.newsPicture = CustomAsset(14, 7, astVars.get_bmp_as_array(L"EngineFiles\\ArticlePictures\\Important.bmp", 7, 7));
		break;
	}
	m_Article.type = SRLAT_Training;
	return m_Article;
}

deque<string> SRLNewsStoryGenerator::generateFeelGoodArticleSickKids(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " met with some young fans");
	temp.push_back("in a local hospital yesterday. Some people");
	temp.push_back("have questioned the legitimacy of their act, with some");
	temp.push_back("claiming it was to fulfill hours of community service");
	temp.push_back("after last year's parking ticket incident.");
	temp.push_back(Player1 + " has denied these claims,");
	temp.push_back("slamming their critics as 'A Bunch Of Cowards'.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelGoodArticleSavesDrowner(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " has been met with applause today");
	temp.push_back("after they heroically saved a local 50 year old man");
	temp.push_back("from drowning at a local beach.");
	temp.push_back("The SRL has reacted to this event by offering the man");
	temp.push_back("free tickets to the next home game.");
	temp.push_back("The man has responded by saying:");
	temp.push_back("'I appreciate " + Player1 + ", but i hate their team.'");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelGoodArticleDonatesToCharity(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " donated $50k to a local charity");
	temp.push_back("today, and now they are challenging other SRL players");
	temp.push_back("to match the donation.");
	temp.push_back("'We all are more fortunate then others, and we need to");
	temp.push_back("use our power to make this world a better place'");
	temp.push_back("Twitter users have criticised the donation, after it was");
	temp.push_back("found that the charity organisation has strong");
	temp.push_back("anti-LGBT connections. " + Player1);
	temp.push_back("has not commented on that matter.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateRumourArticlePlayerRelease(string Team1, string Player1)
{
	deque<string> temp;
	temp.push_back("Sources tell us that " + Team1 + " are");
	temp.push_back("considering telling " + Player1 + " to");
	temp.push_back("Find a new home immediately. This comes after rumours");
	temp.push_back(Player1 + " has already been told they're");
	temp.push_back("free to talk to other clubs. This news has already");
	temp.push_back("sparked outrage from fans on social media, especially");
	temp.push_back("those who consider " + Player1 + " to");
	temp.push_back("be a fan favourite");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateRumourArticleContractExtension(string Team1, string Player1)
{
	deque<string> temp;
	temp.push_back("Sources tell us that " + Team1 + " are");
	temp.push_back("considering extending " + Player1 + "'s");
	temp.push_back("contract by a further 3 years.");
	temp.push_back(Player1 + " has already been approached");
	temp.push_back("by other clubs, who were hoping to snatch the");
	temp.push_back("fan favourite before season's end.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateGeneralArticle_PassedAway(string Player)
{
	deque<string> temp;
	temp.push_back("After a lengthy battle with terminal illness, it is");
	temp.push_back("with deep sadness that we report the death of beloved");
	temp.push_back("player " + Player + " passed away today.");
	temp.push_back("Players of the league will be remembering their");
	temp.push_back("legacy with a moment of silence before each game");
	temp.push_back("this round.");
	temp.push_back("They were aged 74");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateGeneralArticle_TalksRetirement(string Player)
{
	deque<string> temp;
	temp.push_back("After a beloved career that was cut short 2 years ago,");
	temp.push_back(Player + " has taken the time to speak");
	temp.push_back("out about retirement today.");
	temp.push_back("'My Brain Hurts'");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateOpinionArticlePlayerShouldSwap(string Team1, string Player1)
{
	deque<string> temp;
	temp.push_back("After having watched " + Player1 + " play");
	temp.push_back("as long as I have for " + Team1 +",");
	temp.push_back("I have come to the conclusion that their potential is");
	temp.push_back("being wasted and they would be much better off if they");
	temp.push_back("found a home elsewhere. I don't think I've ever seen a");
	temp.push_back("player get as screwed over by their teammates in game");
	temp.push_back("as much as " + Player1 + " does");
	temp.push_back("PASS EM THE BLOODY BALL");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateOpinionArticlePlayerOfYear(string Team1, string Player1)
{
	deque<string> temp;
	temp.push_back("The fans have spoken, and they claim that the best");
	temp.push_back("player for " + Team1 + " is no other");
	temp.push_back("than " + Player1 + "!");
	temp.push_back(Player1 + " won with 70% of the vote,");
	temp.push_back("after a social media campaign from them went");
	temp.push_back("viral. Speculation is that the club is now");
	temp.push_back("considering resigning them for another 2");
	temp.push_back("years!");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateOpinionArticlePlayerShouldCaptain(string Country, string Player1)
{
	deque<string> temp;
	temp.push_back("With rumours of a world cup coming end of season, ");
	temp.push_back(Country + " must start looking quick to");
	temp.push_back("become a major contender for the title. To start,");
	temp.push_back(Player1 + " should be given the role of captain.");
	temp.push_back("In my opinion, they have stepped up and showed");
	temp.push_back("leadership when no one else has. This simple");
	temp.push_back("change could see " + Country + " become");
	temp.push_back("a quick favourite.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateOpinionArticleCoachWantsFinalsSystem(string Team1)
{
	deque<string> temp;
	temp.push_back(Team1 +"'s coach has proposed");
	temp.push_back("a new finals system to the SRL Today. This new");
	temp.push_back("system would see the top 11 teams go through,");
	temp.push_back("with the minor premiers getting week 1 off.");
	temp.push_back("Criticism has come over it's complicated");
	temp.push_back("structure, and 11 week system.");
	temp.push_back("'It's just an idea at the moment', the coach");
	temp.push_back("responded, 'don't get too involved yet'");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelBadArticleSexScandal(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " is currently in hot water");
	temp.push_back("after a sexting scandal arrised today");
	temp.push_back(Player1 + " has been alleged to have been");
	temp.push_back("sexting other players for the past year and a half");
	temp.push_back("When asked for a comment, all we recieved was a pic");
	temp.push_back("of their genitalia.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelBadArticlePunchUp(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " is currently out on bail");
	temp.push_back("after an alleged punch on at northies RSL occured");
	temp.push_back("last friday night.");
	temp.push_back("We asked " + Player1 + " for a comment,");
	temp.push_back("who only responded by threatening to 'take this outside'");
	temp.push_back("We'll have more as this story develops");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelBadArticleGambling(string Player1)
{
	deque<string> temp;
	temp.push_back(Player1 + " has allegedly lost over $30k");
	temp.push_back("at the pokies last night after a long bender.");
	temp.push_back("When reached out for a comment, " + Player1);
	temp.push_back("responded by pushing us aside, and claiming that we were");
	temp.push_back("'bringing bad luck to the machine'.");
	temp.push_back("We'll have more as this story develops");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelBadEligibilityCrisis(string Country, string Player1)
{
	deque<string> temp;
	temp.push_back(Country + " have been dealt a possibly huge blow");
	temp.push_back("after " + Player1 + " was announced");
	temp.push_back("to be under investigation for possible ineligibility");
	temp.push_back("to play for the country. This comes after rumours");
	temp.push_back("that they did not move to that country and play");
	temp.push_back("rugby, before the age of 13.");
	temp.push_back(Player1 + " has denied the allegations, ");
	temp.push_back("claiming that the investigation will lead only");
	temp.push_back("to prove innocence. The player is allowed to play");
	temp.push_back("for the country in the meantime");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelBadRSLFight(string Player1, string Player2)
{
	deque<string> temp;
	temp.push_back(Player1 + " & " + Player2 + " are in");
	temp.push_back("hot water today after the two were caught on");
	temp.push_back("camera having a drunken brawl at a local RSL.");
	temp.push_back("The two players are set to face court over the");
	temp.push_back("alleged incident, however they will be free");
	temp.push_back("to continue to play in the SRL in the time");
	temp.push_back("being.");
	temp.push_back("Neither player responded when asked for a");
	temp.push_back("comment on the matter.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateArticleDropControversialPlayer(string Team1, string Player1, int team1, int player1)
{
	deque<string> temp;
	temp.push_back("After a recent controversy, " + Team1);
	temp.push_back("have decided to drop " + Player1 + " from");
	temp.push_back("their team, and have released them from their contract.");
	temp.push_back("It is currently unknown who will be replacing them");
	temp.push_back("on the starting line-up, however it is confirmed ");
	temp.push_back("that " + Team1 + " already have a replacement ready.");
	temp.push_back("We'll have more as this story develops");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateArticleWalksOutOnClub(string Team1, string Player1, int team1, int player1)
{
	deque<string> temp;
	temp.push_back("After issues with recent contract negotiations, ");
	temp.push_back(Player1 + " has walked from the ");
	temp.push_back(Team1 + ", who in return have released them");
	temp.push_back("from the team, and are threatening legal action");
	temp.push_back("to get them barred from the SRL for the remainder");
	temp.push_back("of the original contract.");
	temp.push_back("It is currently unsure who will be replacing");
	temp.push_back(Player1 + " at " + Team1 + ".");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateRumourArticlePlayerUnrest(string Team1)
{
	deque<string> temp;
	temp.push_back("It seems that the coach of " + Team1);
	temp.push_back("has lost the dressing room after bombshell");
	temp.push_back("allegations arose today that 5 key players are");
	temp.push_back("considering swapping to rival clubs as soon as possible.");
	temp.push_back(Team1 + " has denied these allegations,");
	temp.push_back("jokingly adding that the only problem at the club is");
	temp.push_back("the lack of chairs in the ground.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateRumourArticlePayCut(string Team1, string Player1)
{
	deque<string> temp;
	int pay = (rand() % 9) + 1;
	temp.push_back(Player1 + " has reportedly been told that");
	temp.push_back("if they want to stay at " + Team1 + ",");
	temp.push_back("they must be willing to take a $" + to_string(pay) + "00k/year" );
	temp.push_back("pay cut, or they won't re-sign them.");
	temp.push_back("This is the latest development in what has been a");
	temp.push_back("pretty ugly contract drama between the player and");
	temp.push_back("their club. It is expected that " + Player1);
	if (pay < 3)
	{
		temp.push_back("will accept the pay cut.");
	}
	else
	{
		temp.push_back("will decline the offer and look elsewhere.");
	}
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateRumourArticleRetirement(string Team1, string Player1)
{
	deque<string> temp;
	temp.push_back("Sources tell us that " + Player1 + " will");
	temp.push_back("be finishing their career at " + Team1 + ",");
	temp.push_back("with retirement potentially coming at the end of the season.");
	temp.push_back("The retirement is expected to be announced anywhere between");
	temp.push_back("tomorrow, and the near future.");
	temp.push_back(Player1 + " did not respond when we approached them");
	temp.push_back("for a comment.");
	return temp;
}

deque<string> SRLNewsStoryGenerator::generateFeelGoodArticleCharityEvent(string Player1, string Player2)
{
	deque<string> temp;
	temp.push_back(Player1 + " & " + Player2 + " have");
	temp.push_back("today put their SRL rivalry aside to host a charity event");
	temp.push_back("to help raise money for SYDE Disease awareness.");
	temp.push_back("The event was hosted in East Kylzebrek, & saw the two");
	temp.push_back("players coach teams of kids, who would then play");
	temp.push_back("touch footy games. Some of those kids are inflicted");
	temp.push_back("with the disease themselves.");
	temp.push_back(Player2 + ": 'Yeah it's a good cause'");
	return temp;
}
