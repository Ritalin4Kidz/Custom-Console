#pragma once
#include "Move.h"
class SabotageMove : public Move {
public:
	SabotageMove()
	{
		m_Name = "Sabotage";
		m_Type = Metal;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Metal\\Sabotage.bmp", 100, 160, 20, 20, 0, 40));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};