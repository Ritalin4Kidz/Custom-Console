#pragma once
#include "Move.h"
class ThunderStormMove : public Move {
public:
	ThunderStormMove()
	{
		m_Name = "Thunder Storm";
		m_Type = Electric;
		BasePower = 35;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\ThunderStorm.bmp", 200, 100, 20, 20, 0, 50));
		maxUsages = 25;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		useMagicAttack = true;
		m_TM_Identifier = "TM_002";
	}
protected:
};