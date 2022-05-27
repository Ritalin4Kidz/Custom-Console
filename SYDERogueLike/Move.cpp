#include "Move.h"
AssetsClass BattleFunctions::astVars = AssetsClass();

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


float BattleFunctions::DetermineMultiplier(Move* Attack, Character* Defender)
{
    if (Attack->getType() == Water)
    {
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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
        switch (Defender->getType())
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