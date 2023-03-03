#include "SabotageMove.h"

bool SabotageMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
    return setStatus(Status_Sabotaged, Defender, 0);
}

void SabotageMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
}
