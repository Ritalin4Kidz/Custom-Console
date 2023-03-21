#include "MeowCoastLevel.h"

void MeowCoastLevel::doBossAction(MapSpace currentSpace)
{
	int BossTag =m_CfgObj.getBossTagAtPos(currentSpace.getPathNumber(), currentSpace.getSpaceNumber());
	m_BossTag = BossTag;
	if (BossTag == 0)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\GhostFishCutscene.bmp", 150, 460, 30, 20, 0, 115));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new GhostFish(5)));
		return;
	}
	else if (BossTag == 1)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\FreebeeCutscene.bmp", 150, 280, 30, 20, 0, 70));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FreebeeBoss(5)));
		return;
	}
	else if (BossTag == 2)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\DefaultBossCutscene.bmp", 150, 120, 30, 20, 0, 30));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new AliBoss(5)));
		return;
	}
	else if (BossTag == 3)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\DefaultBossCutscene.bmp", 150, 120, 30, 20, 0, 30));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_UIAnimation;
		sceneLoad = "Battle Scene";
		HideUI();
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FireSkeletonBoss(5)));
		return;
	}
}

void MeowCoastLevel::doBossDefeatedAction()
{
	if (m_BossTag == 0)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\GhostFishDeathCutscene.bmp", 150, 440, 30, 20, 0, 110));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	else if (m_BossTag == 1)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\FreebeeDeathCutscene.bmp", 210, 200, 30, 20, 0, 70));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	else if (m_BossTag == 2)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\DefaultBossWin.bmp", 150, 40, 30, 20, 0, 10));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	else if (m_BossTag == 3)
	{
		m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\DefaultBossWin.bmp", 150, 40, 30, 20, 0, 10));
		m_UIAnimation.setLooping(false);
		m_UIAnimation.setFrame(0);
		m_SceneState = MMS_END_UIAnimation;
		sceneLoad = "";
	}
	HideUI();
}

void MeowCoastLevel::generateEnemy(MapSpace currentSpace)
{
	int LevelAdditions = currentSpace.getSpaceNumber() / 10;
	int chanceSpawn = rand() % 100;
	if (currentSpace.getPathNumber() == 1)
	{
		int level = ((rand() % 3) + 4) + LevelAdditions; //(4-6) + LevelAdditions
		if (chanceSpawn >= 0 && chanceSpawn < 50)
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new BloodGhostEnemy(level)));
		}
		else
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FishEnemy(level)));
		}
	}
	else
	{
		int level = ((rand() % 3) + 4) + LevelAdditions; //(4-6) + LevelAdditions
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new WolfEnemy(level)));
	}
}
