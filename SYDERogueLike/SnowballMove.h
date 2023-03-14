#pragma once
#include "Move.h"
class SnowballMove : public Move {
public:
	SnowballMove()
	{
		m_Name = "Snowball";
		m_Type = Snow;
		BasePower = 30;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Snow\\Snowball.bmp", 180, 80, 20, 20, 0, 36));
		maxUsages = 20;
		usagesLeft = maxUsages;
		m_Accuracy = 90;
		m_TM_Identifier = "TM_005";
	}
protected:
};