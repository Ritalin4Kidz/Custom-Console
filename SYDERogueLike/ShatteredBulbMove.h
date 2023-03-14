#pragma once
#include "Move.h"
class ShatteredBulbMove : public Move {
public:
	ShatteredBulbMove()
	{
		m_Name = "Shattered Bulb";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Telekinetic\\ShatteredBulb.bmp", 120, 120, 20, 20, 0, 36));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		useMagicAttack = true;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};