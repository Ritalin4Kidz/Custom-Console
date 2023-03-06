#pragma once
#include "Move.h"
class LightningPunchMove : public Move {
public:
	LightningPunchMove()
	{
		m_Name = "Lightning Punch";
		m_Type = Electric;
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\LightningPunch.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 20;
		usagesLeft = maxUsages;
	}
protected:
};