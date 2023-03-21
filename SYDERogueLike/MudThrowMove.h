#pragma once
#include "Move.h"
class MudThrowMove : public Move {
public:
	MudThrowMove()
	{
		m_Name = "Mud Throw";
		m_Type = Typeless;
		BasePower = 5;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\MudThrow.bmp", 200, 80, 20, 20, 0, 37));
		maxUsages = 30;
		useMagicAttack = true;
		usagesLeft = maxUsages;
		m_Accuracy = 5;
	}
protected:
};