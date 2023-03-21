#pragma once
#include "MainMapScene.h"
#include "OrcEnemy.h"
#include "BloodGhostEnemy.h"
#include "FreebeeBoss.h"
#include "GhostFish.h"
#include "WolfEnemy.h"
#include "FishEnemy.h"
#include "AliBoss.h"
#include "FireSkeletonBoss.h"
class MeowCoastLevel : public MainMapScene
{
public:
	MeowCoastLevel() { m_SceneTag = "Meow Coast Map Scene"; m_MapToLoad = "MeowCoast"; }

	void doBossAction(MapSpace currentSpace) override;
	void doBossDefeatedAction() override;
	void generateEnemy(MapSpace currentSpace) override;
private:
	int m_BossTag = 0;
};