#pragma once
#include "Move.h"
class HackMove : public Move {
public:
	HackMove()
	{
		m_Name = "Hack";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\HackMove.bmp", 100, 340, 20, 20, 0, 85));
		maxUsages = 20;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;

	void defaultStats(json* a);

	void addStats(json* a, int points);

protected:
};