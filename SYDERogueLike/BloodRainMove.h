#pragma once
#include "Move.h"
class BloodRainMove : public Move {
public:
	BloodRainMove()
	{
		m_Name = "Blood Rain";
		m_Type = Telekinetic;
		BasePower = 120;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Telekinetic\\GhostFishBloodRain.bmp", 100, 200, 20, 20, 0, 50));
		maxUsages = 5;
		useMagicAttack = true;
		usagesLeft = maxUsages;
		m_Accuracy = 55;
	}
protected:
};