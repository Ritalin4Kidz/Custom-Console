#include "pch.h"
#include "SRLStructs.h"

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

SRLBetPrice SRLGameBet::ReturnBetWinningsSafe()
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
	return SRLBetPrice(newDollars, newCents);
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

/*
For Rep Rounds
*/
FeaturedGame::FeaturedGame(string home, string away, AssetsClass astVars,int gameNo, SRLBetPrice homeOdds, SRLBetPrice awayOdds, deque<SRLTeam> repTeams)
{
	gameNumber = gameNo;
	for (int j = 0; j < repTeams.size(); j++)
	{
		if (repTeams[j].getName() == home)
		{
			fg_homeTeam = repTeams[j];
		}
		else if (repTeams[j].getName() == away)
		{
			fg_awayTeam = repTeams[j];
		}
	}

	string JerseyBmp = "EngineFiles\\JerseyFeatures\\jersey" + to_string(fg_homeTeam.getJerseryType()) + ".bmp";
	wstring wJerseyBmp = wstring(JerseyBmp.begin(), JerseyBmp.end());
	fg_homeTeamJersey = CustomAsset(30, 15, astVars.get_bmp_as_array((WCHAR*)wJerseyBmp.c_str(), 15, 15));
	fg_homeTeamJersey.changeAllInstancesOfColour(BRIGHTWHITE_BRIGHTWHITE_BG, BLACK_BRIGHTWHITE_BG);
	fg_homeTeamJersey.changeAllInstancesOfColour(WHITE_WHITE_BG, BLACK_WHITE_BG);
	fg_homeTeamJersey.changeAllInstancesOfColour(LIGHTGREY_LIGHTGREY_BG, BLACK_LIGHTGREY_BG);

	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_BRIGHTWHITE_BG, fg_homeTeam.getPrimary());
	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_WHITE_BG, fg_homeTeam.getSecondary());
	fg_homeTeamJersey.changeAllInstancesOfColour(BLACK_LIGHTGREY_BG, fg_homeTeam.getBadge());
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

GameSummaryText::GameSummaryText(string t, string p, string player, string s)
{
	Time = t; Play = p; Player = player; ScoreText = s;
	if (Play == "TRY" || Play == "GOAL" || Play == "FIELD GOAL" || Play == "PENALTY GOAL")
	{
		summaryTextType = GSTType_Points;
	}
	else if (Play == "SEND OFF" || Play == "SIN BIN")
	{
		summaryTextType = GSTType_Sent;
	}
	else if (Play == "INJURY" || Play == "INTERCHANGE")
	{
		summaryTextType = GSTType_Interchange_Injury;
	}
	else if (Play == "KNOCK ON" || Play == "FORWARD PASS" || Play == "RUCK INFRINGEMENT")
	{
		summaryTextType = GSTType_Error;
	}
	else if (Play == "PENALTY")
	{
		summaryTextType = GSTType_Penalty;
	}
}

ConsoleWindow GameSummaryText::draw(ConsoleWindow window, Vector2 point)
{
	ColourClass colourToUse = BLACK_BRIGHTWHITE_BG;
	switch (summaryTextType)
	{
	case GSTType_Points:
		colourToUse = BRIGHTWHITE_GREEN_BG;
		break;
	case GSTType_Error:
		colourToUse = BLACK_BRIGHTWHITE_BG;
		break;
	case GSTType_Penalty:
		colourToUse = BRIGHTWHITE_BRIGHTRED_BG;
		break;
	case GSTType_Interchange_Injury:
		colourToUse = RED_BRIGHTWHITE_BG;
		break;
	case GSTType_Sent:
		colourToUse = BRIGHTWHITE_RED_BG;
		break;
	}
	for (int i = point.getX(); i < point.getX() + 50; i++)
	{
		for (int ii = point.getY(); ii < point.getY() + 4; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", colourToUse);
		}
	}
	if (Time != "!")
	{
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY()), Time, colourToUse);
	}
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), Play, colourToUse);
	if (Player != "!")
	{
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 2), Player, colourToUse);
	}
	if (ScoreText != "!")
	{
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 3), ScoreText, colourToUse);
	}
	return window;
}

