#include "ChallengeSelectScene.h"

int ChallengeSelectScene::selectedChallenge = 0;
ChallengeSelectSceneStates ChallengeSelectScene::m_SceneState = m_CSS_Normal;
bool ChallengeSelectScene::startChallengeCall = false;

void backMenuClick()
{
	SydeRogueLikeStatics::setSceneTag("Main Menu");
}

void challengeBtnClick()
{
	ChallengeSelectScene::m_SceneState = m_CSS_Details;
	ChallengeSelectScene::setSelectedChallengeInt(stoi(SYDEClickableButton::getLastButtonTag()));
}

void challengeStartClick()
{
	ChallengeSelectScene::initChallengeCall();
}

void backDetailsClick()
{
	ChallengeSelectScene::m_SceneState = m_CSS_Normal;
}



ConsoleWindow ChallengeSelectScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	if (m_SceneState == m_CSS_Details)
	{
		HideUI();
		if (startChallengeCall)
		{
			startChallengeCall = false;
			SydeRogueLikeStatics::toggleInitMap(true);
			SydeRogueLikeStatics::setSceneTag(m_LevelList[selectedChallenge].m_SceneTag);
			SydeRogueLikeStatics::setLevelSceneTag(m_LevelList[selectedChallenge].m_SceneTag);
			clearUI();
			ShowUI();
			return window;
		}
		for (int ii = 0; ii < m_LevelList[selectedChallenge].m_Desc.size(); ii++)
		{
			window.setTextAtPoint(Vector2(0, ii + 1), m_LevelList[selectedChallenge].m_Desc[ii], BRIGHTWHITE);
		}
		window = m_BackDtlsBtn.draw_ui(window);
		window = m_StartGameDtlsBtn.draw_ui(window);
	}
	else
	{
		ShowUI();
	}
	return window;
}

void ChallengeSelectScene::onNewScene()
{
	m_SceneState = m_CSS_Normal;
	startChallengeCall = false;
	std::vector<SYDEScrollViewerElement> tempVec = std::vector<SYDEScrollViewerElement>();

	m_LevelList = std::vector<ChallengeSelectObject>({
		ChallengeSelectObject("Challenge Map 001 Scene", ChallengeDescStatics::generateBaseDesc(), "Furi Of The Orcs"),
		ChallengeSelectObject("Challenge Map 002 Scene", ChallengeDescStatics::generateBaseDesc(), "Shopping Spree")
		});

	for (int i = 0; i < m_LevelList.size(); i++)
	{
		tempVec.push_back(SYDEScrollViewerElement(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			m_LevelList[i].m_DisplayTag,
			Vector2(0, i * 2),
			Vector2(45, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			challengeBtnClick,
			to_string(i),
			to_string(i)
		))));

	}


	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEScrollViewer(Vector2(6, 2), Vector2(48, 17), vector<SYDEScrollViewerElement>(
		{
			tempVec
		}),
		BLACK)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"Back To Menu",
		Vector2(0, 19),
		Vector2(12, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		backMenuClick,
		"SwapViewLBL",
		"SwapViewLBL"
	)));


	m_BackDtlsBtn = SYDEClickableButton(
		"Back To List",
		Vector2(0, 19),
		Vector2(12, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		backDetailsClick,
		"SwapViewLBL",
		"SwapViewLBL"
	);
	m_StartGameDtlsBtn = SYDEClickableButton(
		"Start Challenge",
		Vector2(45, 19),
		Vector2(15, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		challengeStartClick,
		"SwapViewLBL",
		"SwapViewLBL"
	);
}


std::vector<std::string> ChallengeDescStatics::generateBaseDesc()
{
	std::vector<std::string> tempVec = std::vector<std::string>();
	tempVec.push_back("Challenge 01: ------");
	return tempVec;
}