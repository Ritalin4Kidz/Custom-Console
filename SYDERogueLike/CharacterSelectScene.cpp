#include "CharacterSelectScene.h"


bool  CharacterSelectScene::nextCharCall = false;
 bool  CharacterSelectScene::prevCharCall = false;
 bool  CharacterSelectScene::startGameCall = false;
 bool  CharacterSelectScene::showCharDetails = false;

void startGameClick()
{
	CharacterSelectScene::CallStartGame();
}

void backToMenuClick()
{
	SydeRogueLikeStatics::setSceneTag("Main Menu");
}

void nextCharClick()
{
	CharacterSelectScene::CallNextChar();
}

void prevCharClick()
{
	CharacterSelectScene::CallPrevChar();
}

void changeDetailsClick()
{
	CharacterSelectScene::ToggleCharDetails();
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
	if (!showCharDetails)
	{
		window = drawCharImg(window, windowWidth, windowHeight);
	}
	else
	{
		for (int ii = 0; ii < m_PlayersVec[m_SelectedPlayer].getDesc().size(); ii++)
		{
			window.setTextAtPoint(Vector2(22, ii + 1), m_PlayersVec[m_SelectedPlayer].getDesc()[ii], BRIGHTWHITE);
		}
	}
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
			PlayerSelectObject(2, "Furi", L"EngineFiles\\CharacterBMPS\\Furi.bmp", DesciptionStatics::generateFuriDesc()),
			PlayerSelectObject(2, "Alison",L"EngineFiles\\CharacterBMPS\\Alison.bmp", DesciptionStatics::generateAlisonDesc()),
			PlayerSelectObject(2, "Bruce", L"EngineFiles\\CharacterBMPS\\Bruce.bmp", DesciptionStatics::generateBruceDesc()),
			PlayerSelectObject(3, "Jordan", L"EngineFiles\\CharacterBMPS\\Jordan.bmp", DesciptionStatics::generateJordanDesc()),
			PlayerSelectObject(2, "Fuego", L"EngineFiles\\CharacterBMPS\\Fuego.bmp", DesciptionStatics::generateFuegoDesc())
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


	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		" Change View ",
		Vector2(3, 13),
		Vector2(14, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		changeDetailsClick,
		"SwapViewLBL",
		"SwapViewLBL"
	)));


	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Back To Menu",
		Vector2(0, 19),
		Vector2(13, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		backToMenuClick,
		"SwapViewLBL",
		"SwapViewLBL"
	)));
}

void CharacterSelectScene::destroyScene()
{
	m_PlayersVec.clear();
}

ConsoleWindow CharacterSelectScene::drawCharImg(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_Spotlight.draw_asset(window, Vector2(22, 1));
	window = m_PlayersVec[m_SelectedPlayer].getImg().draw_asset(window, Vector2(32, 10));
	return window;
}

std::vector<std::string> DesciptionStatics::generateFuriDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	//tempVec.push_back("--------------------------------------")
	tempVec.push_back("CASE FILE #114: Furi");
	tempVec.push_back("Furi ran away from home after at the");
	tempVec.push_back("age of 15 due to an incident that saw");
	tempVec.push_back("half her kitchen go up in flames.");
	tempVec.push_back("She joined the SYDE task force 3 years");
	tempVec.push_back("later involuntarily after court had");
	tempVec.push_back("sentenced her to community service for");
	tempVec.push_back("stealing, but decided to remain on the");
	tempVec.push_back("force after her time for the sake of");
	tempVec.push_back("employment. She's been good to us");
	tempVec.push_back("since, but you know what they say.");
	tempVec.push_back("Once a thief, always a thief.");
	return tempVec;
}

std::vector<std::string> DesciptionStatics::generateFuegoDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	//tempVec.push_back("--------------------------------------")
	tempVec.push_back("CASE FILE #39: Fuego");
	tempVec.push_back("Fuego seems to still think it's the");
	tempVec.push_back("renaissance or something. He keeps on");
	tempVec.push_back("and on and on about having to save the");
	tempVec.push_back("princess from a dragon, weird right?");
	tempVec.push_back("It's almost like he appeared from thin");
	tempVec.push_back("air, all we know is his name and we've");
	tempVec.push_back("found no records of him whatsoever. ");
	tempVec.push_back("What a weird man.");
	tempVec.push_back("");
	tempVec.push_back("I can't doubt the man knows his way");
	tempVec.push_back("around a sword though.");
	return tempVec;
}

std::vector<std::string> DesciptionStatics::generateBruceDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	//tempVec.push_back("--------------------------------------")
	tempVec.push_back("CASE FILE #8: Bruce");
	tempVec.push_back("Bruce joined the force back in '04. I");
	tempVec.push_back("have never met a man so dedicated as");
	tempVec.push_back("him in my life, yet he is forever");
	tempVec.push_back("insistent on 'doing things his own");
	tempVec.push_back("way'. I can't argue that the man gets");
	tempVec.push_back("results, but surely he would come home");
	tempVec.push_back("with less scars if he would put a god ");
	tempVec.push_back("damn shirt on at least.");
	return tempVec;
}

std::vector<std::string> DesciptionStatics::generateJordanDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	//tempVec.push_back("--------------------------------------")
	tempVec.push_back("CASE FILE #256: Jordan");
	tempVec.push_back("I once asked jordan to turn off the");
	tempVec.push_back("light in the room and she caused a");
	tempVec.push_back("blackout involuntarily. We went three");
	tempVec.push_back("days without power. I haven't talked");
	tempVec.push_back("to her much since.");
	return tempVec;
}

std::vector<std::string> DesciptionStatics::generateAlisonDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	//tempVec.push_back("--------------------------------------")
	tempVec.push_back("CASE FILE #81: Alison");
	tempVec.push_back("???");

	return tempVec;
}
