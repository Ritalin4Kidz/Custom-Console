#include "SydeRoguelikeMainControl.h"

void SYDERogueLikeMainControl::init()
{
	mainScene = m_ScenesList.at(0);
	mainScene->onNewScene();
	SydeRogueLikeStatics::setSceneTag(mainScene->GetSceneTag());
}

void SYDERogueLikeMainControl::initNewScene()
{
	mainScene->destroyScene();
	GameScene::clearUI();
	if (mainScene->getIsTransient())
	{
		delete mainScene;
	}
	if (SydeRogueLikeStatics::getSceneTag() == "Battle Scene")
	{
		mainScene = new BattleScene();
		mainScene->onNewScene();
		return;
	}
	else if (SydeRogueLikeStatics::getSceneTag() == "Shop Scene")
	{
		mainScene = new ShopScene();
		mainScene->onNewScene();
		return;
	}
	for (int i = 0; i < m_ScenesList.size(); i++)
	{
		if (m_ScenesList[i]->GetSceneTag() == SydeRogueLikeStatics::getSceneTag())
		{
			mainScene = m_ScenesList[i];
			mainScene->onNewScene();
			return;
		}
	}

	mainScene = m_ScenesList.at(0);
	mainScene->onNewScene();
	SydeRogueLikeStatics::setSceneTag(mainScene->GetSceneTag());
}

ConsoleWindow SYDERogueLikeMainControl::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (mainScene->GetSceneTag() != SydeRogueLikeStatics::getSceneTag())
	{
		initNewScene();
	}
	window = mainScene->window_draw(window, windowWidth, windowHeight);
	window = GameScene::drawUI(window);
	return window;
}
