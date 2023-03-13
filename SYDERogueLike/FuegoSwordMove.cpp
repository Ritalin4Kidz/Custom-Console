#include "FuegoSwordMove.h"

void FuegoSwordMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    //WE NEED TO VALIDATE THE JSON
    //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    if (static_cast<_SQStatus>(Attacker->at("status").get<int>()) == Status_Enchanted)
    {
        Bonus_Damage += 1.5f;
    }

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
