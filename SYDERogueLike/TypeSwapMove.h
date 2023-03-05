#pragma once
#include "Move.h"
class TypeSwapMove : public Move {
public:
	TypeSwapMove()
	{
		m_Name = "Type Swap";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Telekinetic\\TypeSwap.bmp", 120, 120, 20, 20, 0, 36));
		maxUsages = 10;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};