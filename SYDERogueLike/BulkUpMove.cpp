#include "BulkUpMove.h"

bool BulkUpMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void BulkUpMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	Attacker->at("defence") = Attacker->at("defence").get<int>() + 10;
	Attacker->at("attack") = Attacker->at("attack").get<int>() + 3;
}
