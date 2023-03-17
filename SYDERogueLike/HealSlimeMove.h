#pragma once
#include "Move.h"
class HealSlimeMove : public Move {
public:
	HealSlimeMove()
	{
		m_Name = "Heal Slime";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\HealSlime.bmp", 100, 360, 20, 20, 0, 90));
		maxUsages = 5;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};