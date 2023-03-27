#pragma once
#include "Move.h"
class VoltTackleMove : public Move {
public:
	VoltTackleMove()
	{
		m_Name = "Volt Tackle";
		m_Type = Electric;
		BasePower = 90;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\VoltTackle.bmp", 120, 120, 20, 20, 0, 36));
		maxUsages = 10;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_012";
	}
protected:
};