ConsoleWindow SRLTrainingOption::draw(ConsoleWindow window, Vector2 point)
{
	for (int i = point.getX(); i < point.getX() + 50; i++)
	{
		for (int ii = point.getY(); ii < point.getY() + 3; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTWHITE_BLUE_BG);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY()), player + " - " + to_string(player1_currentStat), BRIGHTWHITE_BLUE_BG);
	switch (training)
	{
	case Training_Attack:
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), "Attacking Practice", BRIGHTWHITE_BLUE_BG);
		break;
	case Training_Defence:
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), "Defensive Practice", BRIGHTWHITE_BLUE_BG);
		break;
	case Training_Speed:
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), "Running Practice", BRIGHTWHITE_BLUE_BG);
		break;
	case Training_Handling:
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), "Ballrunning Practice", BRIGHTWHITE_BLUE_BG);
		break;
	case Training_Kick:
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), "Kicking Practice", BRIGHTWHITE_BLUE_BG);
		break;
	}
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY()+2), _price.ReturnPrice(), BRIGHTWHITE_BLUE_BG);
	return window;
}

ConsoleWindow SRLTradingOption::draw(ConsoleWindow window, Vector2 point)
{
	for (int i = point.getX(); i < point.getX() + 50; i++)
	{
		for (int ii = point.getY(); ii < point.getY() + 3; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK_BRIGHTYELLOW_BG);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY()), OtherTeam, BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 1), player1 + " A:" + to_string(player1_atk) + " D:" + to_string(player1_def) + " S:" + to_string(player1_spd) + " H:" + to_string(player1_hand) + " K:" + to_string(player1_kick), RED_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() + 2), player2 + " A:" + to_string(player2_atk) + " D:" + to_string(player2_def) + " S:" + to_string(player2_spd) + " H:" + to_string(player2_hand) + " K:" + to_string(player2_kick), GREEN_BRIGHTYELLOW_BG);
	return window;
}

void SRLSeason::clear()
{
	m_Draw = SRLDraw(); m_PremiershipBets.clear(); m_Ladder = SRLLadder();
	m_TopPlayers.clear();
	m_TopTries.clear();
	m_TopGoals.clear();
	m_TopPoints.clear();
	m_TopMetres.clear();
	m_TopFieldGoals.clear();
	m_TopTackles.clear();
	m_Top4020.clear();
	m_TopKickMetres.clear();
	m_TopSteals.clear();
	m_TopErrors.clear();
	m_TopPenalty.clear();
	m_TopRuckErrors.clear();
	m_TopNoTries.clear();
	m_TopSinBin.clear();
	m_TopSendOff.clear();
	m_TopInjuries.clear();
}

void SRLGameMatchup::calculateBiggestLeads(int homeScore, int awayScore)
{
	int lead = 0;
	if (homeScore > awayScore)
	{
		lead = homeScore - awayScore;
		if (lead > homeTeamBiggestLead)
		{
			homeTeamBiggestLead = lead;
		}
	}
	else
	{
		lead = awayScore - homeScore;
		if (lead > awayTeamBiggestLead)
		{
			awayTeamBiggestLead = lead;
		}
	}
}

