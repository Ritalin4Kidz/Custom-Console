#pragma once
#include "Move.h"
class WaterPinchMove : public Move {
public:
	WaterPinchMove()
	{
		m_Name = "Water Pinch";
		m_Type = Water;
		BasePower = 35;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\WaterPinch.bmp", 120, 120, 20, 20, 0, 36));
		maxUsages = 20;
		useMagicAttack = false;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_009";
	}
protected:
};