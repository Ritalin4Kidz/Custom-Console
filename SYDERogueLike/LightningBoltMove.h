#pragma once
#include "Move.h"
class LightningBoltMove : public Move {
public:
	LightningBoltMove()
	{
		m_Name = "Lightning Bolt";
		m_Type = Electric;
		BasePower = 95;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\LightningBolt.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 70;
		useMagicAttack = true;
		m_TM_Identifier = "TM_002";
	}
protected:
};