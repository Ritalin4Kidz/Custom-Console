#include "SmokeBreakMove.h"

void SmokeBreakMove::Execute(json* Attacker, json* Defender)
{
    //WE NEED TO VALIDATE THE JSON
    //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->at("level").get<int>(), Attacker->at("attack").get<int>(), Defender->at("defence").get<int>(), Bonus_Damage);
    Attacker->AddHealth(Attacker->getMaxHealth() / 5);
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (Attacker->getDefence() > 5 && Attacker->getAbility() != Ability_ChainSmoker)
    {
        Attacker->setDefence(Attacker->getDefence() - 1);
        if (Attacker->getDefence() < 5)
        {
            Attacker->setDefence(5);
        }
    }
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }

    //THEN WE NEED TO MAKE SURE JSON IS SAVED

}
