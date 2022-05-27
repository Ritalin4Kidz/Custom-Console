#pragma once
#include "Move.h"
class SmokeBreakMove : public Move {
public:
	SmokeBreakMove()
	{
		m_Name = "Smoke Break";
		m_Type = Air;
		BasePower = 5;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\ItemUseAnimations\\CigaretteUseAnimation.bmp", 200, 280, 20, 20, 0, 137));
	}
	virtual ~SmokeBreakMove() {}
	void Execute(json* Attacker, json* Defender) override;
protected:
};