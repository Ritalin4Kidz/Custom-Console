#include "SRL.h"
GameStateSYDE SRLGame::currentState = Unknown_STATE;
GameStateSYDE SRLGame::newState = MainMenu_STATE;

bool SRLGame::SeasonStart = false;

void ExhibitionMatchClick()
{
	if (SRLGame::currentState = MainMenu_STATE)
	{
		SRLGame::newState = Exhibition_LoadState;
	}
}

void SeasonModeClick()
{
	if (SRLGame::currentState == MainMenu_STATE)
	{
		SRLGame::newState = SeasonConfig_State;
	}
	if (SRLGame::currentState == SeasonConfig_State)
	{
		SRLGame::SeasonStart = true;
	}
}

void SRLGame::init()
{
	test();
	m_ExhibitionMatchBtn = SYDEClickableButton("Exhibition", Vector2(0, 3), Vector2(10, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ExhibitionMatchBtn.setHighLight(RED);
	m_ExhibitionMatchBtn.SetFunc(ExhibitionMatchClick);

	m_SeasonModeBtn = SYDEClickableButton("Season Mode", Vector2(0, 4), Vector2(11, 1), BLACK_BRIGHTWHITE_BG, false);
	m_SeasonModeBtn.setHighLight(RED);
	m_SeasonModeBtn.SetFunc(SeasonModeClick);

	m_StartSeasonBtn = SYDEClickableButton("Start Season", Vector2(25, 19), Vector2(12, 1), BLACK_BRIGHTWHITE_BG, false);
	m_StartSeasonBtn.setHighLight(RED);
	m_StartSeasonBtn.SetFunc(SeasonModeClick);
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		m_Team.push_back(SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), rand() % 100, rand() % 100, rand() % 100));
	}
	return m_Team;
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix, float multiplier)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		m_Team.push_back(SRLPlayer(prefix + SRLNameGenerator::generateRandomName(), (rand() % 100) * multiplier, (rand() % 100) * multiplier, (rand() % 100) * multiplier));
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
	return SRLTeam(createRandomTeam(""), SRLNameGenerator::generateRandomTeamName());
}

SRLTeam SRLGame::generateRandomTeam(float multiplier)
{
	return SRLTeam(createRandomTeam("", multiplier), SRLNameGenerator::generateRandomTeamName());
}

ConsoleWindow SRLGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	if (newState != currentState)
	{
		currentState = newState;
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
		else if (currentState == SeasonConfig_State)
		{
			while (SYDEFileDefaults::getFileCount("EngineFiles\\GameResults\\Teams", ".json") < 17)
			{
				SRLTeam HomeTeam = generateRandomTeam();
				HomeTeam.saveTeam();
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

ConsoleWindow SRLGame::main_menu_scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window.setTextAtPoint(Vector2(0,1), "SYDE RUGBY LEAGUE", WHITE);
	window = m_ExhibitionMatchBtn.draw_ui(window);
	window = m_SeasonModeBtn.draw_ui(window);
	return window;
}

ConsoleWindow SRLGame::exhibition_match_settings(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return window;
}

ConsoleWindow SRLGame::season_config_settings(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (SeasonStart)
	{
		SeasonStart = false;

		//DO CONFIG IN HERE
		vector<SRLLadderPosition> ladders;
		for (int i = 0; i < m_SeasonTeams.size(); i++)
		{
			SRLLadderPosition newPosition;
			newPosition.teamName = m_SeasonTeams[i];
			ladders.push_back(newPosition);
		}
		SRLLadder Ladder = SRLLadder(ladders);
		vector<SRLRound> rounds;
		for (int i = 0; i < 26; i++)
		{
			vector<SRLGameMatchup> games;
			vector<string> AvailableTeams = m_SeasonTeams;
			for (int ii = 0; ii < 8; ii++)
			{
				int team1 = rand() % AvailableTeams.size();
				string team1Name = AvailableTeams[team1];
				AvailableTeams.erase(AvailableTeams.begin() + team1);
				int team2 = rand() % AvailableTeams.size();
				string team2Name = AvailableTeams[team2];
				AvailableTeams.erase(AvailableTeams.begin() + team2);
				games.push_back(SRLGameMatchup(team1Name, team2Name));
			}
			rounds.push_back(SRLRound(games));
		}
		SRLDraw Draw(rounds);
		m_Season = SRLSeason(Draw, Ladder);
		newState = SeasonModeState;

		return window;
	}


	window.setTextAtPoint(Vector2(0, 1), "SEASON CONFIG", WHITE);
	window.setTextAtPoint(Vector2(0, 2), m_SavedTeams[m_SelectedTeam], WHITE);
	window.setTextAtPoint(Vector2(0, 3), "TEAMS:", WHITE);
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		m_SelectedTeam++;
		if (m_SelectedTeam > m_SavedTeams.size() - 1)
		{
			m_SelectedTeam = 0;
		}
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		m_SelectedTeam--;
		if (m_SelectedTeam < 0)
		{
			m_SelectedTeam = m_SavedTeams.size() - 1;
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		if (m_SeasonTeams.size() < 16)
		{
			m_SeasonTeams.push_back(m_SavedTeams[m_SelectedTeam]);
			m_SavedTeams.erase(m_SavedTeams.begin() + m_SelectedTeam);
			if (m_SelectedTeam > m_SavedTeams.size() - 1)
			{
				m_SelectedTeam = 0;
			}
		}
	}
	if (m_SeasonTeams.size() == 16)
	{
		window = m_StartSeasonBtn.draw_ui(window);
	}

	for (int i = 0; i < m_SeasonTeams.size(); i++)
	{
		window.setTextAtPoint(Vector2(7, i + 3), m_SeasonTeams[i], WHITE);
	}

	return window;
}

ConsoleWindow SRLGame::season_mode(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//m_Season will contain all the data for the season
	//Grab the draw to determine the next game to play
	//after the game is complete, adjust the ladder with the new values
	// the ladder should be sorted by Points - P/D - Points For - Played - Alphabetical
	return window;
}