void SRLProfile::completeChallenge(string name, deque<string>& vec)
{
	for (int i = 0; i < Sponsor_Clarity_Casino.challenges.size(); i++)
	{
		if (Sponsor_Clarity_Casino.challenges[i].challenge == name)
		{
			Sponsor_Clarity_Casino.challenges[i].Completed = true;
		}
	}
	bool casinoChallenges = true;
	for (int i = 0; i < Sponsor_Clarity_Casino.challenges.size(); i++)
	{
		casinoChallenges =  casinoChallenges && Sponsor_Clarity_Casino.challenges[i].Completed;
	}

	if (casinoChallenges)
	{
		vec.push_back("SRL_CLARITY_CASINO");
	}

	for
		(int i = 0; i < Sponsor_Northkellion_Shoes.challenges.size(); i++)
	{
		if (Sponsor_Northkellion_Shoes.challenges[i].challenge == name)
		{
			Sponsor_Northkellion_Shoes.challenges[i].Completed = true;
		}
	}
	bool shoeChallenges = true;
	for (int i = 0; i < Sponsor_Northkellion_Shoes.challenges.size(); i++)
	{
		shoeChallenges = shoeChallenges && Sponsor_Northkellion_Shoes.challenges[i].Completed;
	}
	if (shoeChallenges)
	{
		vec.push_back("SRL_NORTHKELLION");
	}

	for (int i = 0; i < Sponsor_Zeckfast.challenges.size(); i++)
	{
		if (Sponsor_Zeckfast.challenges[i].challenge == name)
		{
			Sponsor_Zeckfast.challenges[i].Completed = true;
		}
	}
	bool cafeChallenges = true;
	for (int i = 0; i < Sponsor_Zeckfast.challenges.size(); i++)
	{
		cafeChallenges = cafeChallenges && Sponsor_Zeckfast.challenges[i].Completed;
	}
	if (cafeChallenges)
	{
		vec.push_back("SRL_ZECKFAST");
	}
	SaveSettings();
}

void SRLProfile::initChallenges()
{
	deque<SRLSponsorChallenge> casinoChallenges;
	casinoChallenges.push_back(SRLSponsorChallenge("Bet At Least 50 Times In A Completed Season")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Bet At Least 100 Times In A Completed Season")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Bet At Least 500 Times In A Completed Season")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Throw A 16 Point Lead In A Match")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Simulated 1000 Total Seasons")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("End A Season With $100k+")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Lose Every Game In A Season")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Win Every Game In A Season But The Grand Final")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Win The Premiership From Lower Than 6th")); //Implemented
	casinoChallenges.push_back(SRLSponsorChallenge("End The Season With $36.36 In Your Account")); //Implemented
	casinoChallenges.push_back(SRLSponsorChallenge("Win Over 100 Bets In A Season")); //IMPLEMENTED
	casinoChallenges.push_back(SRLSponsorChallenge("Win Over 500 Bets In A Season")); //IMPLEMENTED
	Sponsor_Clarity_Casino = SRLSponsor("Clarity Casino", casinoChallenges);

	deque<SRLSponsorChallenge> northChallenges;
	northChallenges.push_back(SRLSponsorChallenge("Train A Team To A 99 Speed Stat")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Max Out A Player's Stats")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Go From A Team Rating Of < 40 to 60+")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Have A Player Score 3 Tries In A Match")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Coach The Player Of The Season")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Win A Game By 50+ Points")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Win A Game By A Point")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Win A Finals Game In Extra Time")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Hold The Other Team To 0")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Lose A Game By 50+ Points")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Score 100 Points In A Game")); //IMPLEMENTED
	northChallenges.push_back(SRLSponsorChallenge("Win A Grand Final Having Been Down At Anytime")); //IMPLEMENTED
	Sponsor_Northkellion_Shoes = SRLSponsor("Northkellion Shoes", northChallenges);

	deque<SRLSponsorChallenge> zeckChallenges;
	zeckChallenges.push_back(SRLSponsorChallenge("Coach A Team To A Premiership")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Comeback From A 12 Point Deficit")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Win A Game With 10 Or Less Total Points")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Win A Game With 60 Or More Total Points")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Lose A Grand Final After Having Been Up At Anytime")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Win A Grand Final By A Point")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Randomize A Player With a 90+ Rating")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Format The Teams And Start Over")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Have Over 50 Teams Existing")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Simulate A Tied Game")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Win Over $1k On A Single Bet")); //IMPLEMENTED
	zeckChallenges.push_back(SRLSponsorChallenge("Place a $10k Bet And Win It")); //IMPLEMENTED
	Sponsor_Zeckfast = SRLSponsor("Zeckfast Cafes", zeckChallenges);
}

