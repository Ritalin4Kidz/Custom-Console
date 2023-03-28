#include "SydeRoguelikeMainControl.h"

bool SYDERogueLikeMainControl::exitGameCall = false;

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
		mainScene = nullptr;
	}
	if (SydeRogueLikeStatics::getSceneTag() == "Exit Game")
	{
		exitGameCall = true;
		return;
	}
	if (SydeRogueLikeStatics::getSceneTag() == "Battle Scene")
	{
		mainScene = std::shared_ptr<GameScene>(new BattleScene());
		mainScene->onNewScene();
		return;
	}
	else if (SydeRogueLikeStatics::getSceneTag() == "Shop Scene")
	{
		mainScene = std::shared_ptr<GameScene>(new ShopScene());
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
