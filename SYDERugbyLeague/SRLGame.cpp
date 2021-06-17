#include "SRLGame.h"

SRLGameManager::SRLGameManager()
{
	m_SecondsPassed = 0;
	m_MinutesPassed = 0;
}

SRLGameManager::~SRLGameManager()
{
}

void SRLGameManager::addPlay(string a_Play)
{
	string minutesStr = to_string(m_MinutesPassed);
	if (minutesStr.length() == 1)
	{
		minutesStr = "0" + minutesStr;
	}
	string secondsStr = to_string(m_SecondsPassed);
	if (secondsStr.length() == 1)
	{
		secondsStr = "0" + secondsStr;
	}
	m_PlayByPlay.push_back(minutesStr + ":" + secondsStr + " - "  + a_Play);
}

void SRLGameManager::addPlayNoMinutes(string a_Play)
{
	m_PlayByPlay.push_back(a_Play);
}

void SRLGameManager::addPlay(string a_Play, SRLPlayer player)
{
	string minutesStr = to_string(m_MinutesPassed);
	if (minutesStr.length() == 1)
	{
		minutesStr = "0" + minutesStr;
	}
	string secondsStr = to_string(m_SecondsPassed);
	if (secondsStr.length() == 1)
	{
		secondsStr = "0" + secondsStr;
	}
	m_PlayByPlay.push_back(minutesStr + ":" + secondsStr + " - " + player.getName() + " - " + a_Play);
}



int SRLGameManager::fromRand(int range)
{
	if (range == 0)
	{
		range = 1;
	}
	return rand() % range;
}

void SRLGameManager::addTeamLineupsPlayByPlay()
{
	addPlayNoMinutes("----------LINE-UPS----------");
	addPlayNoMinutes("Home Team: " + m_HomeTeam.getName());
	for (int i = 0; i < m_HomeTeam.getPlayers().size(); i++)
	{
		addPlayNoMinutes(std::to_string(i+1) +": " + m_HomeTeam.getPlayers()[i].getName());
	}
	addPlayNoMinutes("Away Team: " + m_AwayTeam.getName());
	for (int i = 0; i < m_AwayTeam.getPlayers().size(); i++)
	{
		addPlayNoMinutes(std::to_string(i + 1) + ": " + m_AwayTeam.getPlayers()[i].getName());
	}
	addPlayNoMinutes("----------------------------");
}

