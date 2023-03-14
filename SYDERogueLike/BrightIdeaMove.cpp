#include "BrightIdeaMove.h"

bool BrightIdeaMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void BrightIdeaMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    Attacker->at("magicDefence") = Attacker->at("magicDefence").get<int>() + 15;
    Attacker->at("defence") = Attacker->at("defence").get<int>() + 15;
}
