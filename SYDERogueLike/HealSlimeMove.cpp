#include "HealSlimeMove.h"

bool HealSlimeMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return Attacker->at("health").get<int>() < Attacker->at("maxHealth").get<int>();
}

void HealSlimeMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	Attacker->at("health") = Attacker->at("maxHealth").get<int>();
}
