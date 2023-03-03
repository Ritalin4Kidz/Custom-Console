#include "SmokeMoveType.h"

void SmokeMoveType::doDefenseDrop(json* Attacker, json* Defender, std::string* tag)
{
    int attackDef = Attacker->at("defence").get<int>();

    _SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (attackDef > 5 && ability != Ability_ChainSmoker)
    {
        attackDef--;;
        if (attackDef < 5)
        {
            attackDef = 5;
        }
    }
    //THEN WE NEED TO MAKE SURE JSON IS SAVED
    Attacker->at("defence") = attackDef;
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
