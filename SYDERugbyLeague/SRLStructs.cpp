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
