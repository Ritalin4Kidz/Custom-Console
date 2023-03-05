#include "SydeCoastLevel.h"

void SydeCoastLevel::doBossAction(MapSpace currentSpace)
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\SmokingCrab.bmp", 300, 120, 30, 20, 0, 65));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "Battle Scene";
	HideUI();
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SmokingCrab(5)));
	//TODO:
	/*
	WE NEED TO GENERATE THE BATTLE HERE
	THIS IS NOT FOR BOSS FIGHTS, WHICH WILL HAVE AN ENTIRELY DIFFERENT START ANIMATION REGARDLESS
	*/
}

void SydeCoastLevel::doBossDefeatedAction()
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\SmokingCrabDeathCutscene.bmp", 150, 320, 30, 20, 0, 80));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_END_UIAnimation;
	sceneLoad = "";
	HideUI();
}

void SydeCoastLevel::generateEnemy()
{
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new OrcEnemy(5)));
}
