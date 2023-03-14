#pragma once
#include "Move.h"
class BulkUpMove : public Move {
public:
	BulkUpMove()
	{
		m_Name = "Bulk Up";
		m_Type = Melee;
		BasePower = 00;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\BulkUp.bmp", 120, 140, 20, 20, 0, 42));
		maxUsages = 20;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		m_TM_Identifier = "TM_003";
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};