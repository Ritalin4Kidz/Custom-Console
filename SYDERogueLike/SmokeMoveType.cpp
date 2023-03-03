#include "SmokeMoveType.h"

void SmokeMoveType::doDefenseDrop(json* Attacker, json* Defender, std::string* tag)
{
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
