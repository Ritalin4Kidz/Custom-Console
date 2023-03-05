#include "TypeSwapMove.h"

void TypeSwapMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	_SQType atkType = static_cast<_SQType>(Attacker->at("type").get<int>());
	_SQType defType = static_cast<_SQType>(Defender->at("type").get<int>());

	Attacker->at("type") = static_cast<int>(defType);
	Defender->at("type") = static_cast<int>(atkType);
}
