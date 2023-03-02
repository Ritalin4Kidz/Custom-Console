#pragma once
#include "Move.h"
class SabotagedMoveEffect : public Move {
public:
	SabotagedMoveEffect()
	{
		m_Name = "A Sabotaged Move";
		m_Type = Typeless;
		BasePower = 35;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fire\\Explosion.bmp", 100, 140, 20, 20, 0, 33));
		maxUsages = 0;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
	void decrementUsages() override;
protected:
};