#pragma once
#include "Move.h"
class SkullPiercerMove : public Move {
public:
	SkullPiercerMove()
	{
		m_Name = "Skull Piercer";
		m_Type = Metal;
		BasePower = 110;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Metal\\SkullPiercer.bmp", 160, 100, 20, 20, 0, 40));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 65;
		useMagicAttack = true;
		m_TM_Identifier = "TM_013";
	}
protected:
};