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
	return window;
}
