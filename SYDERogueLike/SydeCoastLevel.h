#pragma once
#include "MainMapScene.h"
#include "OrcEnemy.h"
#include "SmokingCrab.h"
class SydeCoastLevel : public MainMapScene
{
public:
	SydeCoastLevel() { m_SceneTag = "SYDE Coast Map Scene"; m_MapToLoad = "SydeCoast";}

	void doBossAction(MapSpace currentSpace) override;
	void generateEnemy() override;
private:
};