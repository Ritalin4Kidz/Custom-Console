#include "CharacterSelectScene.h"


bool  CharacterSelectScene::nextCharCall = false;
 bool  CharacterSelectScene::prevCharCall = false;
 bool  CharacterSelectScene::startGameCall = false;

void startGameClick()
{
	CharacterSelectScene::CallStartGame();
}

void nextCharClick()
{
	CharacterSelectScene::CallNextChar();
}

void prevCharClick()
{
	CharacterSelectScene::CallPrevChar();
}

ConsoleWindow CharacterSelectScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (nextCharCall)
	{
		nextCharCall = false;
		m_SelectedPlayer++;
		if (m_SelectedPlayer >= m_PlayersVec.size())
		{
			m_SelectedPlayer = 0;
		}
	}
	if (prevCharCall)
	{
		prevCharCall = false;
		m_SelectedPlayer--;
		if (m_SelectedPlayer < 0)
		{
			m_SelectedPlayer = m_PlayersVec.size() - 1;
		}
	}
	if (startGameCall)
	{
		//TODO: SHOW A POPUP
		startGameCall = false;
		//SydeRogueLikeStatics::toggleInitMap(true);
		SydeRogueLikeStatics::setSceneTag("Level Select Scene");
		SydeRogueLikeStatics::setPlayer(std::shared_ptr<Player>(TagToPlayer::getNewFromString(5,m_PlayersVec[m_SelectedPlayer].getTag())));
		return window;
	}

	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window = m_Spotlight.draw_asset(window, Vector2(22, 1));
	for (int i = 0; i < windowWidth; i++)
	{

		window.setTextAtPoint(Vector2(i, 19), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	}
	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTGREY_LIGHTGREY_BG);
		}
	}
	window = m_PlayersVec[m_SelectedPlayer].getImg().draw_asset(window, Vector2(32,10));

	window.setTextAtPoint(Vector2(0, 1), "CHARACTER:", BLACK_LIGHTGREY_BG);
	window.setTextAtPoint(Vector2(0, 2), m_PlayersVec[m_SelectedPlayer].getTag(), BLACK_LIGHTGREY_BG);

	window.setTextAtPoint(Vector2(0, 7), "RATING: ", BLACK_LIGHTGREY_BG);
	for (int i = 0; i < m_PlayersVec[m_SelectedPlayer].getRating(); i++)
	{
		window.setTextAtPoint(Vector2(i + 1, 8), "|", RED_LIGHTGREY_BG);
	}

	return window;
}

void CharacterSelectScene::onNewScene()
{
	m_PlayersVec = std::vector<PlayerSelectObject>(
		{
			PlayerSelectObject(2, "Furi", L"EngineFiles\\CharacterBMPS\\Furi.bmp"),
			PlayerSelectObject(2, "Alison",L"EngineFiles\\CharacterBMPS\\Alison.bmp"),
			PlayerSelectObject(2, "Bruce", L"EngineFiles\\CharacterBMPS\\Bruce.bmp"),
			PlayerSelectObject(3, "Jordan", L"EngineFiles\\CharacterBMPS\\Jordan.bmp"),
			PlayerSelectObject(2, "Fuego", L"EngineFiles\\CharacterBMPS\\Fuego.bmp")
		});
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"   SELECT CHAR    ",
		Vector2(31, 19),
		Vector2(18, 1),
		BRIGHTWHITE_BRIGHTGREEN_BG,
		NULLCOLOUR,
		false,
		startGameClick,
		"StartGameLabel",
		"StartGameLabel"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"<<",
		Vector2(27, 19),
		Vector2(2, 1),
		BRIGHTWHITE_BRIGHTGREEN_BG,
		NULLCOLOUR,
		false,
		prevCharClick,
		"PrevCharLabel",
		"PrevCharLabel"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		">>",
		Vector2(51, 19),
		Vector2(2, 1),
		BRIGHTWHITE_BRIGHTGREEN_BG,
		NULLCOLOUR,
		false,
		nextCharClick,
		"NextCharLabel",
		"NextCharLabel"
	)));
}

void CharacterSelectScene::destroyScene()
{
	m_PlayersVec.clear();
}
