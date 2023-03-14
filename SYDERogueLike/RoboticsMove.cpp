#include "RoboticsMove.h"

bool RoboticsMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void RoboticsMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	Attacker->at("magicAttack") = Attacker->at("magicAttack").get<int>() + 2;
	Attacker->at("attack") = Attacker->at("attack").get<int>() + 12;
}
