#include "ChallengeMapLevel.h"

void ChallengeMapLevel::doBossAction(MapSpace currentSpace)
{
}

void ChallengeMapLevel::doBossDefeatedAction()
{
}

int ChallengeMap001::generateDiceRollAmount()
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
