#pragma once
#include "Move.h"
class LooseMatchMove : public Move {
public:
	LooseMatchMove()
	{
		m_Name = "Loose Match";
		m_Type = Fire;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fire\\LooseMatch.bmp", 100, 160, 20, 20, 0, 40));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_011";
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override
	{
		return true;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		Attacker->at("magicAttack") = Attacker->at("magicAttack").get<int>() + 15;
	}
protected:
};