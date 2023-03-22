#pragma once
#include "Move.h"
class BeeStingMove : public Move {
public:
	BeeStingMove()
	{
		m_Name = "Bee Sting";
		m_Type = Air;
		BasePower = 80;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\BeeSting.bmp", 100, 100, 20, 20, 0, 15));
		maxUsages = 10;
		useMagicAttack = false;
		usagesLeft = maxUsages;
	}
protected:
};