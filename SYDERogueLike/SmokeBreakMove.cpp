#include "SmokeBreakMove.h"

void SmokeBreakMove::Execute(json* Attacker, json* Defender)
{
    //WE NEED TO VALIDATE THE JSON
    //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->at("level").get<int>(), Attacker->at("attack").get<int>(), Defender->at("defence").get<int>(), Bonus_Damage);
    int healthDef = Defender->at("health").get<int>();
    int maxHealthAttk = Attacker->at("maxHealth").get<int>();

    int attackDef = Attacker->at("defence").get<int>();

     _SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (attackDef > 5 && ability != Ability_ChainSmoker)
    {
        attackDef--;;
        if (attackDef < 5)
        {
            attackDef = 5;;
        }
    }
    if (totalDamage > 0)
    {
        healthDef -= totalDamage;
    }

    //THEN WE NEED TO MAKE SURE JSON IS SAVED
    Attacker->at("defence") = attackDef;
    Defender->at("health") = healthDef;

}
