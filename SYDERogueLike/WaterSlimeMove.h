#pragma once
#include "Move.h"
class WaterSlimeMove : public Move {
public:
	WaterSlimeMove()
	{
		m_Name = "Water Slime";
		m_Type = Water;
		BasePower = 100;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\BlueSlime.bmp", 100, 400, 20, 20, 0, 100));
		maxUsages = 5;
		usagesLeft = maxUsages;
		m_Accuracy = 35;
		useMagicAttack = true;
	}
protected:
};