#include "SRL.h"

void SRLGame::init()
{
	test();
}

vector<SRLPlayer> SRLGame::createRandomTeam(string prefix)
{
	vector<SRLPlayer> m_Team = vector<SRLPlayer>();
	for (int i = 0; i < 17; i++)
	{
		m_Team.push_back(SRLPlayer(prefix + "TestPlayer_" + to_string(i), rand() % 100, rand() % 100, rand() % 100));
	}
	return m_Team;
}

void SRLGame::test()
{
	SRLGameManager m_srlmanager;
	SRLTeam HomeTeam = SRLTeam(createRandomTeam("MD-"), "Mildews");
	SRLTeam AwayTeam = SRLTeam(createRandomTeam("HM-"), "Honey Magnets");
	m_srlmanager.setTeams(HomeTeam, AwayTeam);
	try
	{
		while (m_srlmanager.getMinutesPassed() < 80 || m_srlmanager.isTied())
		{
			m_srlmanager.play();
		}
	}
	catch (exception ex)
	{
		//TODO
	}
	m_srlmanager.endStats();

	std::ofstream output_file("EngineFiles\\GameResults\\MainGame.txt");
	for (const auto& e : m_srlmanager.getPlayByPlay()) output_file << e << "\n";
}

ConsoleWindow SRLGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return window;
}
