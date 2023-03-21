#pragma once
#include "Move.h"
class EnergyBeamMove : public Move {
public:
	EnergyBeamMove()
	{
		m_Name = "Energy Beam";
		m_Type = Telekinetic;
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Telekinetic\\Psybeam.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_010";
	}
protected:
};