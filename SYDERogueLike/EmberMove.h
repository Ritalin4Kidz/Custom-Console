#pragma once
#include "Move.h"
class EmberMove : public Move {
public:
	EmberMove()
	{
		m_Name = "Ember";
		m_Type = Fire;
		BasePower = 10;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fire\\Ember.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 20;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};