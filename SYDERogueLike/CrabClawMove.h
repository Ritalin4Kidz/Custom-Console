#pragma once
#include "Move.h"
class CrabClawMove : public Move {
public:
	CrabClawMove()
	{
		m_Name = "Crab Claw";
		m_Type = Melee;
		BasePower = 35;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\BoneAttack.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 25;
		usagesLeft = maxUsages;
	}
protected:
};