#pragma once
#include "Move.h"
class PigRollMove : public Move {
public:
	PigRollMove()
	{
		m_Name = "Roll Around";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\PigRollAround.bmp", 120, 160, 20, 20, 0, 48));
		maxUsages = 40;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override
	{
		return false;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
	}
protected:
};