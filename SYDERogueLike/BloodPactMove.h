#pragma once
#include "Move.h"
class BloodPactMove : public Move {
public:
	BloodPactMove()
	{
		m_Name = "Blood Pact";
		m_Type = Melee;
		BasePower = 00;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\BloodPact.bmp", 140, 100, 20, 20, 0, 35));
		maxUsages = 10;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		m_TM_Identifier = "TM_004";
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};