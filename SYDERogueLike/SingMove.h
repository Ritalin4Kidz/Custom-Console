#pragma once
#include "Move.h"
class SingMove : public Move {
public:
	SingMove()
	{
		m_Name = "Sleep Song";
		m_Type = Air;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\Sing.bmp", 100, 160, 20, 20, 0, 40));
		maxUsages = 15;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};