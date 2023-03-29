#include "ChallengeSelectScene.h"

int ChallengeSelectScene::selectedChallenge = 0;

void backMenuClick()
{
	SydeRogueLikeStatics::setSceneTag("Main Menu");
}

void challengeBtnClick()
{
	ChallengeSelectScene::setSelectedChallengeInt(stoi(SYDEClickableButton::getLastButtonTag()));
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
	return window;
}

void ChallengeSelectScene::onNewScene()
{
	std::vector<SYDEScrollViewerElement> tempVec = std::vector<SYDEScrollViewerElement>();

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
}
