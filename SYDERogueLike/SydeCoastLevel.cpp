#include "SydeCoastLevel.h"

void SydeCoastLevel::doBossAction(MapSpace currentSpace)
{
	int BossTag = m_CfgObj.getBossTagAtPos(currentSpace.getPathNumber(), currentSpace.getSpaceNumber());
	m_BossTag = BossTag;
	if (BossTag == 0)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\SmokingCrab.bmp", 300, 120, 30, 20, 0, 65));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SmokingCrab(5)));
		return;
	}
	else if (BossTag == 1)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\SlimeKeeperCutscene.bmp", 300, 220, 30, 20, 0, 110));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SlimeKeeper(5)));
		return;
	}
}

void SydeCoastLevel::doBossDefeatedAction()
{
	if (m_BossTag == 0)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\SmokingCrabDeathCutscene.bmp", 150, 320, 30, 20, 0, 80));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	else if (m_BossTag == 1)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\DefaultBossWin.bmp", 150, 40, 30, 20, 0, 10));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	HideUI();
}

void SydeCoastLevel::generateEnemy()
{
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new OrcEnemy(5)));
}
