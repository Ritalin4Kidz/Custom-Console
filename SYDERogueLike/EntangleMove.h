#pragma once
#include "Move.h"
class EntangleMove : public Move {
public:
	EntangleMove()
	{
		m_Name = "Entangle";
		m_Type = Grass;
		BasePower = 40;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Grass\\GrassAttack.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
protected:
};