#include "SmokeMoveType.h"

void SmokeMoveType::doDefenseDrop(json* Attacker, json* Defender, std::string* tag)
{
    int attackDef = Attacker->at("defence").get<int>();

    _SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (attackDef > 5 && ability != Ability_ChainSmoker)
    {
        attackDef -= 25;
        if (attackDef < 5)
        {
            attackDef = 5;
        }
    }
    int health = Attacker->at("health").get<int>();
    int maxHealth = Attacker->at("maxHealth").get<int>();
    health += (maxHealth / 8);
    if (health > maxHealth)
    {
        health = maxHealth;
    }
    //THEN WE NEED TO MAKE SURE JSON IS SAVED
    Attacker->at("defence") = attackDef;
    Attacker->at("health") = health;
}

bool SmokeMoveType::ExecuteMove(json* Attacker, json* Defender, std::string* tag)
{
    doDefenseDrop(Attacker, Defender, tag);
    if (isSuccessful(Attacker, Defender, tag))
    {
        Execute(Attacker, Defender, tag);
        return true;
    }
    return false;
}
