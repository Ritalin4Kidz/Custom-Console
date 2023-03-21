#pragma once
#include "Move.h"
class BubblerMove : public Move {
public:
	BubblerMove()
	{
		m_Name = "Bubbler";
		m_Type = Water;
		BasePower = 25;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\WaterAttack.bmp", 100, 140, 20, 20, 0, 35));
		maxUsages = 20;
		useMagicAttack = false;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_008";
	}
protected:
};