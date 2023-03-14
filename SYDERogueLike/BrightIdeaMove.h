#pragma once
#include "Move.h"
class BrightIdeaMove : public Move {
public:
	BrightIdeaMove()
	{
		m_Name = "Bright Idea";
		m_Type = Electric;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\BrightIdea.bmp", 80, 160, 20, 20, 0, 32));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		useMagicAttack = true;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};