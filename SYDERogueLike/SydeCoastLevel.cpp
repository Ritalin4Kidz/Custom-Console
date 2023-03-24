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
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SmokingCrab(8)));
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
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SlimeKeeper(10)));
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
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SharkBoss(10)));
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
		SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new PigBoss(1)));
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

void SydeCoastLevel::generateEnemy(MapSpace currentSpace)
{
	int LevelAdditions = currentSpace.getSpaceNumber() / 10;
	int chanceSpawn = rand() % 100;
	if (currentSpace.getPathNumber() == 2)
	{
		int level = ((rand() % 3) + 4) + LevelAdditions; //(4-6) + LevelAdditions
		if (chanceSpawn >= 0 && chanceSpawn < 80)
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new CrabEnemy(level)));
		}
		else
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FishEnemy(level)));
		}
	}
	else
	{
		int level = ((rand() % 3) + 4) + LevelAdditions; //(4-6) + LevelAdditions
		if (chanceSpawn >= 0 && chanceSpawn < 20)
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new OrcEnemy(level)));
		}
		else if (chanceSpawn >= 20 && chanceSpawn < 50)
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new RabbitEnemy(level)));
		}
		else
		{
			SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new FishEnemy(level)));
		}
	}
}
