#include "Scene.h"
_SQScene GameScene::m_SceneTag = MainMenu;
_SQScene GameScene::m_SceneTag_Previous = UnknownScene;
void GameScene::SetScene(_SQScene _SceneTag)
{
	m_SceneTag = _SceneTag;
}

void GameScene::SetScenePrev(_SQScene _SceneTag)
{
	m_SceneTag_Previous = _SceneTag;
}
