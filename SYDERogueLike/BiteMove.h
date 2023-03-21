#pragma once
#include "Move.h"
class BiteMove : public Move {
public:
	BiteMove()
	{
		m_Name = "Bite";
		m_Type = Melee;
		BasePower = 70;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\Bite.bmp", 100, 80, 20, 20, 0,20));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 95;
	}
protected:
};