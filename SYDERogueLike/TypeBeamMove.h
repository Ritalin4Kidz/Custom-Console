#pragma once
#include "Move.h"
class TypeBeamMove : public Move {
public:
	TypeBeamMove()
	{
		m_Name = "Type Beam";
		m_Type = Typeless;
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\TypeBeam.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 10;
		m_Accuracy = 85;
		usagesLeft = maxUsages;
		useMagicAttack = true;
		m_TM_Identifier = "TM_014";
	}

	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		//WE NEED TO VALIDATE THE JSON
		//THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
		this->m_Type = static_cast<_SQType>(Attacker->at("type").get<int>());
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
	}
protected:
};
