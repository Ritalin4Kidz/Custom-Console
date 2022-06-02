#include "Move.h"
AssetsClass BattleFunctions::astVars = AssetsClass();

void Move::Execute(json* Attacker, json* Defender, std::string* tag)
{
    //WE NEED TO VALIDATE THE JSON
    //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));

    //Defender Get Attacked By Water
    float totalDamage = 0;
    if (useMagicAttack)
    {
        totalDamage = BaseDamageCalculation(Attacker->at("level").get<int>(), Attacker->at("magicAttack").get<int>(), Defender->at("magicDefence").get<int>(), Bonus_Damage);
    }
    else
    {
        totalDamage = BaseDamageCalculation(Attacker->at("level").get<int>(), Attacker->at("attack").get<int>(), Defender->at("defence").get<int>(), Bonus_Damage);
    }
    int healthDef = Defender->at("health").get<int>();

    _SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());

    if (totalDamage > 0)
    {
        healthDef -= totalDamage;
    }
    //THEN WE NEED TO MAKE SURE JSON IS SAVED
    Defender->at("health") = healthDef;
}

float Move::BaseDamageCalculation(int level, float AttackStat, float DefenceStat, float Bonus_Damage)
{
    //Can't Do Damage Regardless
    if (Bonus_Damage == 0)
    {
        return Bonus_Damage;
    }
    //RANGE BONUS DAMAGE
    float range = ((float)rand() / RAND_MAX) + 0.5;
    Bonus_Damage *= range; //RANGE BETWEEN 0.5-1.5 Multiplier

    //BASED OFF POKEMON https://bulbapedia.bulbagarden.net/wiki/Damage
    float damage_dealt = ((((((2 * level) / 5) + 2) * this->BasePower * (AttackStat / DefenceStat)) / 50) + 2) * Bonus_Damage;
    //MINIMUM OF 1 DAMAGE IF ATTACK CAN HIT
    if (damage_dealt < 1 && Bonus_Damage != 0)
    {
        damage_dealt = 1;
    }

    return damage_dealt;
}


float BattleFunctions::DetermineMultiplier(Move* Attack, _SQType Defender)
{
    if (Attack->getType() == Water)
    {
        switch (Defender)
        {
        case Fire:
            return 3.0f;
        case Grass:
            return 0.75f;
        case Metal:
            return 1.5f;
        case Electric:
            return 1.25f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Fire)
    {
        switch (Defender)
        {
        case Grass:
            return 3.0f;
        case Water:
            return 0.5f;
        case Snow:
            return 2.0f;
        case Metal:
            return 2.5f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Grass)
    {
        switch (Defender)
        {
        case Water:
            return 2.0f;
        case Fire:
            return 0.25f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Air)
    {
        switch (Defender)
        {
        case Melee:
            return 1.5f;
        case Grass:
            return 2.5f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Metal)
    {
        switch (Defender)
        {
        case Fire:
            return 0.5f;
        case Water:
            return 0.5f;
        case Metal:
            return 0.5f;
        case Telekinetic:
            return 3.0f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Melee)
    {
        switch (Defender)
        {
        case Fire:
            return 1.25f;
        case Air:
            return 0.25f;
        case Melee:
            return 3.0f;
        case Telekinetic:
            return 0.5f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Electric)
    {
        switch (Defender)
        {
        case Air:
            return 3.0f;
        case Electric:
            return 0;
        case Telekinetic:
            return 2;
        case Water:
            return 4;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Snow)
    {
        switch (Defender)
        {
        case Fire:
            return 0.5f;
        case Grass:
            return 2.5f;
        case Telekinetic:
            return 2;
        case Air:
            return 3;
        case Metal:
            return 0.75f;
        default:
            return 1;
        }
    }
    else if (Attack->getType() == Telekinetic)
    {
        switch (Defender)
        {
        case Melee:
            return 2.5f;
        case Telekinetic:
            return 0;
        case Air:
            return 2.25f;
        case Electric:
            return 1.25f;
        case Snow:
            return 0.25f;
        case Metal:
            return 0;
        default:
            return 1;
        }
    }
    return 1;
}