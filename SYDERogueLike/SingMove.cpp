#include "SingMove.h"

bool SingMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
    return setStatus(Status_Sleep, Defender, 0);
}

void SingMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
}
