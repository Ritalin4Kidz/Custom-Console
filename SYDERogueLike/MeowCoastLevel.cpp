#include "MeowCoastLevel.h"

void MeowCoastLevel::doBossAction(MapSpace currentSpace)
{

	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\FreebeeCutscene.bmp", 150, 280, 30, 20, 0, 70));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "Battle Scene";
	HideUI();
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FreebeeBoss(5)));
	//TODO:
	/*
	WE NEED TO GENERATE THE BATTLE HERE
	THIS IS NOT FOR BOSS FIGHTS, WHICH WILL HAVE AN ENTIRELY DIFFERENT START ANIMATION REGARDLESS
	*/
}

void MeowCoastLevel::doBossDefeatedAction()
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\FreebeeDeathCutscene.bmp", 210, 200, 30, 20, 0, 70));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_END_UIAnimation;
	sceneLoad = "";
	HideUI();
}

void MeowCoastLevel::generateEnemy()
{
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new BloodGhostEnemy(5)));
}
