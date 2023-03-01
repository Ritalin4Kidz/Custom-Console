#include "BurntStatus.h"

void BurntStatus::Execute(json* Attacker, json* Defender, std::string* tag)
{
    int healthDef = Attacker->at("health").get<int>();
    healthDef -= 5;
    Attacker->at("health") = healthDef;
}

void BurntStatus::decrementUsages()
{
}
