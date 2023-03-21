#pragma once
#include "Move.h"
class WaterboardMove : public Move {
public:
	WaterboardMove()
	{
		m_Name = "Wave";
		m_Type = Water;
		BasePower = 120;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\Waterboard.bmp", 100, 100, 20, 20, 0, 21));
		maxUsages = 5;
		useMagicAttack = false;
		usagesLeft = maxUsages;
		m_Accuracy = 55;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

		//Defender Get Attacked By Water
		float totalDamage = BaseDamageCalculation(Attacker, Defender, Bonus_Damage, useMagicAttack);
		int healthDef = Defender->at("health").get<int>();

		_SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());

		if (totalDamage > 0)
		{
			healthDef -= totalDamage;
		}
		//THEN WE NEED TO MAKE SURE JSON IS SAVED
		Defender->at("health") = healthDef;
		Defender->at("type") = static_cast<int>(Water);

	};
protected:
};
