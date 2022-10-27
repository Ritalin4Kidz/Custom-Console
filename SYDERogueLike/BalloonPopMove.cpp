#include "BalloonPopMove.h"

void BalloonPopMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    int defenceDef = Defender->at("defence").get<int>();

    _SQAbility ability = static_cast<_SQAbility>(Attacker->at("ability").get<int>());
    if (defenceDef > 5)
    {
        defenceDef-=20;
        if (defenceDef < 5)
        {
            defenceDef = 5;
        }
    }

    Defender->at("defence") = defenceDef;

}