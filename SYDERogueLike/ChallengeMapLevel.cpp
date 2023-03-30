#include "ChallengeMapLevel.h"

void ChallengeMapLevel::doBossAction(MapSpace currentSpace)
{
}

void ChallengeMapLevel::doBossDefeatedAction()
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\EndCutscenes\\DefaultBossWin.bmp", 150, 40, 30, 20, 0, 10));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_END_UIAnimation;
	sceneLoad = "";
}

int ChallengeMapLevel::generateDiceRollAmount()
{
	return (rand() % m_DiceRollSize) + m_DiceRollMin;
}

void ChallengeMap001::generateEnemy(MapSpace currentSpace)
{

	int level = currentSpace.getSpaceNumber() * 10; //(4-6) + LevelAdditions
	std::shared_ptr<Enemy> enemy = std::shared_ptr<Enemy>(new OrcEnemy(level));
	enemy->setXpGain(0);
	SydeRogueLikeStatics::setEnemy(enemy);

}

MapSpaceTypes ChallengeMap001::generateFromPool()
{
	return MST_BattleSpace;
}


void ChallengeMap002::generateEnemy(MapSpace currentSpace)
{
}

void ChallengeMap002::doEndSpaceMethod(MapSpace currentSpace)
{
	m_UIAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BossAnimations\\StartCutscenes\\DefaultBossCutscene.bmp", 150, 120, 30, 20, 0, 30));
	m_UIAnimation.setLooping(false);
	m_UIAnimation.setFrame(0);
	m_SceneState = MMS_UIAnimation;
	sceneLoad = "Battle Scene";
	HideUI();
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new SharkBoss(50)));
	return;
}

MapSpaceTypes ChallengeMap002::generateFromPool()
{
	return MST_ShopSpace;
}
