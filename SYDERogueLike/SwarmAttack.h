#pragma once
#include "Move.h"
class FishSwarmMove : public Move {
public:
	FishSwarmMove()
	{
		m_Name = "Fish Swarm";
		m_Type = Water;
		BasePower = 10;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\SwarmAttack.bmp", 100, 240, 20, 20, 0, 60));
		maxUsages = 20;
		useMagicAttack = false;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));
		int times = (rand() % 3) + 2;
		while (times > 0)
		{
			//Defender Get Attacked By Water A Random Amount Of Times
			float totalDamage = BaseDamageCalculation(Attacker, Defender, Bonus_Damage, useMagicAttack);
			int healthDef = Defender->at("health").get<int>();
			if (totalDamage > 0)
			{
				healthDef -= totalDamage;
			}
			//THEN WE NEED TO MAKE SURE JSON IS SAVED
			Defender->at("health") = healthDef;
			times--;
		}
	}
protected:
};