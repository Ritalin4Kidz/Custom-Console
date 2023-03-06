#include "EmberMove.h"

void EmberMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    //WE NEED TO VALIDATE THE JSON
//THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker, Defender, Bonus_Damage, useMagicAttack);
    int healthDef = Defender->at("health").get<int>();


    if (totalDamage > 0)
    {
        healthDef -= totalDamage;
    }
   setStatus(Status_Burnt, Defender, 75);

    //THEN WE NEED TO MAKE SURE JSON IS SAVED
    Defender->at("health") = healthDef;
}
