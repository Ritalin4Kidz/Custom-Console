#pragma once
#include "Move.h"
class SlashMove : public Move {
public:
	SlashMove()
	{
		m_Name = "Slash";
		m_Type = Melee;
		BasePower = 70;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\SlashAnimation.bmp", 200, 80, 20, 20, 0, 40));
		maxUsages = 10;
		usagesLeft = maxUsages;
		m_Accuracy = 80;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};