void SRLGameManager::addStartTimePlay()
{
	addPlay("KICK OFF - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore));
}

void SRLGameManager::addFullTimePlay()
{
	addPlay("FULL TIME - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore));
}

void SRLGameManager::endStats()
{
	//m_HomeTeam.saveTeam();
	//m_AwayTeam.saveTeam();
	addPlayNoMinutes("                             ");
	addPlayNoMinutes("--------PLAYER STATS--------");
	addPlayNoMinutes("Home Team: " + m_HomeTeam.getName());
	for (int i = 0; i < m_HomeTeam.getPlayers().size(); i++)
	{
		addPlayNoMinutes(std::to_string(i + 1) + ": " + m_HomeTeam.getPlayers()[i].getName() + " " + m_HomeTeam.getPlayers()[i].getStatsString());
	}
	addPlayNoMinutes("Highlights:                 ");
	addPlayNoMinutes("Most Tackles: " + m_HomeTeam.getMostTackles());
	addPlayNoMinutes("Most Points: " + m_HomeTeam.getMostPoints());
	addPlayNoMinutes("Most Metres: " + m_HomeTeam.getMostMetres());
	addPlayNoMinutes("Most Errors: " + m_HomeTeam.getMostErrors());
	addPlayNoMinutes("                             ");
	addPlayNoMinutes("Away Team: " + m_AwayTeam.getName());
	for (int i = 0; i < m_AwayTeam.getPlayers().size(); i++)
	{
		addPlayNoMinutes(std::to_string(i + 1) + ": " + m_AwayTeam.getPlayers()[i].getName() + " " + m_AwayTeam.getPlayers()[i].getStatsString());
	}
	addPlayNoMinutes("Highlights:                 ");
	addPlayNoMinutes("Most Tackles: " + m_AwayTeam.getMostTackles());
	addPlayNoMinutes("Most Points: " + m_AwayTeam.getMostPoints());
	addPlayNoMinutes("Most Metres: " + m_AwayTeam.getMostMetres());
	addPlayNoMinutes("Most Errors: " + m_AwayTeam.getMostErrors());
	addPlayNoMinutes("                             ");
	addPlayNoMinutes("---------TEAM STATS---------");
	addPlayNoMinutes("Home Team: " + m_HomeTeam.getName());
	addPlayNoMinutes("Total Metres: " + to_string(m_HomeTeam.totalMetres()));
	addPlayNoMinutes("Total Kick Metres: " + to_string(m_HomeTeam.totalKickMetres()));
	addPlayNoMinutes("Total Errors: " + to_string(m_HomeTeam.totalErrors()));
	addPlayNoMinutes("Total Tackles: " + to_string(m_HomeTeam.totalTackles()));
	addPlayNoMinutes("Total Tries: " + to_string(m_HomeTeam.totalTries()));
	addPlayNoMinutes("Total Goals: " + to_string(m_HomeTeam.totalGoals()));
	addPlayNoMinutes("Total Field Goals: " + to_string(m_HomeTeam.totalFieldGoals()));
	addPlayNoMinutes("Interchanges Used: " + to_string(m_HomeTeam.getInterchanges()) + "/8");
	addPlayNoMinutes("                             ");
	addPlayNoMinutes("Away Team: " + m_AwayTeam.getName());
	addPlayNoMinutes("Total Metres: " + to_string(m_AwayTeam.totalMetres()));
	addPlayNoMinutes("Total Kick Metres: " + to_string(m_AwayTeam.totalKickMetres()));
	addPlayNoMinutes("Total Errors: " + to_string(m_AwayTeam.totalErrors()));
	addPlayNoMinutes("Total Tackles: " + to_string(m_AwayTeam.totalTackles()));
	addPlayNoMinutes("Total Tries: " + to_string(m_AwayTeam.totalTries()));
	addPlayNoMinutes("Total Goals: " + to_string(m_AwayTeam.totalGoals()));
	addPlayNoMinutes("Total Field Goals: " + to_string(m_AwayTeam.totalFieldGoals()));
	addPlayNoMinutes("Interchanges Used: " + to_string(m_AwayTeam.getInterchanges()) + "/8");
	addPlayNoMinutes("                             ");
	addPlayNoMinutes("----------DALLY M-----------");
	int temp1 = 0;
	string player1 = "";
	int temp2 = 0;
	string player2 = "";
	int temp3 = 0;
	string player3 = "";
	for (int i = 0; i < 13; i++)
	{
		if (m_HomeTeam.getPlayers()[i].getDallyMPointsWorth() > temp1)
		{
			temp3 = temp2;
			player3 = player2;
			temp2 = temp1;
			player2 = player1;
			temp1 = m_HomeTeam.getPlayers()[i].getDallyMPointsWorth();
			player1 = m_HomeTeam.getPlayers()[i].getName();
		}
		else if (m_HomeTeam.getPlayers()[i].getDallyMPointsWorth() > temp2)
		{
			temp3 = temp2;
			player3 = player2;
			temp2 = m_HomeTeam.getPlayers()[i].getDallyMPointsWorth();
			player2 = m_HomeTeam.getPlayers()[i].getName();
		}
		else if (m_HomeTeam.getPlayers()[i].getDallyMPointsWorth() > temp3)
		{
			temp3 = m_HomeTeam.getPlayers()[i].getDallyMPointsWorth();
			player3 = m_HomeTeam.getPlayers()[i].getName();
		}

		if (m_AwayTeam.getPlayers()[i].getDallyMPointsWorth() > temp1)
		{
			temp3 = temp2;
			player3 = player2;
			temp2 = temp1;
			player2 = player1;
			temp1 = m_AwayTeam.getPlayers()[i].getDallyMPointsWorth();
			player1 = m_AwayTeam.getPlayers()[i].getName();
		}
		else if (m_AwayTeam.getPlayers()[i].getDallyMPointsWorth() > temp2)
		{
			temp3 = temp2;
			player3 = player2;
			temp2 = m_AwayTeam.getPlayers()[i].getDallyMPointsWorth();
			player2 = m_AwayTeam.getPlayers()[i].getName();
		}
		else if (m_AwayTeam.getPlayers()[i].getDallyMPointsWorth() > temp3)
		{
			temp3 = m_AwayTeam.getPlayers()[i].getDallyMPointsWorth();
			player3 = m_AwayTeam.getPlayers()[i].getName();
		}
	}
	addPlayNoMinutes("1st (3 Points) -- " + player1);
	addPlayNoMinutes("2nd (2 Points) -- " + player2);
	addPlayNoMinutes("3rd (1 Point) -- " + player3);
	addPlayNoMinutes("----------------------------");
}

void SRLGameManager::play()
{
	//DO WE DO AN INTERCHANGE
	if ((m_SecondsPassed % 10 == 0 || m_MinutesPassed % 10 <= 1)  && m_MinutesPassed > 5)
	{
		int interchangeHomeTeam = (rand() % 50) + 1;
		int interchangeAwayTeam = (rand() % 50) + 1;

		if (interchangeHomeTeam > 40)
		{
			string swap = m_HomeTeam.Interchange();
			if (swap != "")
			{
				addPlay(swap);
			}
		}

		if (interchangeAwayTeam > 40)
		{
			string swap = m_AwayTeam.Interchange();
			if (swap != "")
			{
				addPlay(swap);
			}
		}
	}

	//CALLED EVERY SECOND
	int timeSecondSkip = minTimeSecondSkip + (rand() % (maxTimeSecondSkip - minTimeSecondSkip));
	m_SecondsPassed += timeSecondSkip;
	m_HomeTeam.addTimeOnField(timeSecondSkip);
	m_AwayTeam.addTimeOnField(timeSecondSkip);
	if (m_SecondsPassed >= 60)
	{
		m_SecondsPassed -= 60;
		m_MinutesPassed++;
		if (m_MinutesPassed >= 40 && halfTimeHasPassed == false)
		{
			halfTimeHasPassed = true;
			m_PlayByPlay.push_back("40:00 - HALF TIME - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore));
			m_BallPosition = 0;
			m_HomeTeamHasBall = false;
			m_Tackle = 0;
			return;
		}
	}
	SRLPlayer defender = m_AwayTeam.getRandomPlayer();
	SRLPlayer attacker = m_HomeTeam.getRandomPlayer();
	if (!m_HomeTeamHasBall)
	{
		defender = m_HomeTeam.getRandomPlayer();
		attacker = m_AwayTeam.getRandomPlayer();
	}

	//MOVEMENT
	doRegularMovement(defender, attacker);

	//CHECK FOR ERRORS
	if (checkError(defender, attacker))
	{
		return;
	}

	//CHANCE FOR INTERCEPT
	if (checkIntercept(defender, attacker))
	{
		addPlay("Intercepted Off A " + attacker.getName() + " Pass", defender);
		attacker = defender;
		if (m_HomeTeamHasBall)
		{
			defender = m_AwayTeam.getRandomPlayer();
		}
		else
		{
			defender = m_HomeTeam.getRandomPlayer();
		}
	}
	//CHANCE FOR STRIP
	else
	{
		int strip = checkStrip(defender, attacker);
		//SUCCESS
		if (strip == 0)
		{
			addPlay("Stripped Ball Off " + attacker.getName(), defender);
			attacker = defender;
			if (m_HomeTeamHasBall)
			{
				defender = m_AwayTeam.getRandomPlayer();
			}
			else
			{
				defender = m_HomeTeam.getRandomPlayer();
			}
		}
		//PENALTY
		else if (strip == 2)
		{
			return;
		}
	}

	if (doFieldGoal(defender, attacker))
	{
		return;
	}
	else
	{
		int kick = checkKick(defender, attacker);
		//SUCCESS
		if (kick == 1)
		{
			return;
		}
		else if (kick == 2)
		{
			attacker = defender;
			if (m_HomeTeamHasBall)
			{
				defender = m_AwayTeam.getRandomPlayer();
			}
			else
			{
				defender = m_HomeTeam.getRandomPlayer();
			}
		}
	}
	//END OF SET, CHANGEOVER
	if (m_Tackle == 6)
	{
		addPlay("6th Tackle Changeover", attacker);
		changeOver(false);
		return;
	}
	//CHECK FOR POINTS
	else if (doTry(defender, attacker))
	{
		return;
	}
	
}

bool SRLGameManager::checkError(SRLPlayer defender, SRLPlayer attacker)
{
	int atkError1 = (rand() % defaultAttackErrorChance);
	int defError1 = (rand() % defaultDefenceErrorChance);
	if (atkError1 > attacker.getAttack())
	{
		//1 in 4 chance of error
		int atkError2 = (rand() % secondaryErrorChance);
		if (atkError2 == 0)
		{
			addPlay("Knock On", attacker);
			if (m_HomeTeamHasBall)
			{
				m_HomeTeam.addPlayerError(attacker.getName());
			}
			else
			{
				m_AwayTeam.addPlayerError(attacker.getName());
			}
			changeOver(true);
			return true;
		}
		//1 in 4 chance of error
		int atkError3 = (rand() % secondaryErrorChance);
		if (atkError3 == 0)
		{
			addPlay("Over The Sideline", attacker);
			if (m_HomeTeamHasBall)
			{
				m_HomeTeam.addPlayerError(attacker.getName());
			}
			else
			{
				m_AwayTeam.addPlayerError(attacker.getName());
			}
			changeOver(false);
			return true;
		}
		int atkError4 = (rand() % secondaryErrorChance);
		if (atkError4 == 0)
		{
			addPlay("Forward Pass", attacker);
			if (m_HomeTeamHasBall)
			{
				m_HomeTeam.addPlayerError(attacker.getName());
			}
			else
			{
				m_AwayTeam.addPlayerError(attacker.getName());
			}
			changeOver(false);
			return true;
		}
	}
	else if (defError1 > defender.getDefence())
	{
		//1 in 4 chance of error
		int defError2 = (rand() % secondaryErrorChance);
		if (defError2 == 0)
		{
			addPlay("Ruck Infringement", defender);
			if (!m_HomeTeamHasBall)
			{
				m_HomeTeam.addPlayerError(defender.getName());
			}
			else
			{
				m_AwayTeam.addPlayerError(defender.getName());
			}
			m_Tackle = 0;
			//changeOver(true);
		}
		//1 in 4 chance of error
		int defError3 = (rand() % secondaryErrorChance);
		if (defError3 != 0 && defError2 == 0)
		{
			return true;
		}
		if (defError3 == 0)
		{
			doPenalty(defender, attacker);
			return true;
		}
	}
	return false;
}

int SRLGameManager::checkKick(SRLPlayer defender, SRLPlayer attacker)
{
	if (m_Tackle < 4)
	{
		return 0;
	}
	if (m_HomeTeamHasBall)
	{
		if (m_BallPosition > 40)
		{
			int chanceKick = rand() % defaultEarlyKickChance;
			if (chanceKick == 0 || m_Tackle == 5)
			{
				return doKick(defender, attacker);
			}
		}
	}
	else
	{
		if (m_BallPosition < 60)
		{
			int chanceKick = rand() % defaultEarlyKickChance;
			if (chanceKick == 0 || m_Tackle == 5)
			{
				return doKick(defender, attacker);
			}
		}
	}
	return 0;
}

int SRLGameManager::doKick(SRLPlayer defender, SRLPlayer attacker)
{
	int chanceKick = rand() % fortytwentyChance;
	if (m_HomeTeamHasBall)
	{
		int kickDistance = 10 + (((rand() % (attacker.getAttack() + attacker.getSpeed() + 1)) / 2.5f));
		int originalPos = m_BallPosition;
		m_HomeTeam.addPlayerKickMetres(attacker.getName(), kickDistance);
		m_HomeTeam.addPlayerKick(attacker.getName());
		m_BallPosition -= kickDistance;
		if (m_BallPosition < -10)
		{
			addPlay("20m Restart - " + m_AwayTeam.getName());
			m_BallPosition = 20;
			changeOver(true);
			return 1;
		}
		else if (originalPos > 60 && m_BallPosition < 20 && m_BallPosition > 0 && chanceKick == 0)
		{
			addPlay("40/20", attacker);
			m_HomeTeam.addPlayer4020(attacker.getName());
			m_BallPosition = 20;
			m_Tackle = 0;
			return 1;
		}
		else
		{
			changeOver(false);
			return 2;
		}
	}
	else 
	{
		int kickDistance = 10 + (((rand() % (attacker.getAttack() + attacker.getSpeed() + 1)) / 2.5f));
		int originalPos = m_BallPosition;
		m_AwayTeam.addPlayerKickMetres(attacker.getName(), kickDistance);
		m_AwayTeam.addPlayerKick(attacker.getName());
		m_BallPosition += kickDistance;
		if (m_BallPosition > 110)
		{
			addPlay("20m Restart - " + m_HomeTeam.getName());
			m_BallPosition = 80;
			changeOver(true);
			return 1;
		}
		else if (originalPos < 40 && m_BallPosition > 80 && m_BallPosition < 100 && chanceKick == 0)
		{
			addPlay("40/20", attacker);
			m_AwayTeam.addPlayer4020(attacker.getName());
			m_BallPosition = 20;
			m_Tackle = 0;
			return 1;
		}
		else
		{
			changeOver(false);
			return 2;
		}
	}
	return 0;
}

void SRLGameManager::doRegularMovement(SRLPlayer defender, SRLPlayer attacker)
{
	if (m_HomeTeamHasBall)
	{
		if (attacker.getAttack() > defender.getDefence())
		{
			int metres = ((rand() % (attacker.getAttack() - defender.getDefence())) + ((attacker.getSpeed() / 20) + 1)) / 2;
			m_HomeTeam.addPlayerMetres(attacker.getName(), metres);
			m_BallPosition -= metres;
		}
		else
		{
			int metres = (((attacker.getSpeed() / 20) + 1)) / 2;
			m_HomeTeam.addPlayerMetres(attacker.getName(), metres);
			m_BallPosition -= metres;
		}
		m_AwayTeam.addPlayerTackle(defender.getName());
	}
	else
	{
		if (attacker.getAttack() > defender.getDefence())
		{
			int metres = ((rand() % (attacker.getAttack() - defender.getDefence())) + ((attacker.getSpeed() / 20) + 1)) / 2;
			m_AwayTeam.addPlayerMetres(attacker.getName(), metres);
			m_BallPosition += metres;
		}
		else
		{
			int metres = (((attacker.getSpeed() / 20) + 1)) / 2;
			m_AwayTeam.addPlayerMetres(attacker.getName(), metres);
			m_BallPosition += metres;
		}
		m_HomeTeam.addPlayerTackle(defender.getName());
	}
	m_Tackle++;
}

bool SRLGameManager::checkIntercept(SRLPlayer defender, SRLPlayer attacker)
{
	if (defender.getAttack() > attacker.getDefence())
	{
		int chance1 = defender.getSpeed() - attacker.getAttack();
		int chance2 = rand() % defaultStealChance;
		if (chance1 > chance2)
		{
			changeOver(false);
			attacker = defender;
			if (m_HomeTeamHasBall)
			{
				m_HomeTeam.addPlayerIntercept(attacker.getName());
				defender = m_AwayTeam.getRandomPlayer();
				if (attacker.getAttack() > defender.getDefence())
				{
					m_BallPosition -= ((rand() % (attacker.getAttack() - defender.getDefence())) + ((attacker.getSpeed() / 20) + 1)) / 2;
				}
				else
				{
					m_BallPosition -= (((attacker.getSpeed() / 20) + 1)) / 2;
				}
			}
			else
			{
				m_AwayTeam.addPlayerIntercept(attacker.getName());
				defender = m_HomeTeam.getRandomPlayer();
				if (attacker.getAttack() > defender.getDefence())
				{
					m_BallPosition += ((rand() % (attacker.getAttack() - defender.getDefence())) + ((attacker.getSpeed() / 20) + 1)) / 2;
				}
				else
				{
					m_BallPosition += (((attacker.getSpeed() / 20) + 1)) / 2;
				}
			}
			m_Tackle++;
			return true;
		}
	}
	return false;
}

int SRLGameManager::checkStrip(SRLPlayer defender, SRLPlayer attacker)
{
	if (defender.getDefence() > attacker.getAttack())
	{
		int chance1 = defender.getDefence() - attacker.getAttack();
		int chance2 = rand() % defaultStealChance;
		if (chance1 > chance2)
		{
			int chance3 = rand() % secondaryStripChance;
			//SUCCESS
			if (chance3 == 0)
			{
				if (!m_HomeTeamHasBall)
				{
					m_HomeTeam.addPlayerStrip(defender.getName());
				}
				else
				{
					m_AwayTeam.addPlayerStrip(defender.getName());
				}
				changeOver(false);
				return 0;
			}
			//PENALTY
			if (chance3 == 1)
			{
				doPenalty(defender, attacker);
				return 2;
			}
		}
	}
	return 1;
}

bool SRLGameManager::doFieldGoal(SRLPlayer defender, SRLPlayer attacker)
{
	if (m_MinutesPassed > 50)
	{
		if ((m_Tackle == 5 && ((homeTeamScore - awayTeamScore >= 0 && (homeTeamScore - awayTeamScore) % 6 == 0) || homeTeamScore - awayTeamScore == -1)) || homeTeamScore == awayTeamScore)
		{
			if (m_BallPosition < 30 && m_BallPosition > 0 && m_HomeTeamHasBall)
			{
				int chance1 = attacker.getAttack();
				int chance2 = rand() % defaultGoalChance;
				if (chance1 > chance2)
				{
					homeTeamScore += 1;
					addPlay("FIELD GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
					m_BallPosition = 100;
					m_HomeTeam.addPlayerFieldGoal(attacker.getName());
				}
				else
				{
					addPlay("FIELD GOAL MISSED", attacker);
					addPlay("20m Restart - " + m_AwayTeam.getName());
					m_BallPosition = 20;
					changeOver(true);
				}
				m_Tackle = 0;
				return true;
			}
		}
		else if ((m_Tackle == 5 && ((awayTeamScore - homeTeamScore >= 0 && (awayTeamScore - homeTeamScore) % 6 == 0) || awayTeamScore - homeTeamScore == -1)) || homeTeamScore == awayTeamScore)
		{
			if (m_BallPosition > 70 && m_BallPosition < 100 && !m_HomeTeamHasBall)
			{
				int chance1 = attacker.getAttack();
				int chance2 = rand() % defaultGoalChance;
				if (chance1 > chance2)
				{
					awayTeamScore += 1;
					addPlay("FIELD GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
					m_BallPosition = 0;
					m_AwayTeam.addPlayerFieldGoal(attacker.getName());
				}
				else
				{
					addPlay("FIELD GOAL MISSED", attacker);
					addPlay("20m Restart - " + m_HomeTeam.getName());
					m_BallPosition = 80;
					changeOver(true);
				}
				m_Tackle = 0;
				return true;
			}
		}
	}
	return false;
}

bool SRLGameManager::doTry(SRLPlayer defender, SRLPlayer attacker)
{
	if (m_BallPosition < 0 && m_HomeTeamHasBall)
	{
		int chance1 = rand() % tryVideoRefChance;
		if (chance1 == 0 || m_MinutesPassed > 77 || (m_MinutesPassed > 70 && homeTeamScore == awayTeamScore))
		{
			addPlay("------VIDEO REFEREE------");
			int chance2 = rand() % tryErrorChance;
			//KNOCK ON
			if (chance2 == 0)
			{
				addPlay("NO TRY - Knock On", attacker);
				changeOver(true);
				return true;
			}
			//HELD UP
			else if (chance2 == 1)
			{
				addPlay("NO TRY - Held Up", attacker);
				m_BallPosition = 10;
				return true;
			}
			//PENALTY
			else if (chance2 == 2)
			{
				addPlay("NO TRY - Obstruction", attacker);
				m_BallPosition = 10;
				changeOver(false);
				defender = attacker;
				attacker = m_AwayTeam.getRandomPlayer();
				doPenalty(defender, attacker);
				return true;
			}
			else if (chance2 == 3)
			{
				addPlay("NO TRY - Offside", attacker);
				m_BallPosition = 10;
				changeOver(false);
				defender = attacker;
				attacker = m_AwayTeam.getRandomPlayer();
				doPenalty(defender, attacker);
				return true;
			}
			//20m RESTART
			else if (chance2 == 4)
			{
				addPlay("NO TRY - 20m Restart", attacker);
				m_BallPosition = 20;
				changeOver(true);
				return true;
			}
			//DropPut
			else if (chance2 == 5)
			{
				addPlay("NO TRY - Goal Line Dropout", attacker);
				m_BallPosition = 50;
				m_Tackle = 0;
				return true;
			}
		}
		homeTeamScore += 4;
		addPlay("TRY - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
		m_HomeTeam.addPlayerTry(attacker.getName());
		m_MinutesPassed++;
		m_HomeTeam.addTimeOnField(60);
		m_AwayTeam.addTimeOnField(60);
		if (!halfTimeHasPassed && m_MinutesPassed >= 40)
		{
			m_MinutesPassed = 40;
			m_SecondsPassed = 0;
		}
		int goal1 = (rand() % defaultGoalChance);
		if (goal1 < attacker.getAttack())
		{
			//1 in 4 chance of error
			int goal2 = (rand() % conversionErrorChance);
			if (goal2 != 0)
			{
				homeTeamScore += 2;
				addPlay("GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
				m_HomeTeam.addPlayerGoal(attacker.getName());
			}
			else
			{
				addPlay("CONVERSION MISSED", attacker);
			}
		}
		else
		{
			addPlay("CONVERSION MISSED", attacker);
		}
		m_MinutesPassed++;
		m_HomeTeam.addTimeOnField(60);
		m_AwayTeam.addTimeOnField(60);
		if (m_MinutesPassed >= 40 && halfTimeHasPassed == false)
		{
			halfTimeHasPassed = true;
			m_PlayByPlay.push_back("40:00 - HALF TIME - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore));
			m_BallPosition = 0;
			m_HomeTeamHasBall = false;
			m_Tackle = 0;
			return true;
		}
		m_BallPosition = 100;
		m_Tackle = 0;
	}
	//CHECK FOR POINTS
	else if (m_BallPosition > 100 && !m_HomeTeamHasBall)
	{
		int chance1 = rand() % tryVideoRefChance;
		if (chance1 == 0 || m_MinutesPassed > 77 || (m_MinutesPassed > 70 && homeTeamScore == awayTeamScore))
		{
			addPlay("------VIDEO REFEREE------");
			int chance2 = rand() % tryErrorChance;
			//KNOCK ON
			if (chance2 == 0)
			{
				addPlay("NO TRY - Knock On", attacker);
				changeOver(true);
				return true;
			}
			//HELD UP
			else if (chance2 == 1)
			{
				addPlay("NO TRY - Held Up", attacker);
				m_BallPosition = 90;
				return true;
			}
			//PENALTY
			else if (chance2 == 2)
			{
				addPlay("NO TRY - Obstruction", attacker);
				m_BallPosition = 90;
				changeOver(false);
				defender = attacker;
				attacker = m_HomeTeam.getRandomPlayer();
				doPenalty(defender, attacker);
				return true;
			}
			else if (chance2 == 3)
			{
				addPlay("NO TRY - Offside", attacker);
				m_BallPosition = 90;
				changeOver(false);
				defender = attacker;
				attacker = m_HomeTeam.getRandomPlayer();
				doPenalty(defender, attacker);
				return true;
			}
			//20m RESTART
			else if (chance2 == 4)
			{
				addPlay("NO TRY - 20m Restart", attacker);
				m_BallPosition = 80;
				changeOver(true);
				return true;
			}
			//DropPut
			else if (chance2 == 5)
			{
				addPlay("NO TRY - Goal Line Dropout", attacker);
				m_BallPosition = 50;
				m_Tackle = 0;
				return true;
			}
		}
		awayTeamScore += 4;
		addPlay("TRY - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
		m_AwayTeam.addPlayerTry(attacker.getName());
		m_MinutesPassed++;
		m_HomeTeam.addTimeOnField(60);
		m_AwayTeam.addTimeOnField(60);
		if (!halfTimeHasPassed && m_MinutesPassed >= 40)
		{
			m_MinutesPassed = 40;
			m_SecondsPassed = 0;
		}
		int goal1 = (rand() % defaultGoalChance);
		if (goal1 < attacker.getAttack())
		{
			//1 in 4 chance of error
			int goal2 = (rand() % conversionErrorChance);
			if (goal2 != 0)
			{
				awayTeamScore += 2;
				addPlay("GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
				m_AwayTeam.addPlayerGoal(attacker.getName());
			}
			else
			{
				addPlay("CONVERSION MISSED", attacker);
			}
		}
		else
		{
			addPlay("CONVERSION MISSED", attacker);
		}
		m_MinutesPassed++;
		m_HomeTeam.addTimeOnField(60);
		m_AwayTeam.addTimeOnField(60);
		if (m_MinutesPassed >= 40 && halfTimeHasPassed == false)
		{
			halfTimeHasPassed = true;
			m_PlayByPlay.push_back("40:00 - HALF TIME - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore));
			m_BallPosition = 0;
			m_HomeTeamHasBall = false;
			m_Tackle = 0;
			return true;
		}
		m_BallPosition = 0;
		m_Tackle = 0;
	}
	return false;
}

void SRLGameManager::doPenalty(SRLPlayer defender, SRLPlayer attacker)
{
	addPlay("Penalty", defender);
	m_Tackle = 0;
	if (m_HomeTeamHasBall)
	{
		m_AwayTeam.addPlayerError(defender.getName());
		if (m_BallPosition < 30 && (homeTeamScore - awayTeamScore) > -3)
		{
			//1 in 4 chance of error
			int goal = (rand() % conversionErrorChance);
			if (goal != 0)
			{
				homeTeamScore += 2;
				addPlay("PENALTY GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
				m_HomeTeam.addPlayerGoal(attacker.getName());
				m_BallPosition = 100;
			}
			else
			{
				addPlay("PENALTY GOAL MISSED", attacker);
				m_BallPosition = 50;
			}
			m_MinutesPassed++;
			m_HomeTeam.addTimeOnField(60);
			m_AwayTeam.addTimeOnField(60);
			if (!halfTimeHasPassed && m_MinutesPassed >= 40)
			{
				m_MinutesPassed = 40;
				m_SecondsPassed = 0;
			}
		}
		else if (m_BallPosition < 30)
		{
			m_BallPosition = 10;
		}
		else
		{
			m_BallPosition -= 30;
		}
	}
	else
	{
		m_HomeTeam.addPlayerError(defender.getName());
		if (m_BallPosition > 70 && (awayTeamScore - homeTeamScore) > -3)
		{
			//1 in 4 chance of error
			int goal = (rand() % conversionErrorChance);
			if (goal != 0)
			{
				awayTeamScore += 2;
				addPlay("PENALTY GOAL - " + m_HomeTeam.getName() + ": " + to_string(homeTeamScore) + " v " + m_AwayTeam.getName() + ": " + to_string(awayTeamScore), attacker);
				m_AwayTeam.addPlayerGoal(attacker.getName());
				m_BallPosition = 0;
			}
			else
			{
				addPlay("PENALTY GOAL MISSED", attacker);
				m_BallPosition = 50;
			}
			m_MinutesPassed++;
			m_HomeTeam.addTimeOnField(60);
			m_AwayTeam.addTimeOnField(60);
			if (!halfTimeHasPassed && m_MinutesPassed >= 40)
			{
				m_MinutesPassed = 40;
				m_SecondsPassed = 0;
			}
		}
		else if (m_BallPosition > 70)
		{
			m_BallPosition = 90;
		}
		else
		{
			m_BallPosition += 30;
		}
	}
}


void SRLGameManager::changeOver(bool error)
{
	if (error)
	{
		m_Tackle = -1;
	}
	else
	{
		m_Tackle = 0;
	}
	m_HomeTeamHasBall = !m_HomeTeamHasBall;
}
