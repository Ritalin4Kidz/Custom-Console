#pragma once
#include "Move.h"
class IceBeamMove : public Move {
public:
	IceBeamMove()
	{
		m_Name = "Ice Beam";
		m_Type = Snow;
		BasePower = 75;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Snow\\IceBeam.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
		m_Accuracy = 90;
	}
protected:
};