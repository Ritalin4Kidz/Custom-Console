#include "SabotageMove.h"

void SabotageMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    _SQAbility ability = static_cast<_SQAbility>(Defender->at("status").get<int>());
    _SQStatus status = static_cast<_SQStatus>(Defender->at("status").get<int>());
    if (status == Status_None)
    {
        Defender->at("status") = static_cast<int>(Status_Sabotaged);
    }
}