void SRLProfile::LoadSettings()
{
	if (SYDEFileDefaults::exists("EngineFiles\\Settings\\playerProfile.json"))
	{
		try
		{
			std::ifstream ifs{ "EngineFiles\\Settings\\playerProfile.json" };
			json save_file = json::parse(ifs);
			seasonsSimulated = save_file["seasonsCompleted"];
			for (int i = 0; i < Sponsor_Clarity_Casino.challenges.size(); i++)
			{
				Sponsor_Clarity_Casino.challenges[i].Completed = save_file["casinoSponsor"][to_string(i)];
			}
			for (int i = 0; i < Sponsor_Northkellion_Shoes.challenges.size(); i++)
			{
				Sponsor_Northkellion_Shoes.challenges[i].Completed = save_file["northkellion"][to_string(i)];
			}
			for (int i = 0; i < Sponsor_Zeckfast.challenges.size(); i++)
			{
				Sponsor_Zeckfast.challenges[i].Completed = save_file["zeckfast"][to_string(i)];
			}
		}
		catch (exception e)
		{
			//DON'T WORRY
		}
	}
}

void SRLProfile::SaveSettings()
{
	json save_file;
	//PlayerStats
	save_file["seasonsCompleted"] = seasonsSimulated;
	for (int i = 0; i < Sponsor_Clarity_Casino.challenges.size(); i++)
	{
		save_file["casinoSponsor"][to_string(i)] = Sponsor_Clarity_Casino.challenges[i].Completed;
	}
	for (int i = 0; i < Sponsor_Northkellion_Shoes.challenges.size(); i++)
	{
		save_file["northkellion"][to_string(i)] = Sponsor_Northkellion_Shoes.challenges[i].Completed;
	}
	for (int i = 0; i < Sponsor_Zeckfast.challenges.size(); i++)
	{
		save_file["zeckfast"][to_string(i)] = Sponsor_Zeckfast.challenges[i].Completed;
	}
	std::ofstream ofs("EngineFiles\\Settings\\playerProfile.json");
	ofs << save_file;
}

ConsoleWindow SRLPositionShowcase::draw_showcase(ConsoleWindow window)
{
	window = m_MiniJersery.draw_asset(window, pos);
	window = positionNumber.draw_ui(window);
	window = playerName.draw_ui(window);
	return window;
}

string SRLPositionShowcase::getShorterName(string _s)
{
	int arraySize = 1;
	for (int i = 0; i < _s.length(); i++)
	{
		if (_s[i] == ' ')
		{
			arraySize++;
		}
	}
	std::deque<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < _s.length(); i++)
		{
			if (_s[i] == ' ')
			{
				splitString[arrayNo] = _s.substr(0, i);
				_s = _s.substr(i + 1, _s.length() - i);
				arrayNo++;
				break;
			}
		}
	}

	return splitString[0].substr(0, 1) + ". " + _s;
}

void SRLRound::randomizeOrders()
{
	for (int i = 0; i < m_Games.size(); i++)
	{
		int randNumber = rand() % m_Games.size();
		SRLGameMatchup tempMatchUp = m_Games[i];
		m_Games[i] = m_Games[randNumber];
		m_Games[randNumber] = tempMatchUp;
		if ((rand() % 10) > 5)
		{
			string TempStr = m_Games[i].HomeTeam;
			m_Games[i].HomeTeam = m_Games[i].AwayTeam;
			m_Games[i].AwayTeam = TempStr;
		}
	}
}
