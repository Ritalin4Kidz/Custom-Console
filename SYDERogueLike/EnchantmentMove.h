#pragma once
#include "Move.h"
class EnchantmentMove : public Move {
public:
	EnchantmentMove()
	{
		m_Name = "Enchantment";
		m_Type = Grass;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Grass\\Enchantment.bmp", 200, 100, 20, 20, 0, 50));
		maxUsages = 15;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};