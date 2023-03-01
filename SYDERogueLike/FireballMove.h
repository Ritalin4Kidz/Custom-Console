#pragma once
#include "Move.h"
class FireballMove : public Move {
public:
	FireballMove()
	{
		m_Name = "Fireball";
		m_Type = Fire;
		BasePower = 65;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fire\\Fireball.bmp", 100, 160, 20, 20, 0, 40));
		maxUsages = 10;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
protected:
};