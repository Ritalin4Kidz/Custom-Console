#include "SmokeBreakMove.h"

void SmokeBreakMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    //WE NEED TO VALIDATE THE JSON
    //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker, Defender, Bonus_Damage, useMagicAttack);
    int healthDef = Defender->at("health").get<int>();
    int maxHealthAttk = Attacker->at("maxHealth").get<int>();

    if (totalDamage > 0)
    {
        healthDef -= totalDamage;
    }

    Defender->at("health") = healthDef;

}
