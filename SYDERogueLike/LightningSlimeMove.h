#pragma once
#include "Move.h"
class LightningSlimeMove : public Move {
public:
	LightningSlimeMove()
	{
		m_Name = "Lightning Slime";
		m_Type = Electric;
		BasePower = 100;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\LightningSlime.bmp", 240, 160, 20, 20, 0, 96));
		maxUsages = 5;
		usagesLeft = maxUsages;
		m_Accuracy = 65;
		useMagicAttack = true;
	}
protected:
};