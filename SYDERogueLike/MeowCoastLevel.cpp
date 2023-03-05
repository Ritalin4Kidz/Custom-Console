#include "MeowCoastLevel.h"

void MeowCoastLevel::doBossAction(MapSpace currentSpace)
{
}

void MeowCoastLevel::doBossDefeatedAction()
{
}

void MeowCoastLevel::generateEnemy()
{
	SydeRogueLikeStatics::setEnemy(std::shared_ptr<Enemy>(new BloodGhostEnemy(5)));
}
