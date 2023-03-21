#pragma once
#include "Move.h"
class RabbitFoodMove : public Move {
public:
	RabbitFoodMove()
	{
		m_Name = "Rabbit Food";
		m_Type = Grass;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Grass\\RabbitFood.bmp", 200, 160, 20, 20, 0, 80));
		maxUsages = 10;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override
	{
		return true;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		int health = Attacker->at("health").get<int>();
		int maxHealth = Attacker->at("maxHealth").get<int>();
		
		health += (maxHealth / 2);
		if (health > maxHealth)
		{
			health = maxHealth;
		}

		Attacker->at("health") = health;
	}
protected:
};