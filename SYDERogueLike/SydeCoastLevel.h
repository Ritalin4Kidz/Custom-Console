#pragma once
#include "MainMapScene.h"
#include "OrcEnemy.h"
#include "BloodGhostEnemy.h"
#include "SmokingCrab.h"
#include "SlimeKeeper.h"
#include "FishEnemy.h"
#include "CrabEnemy.h"
#include "RabbitEnemy.h"
class SydeCoastLevel : public MainMapScene
{
public:
	SydeCoastLevel() { m_SceneTag = "SYDE Coast Map Scene"; m_MapToLoad = "SydeCoast";}

	void doBossAction(MapSpace currentSpace) override;
	void doBossDefeatedAction() override;
	void generateEnemy(MapSpace currentSpace) override;
private:
	int m_BossTag = 0;
};