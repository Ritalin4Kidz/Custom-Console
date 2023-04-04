#include "ShatteredBulbMove.h"

bool ShatteredBulbMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void ShatteredBulbMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	int defence = Attacker->at("defence").get<int>();
	int magicDefence = Attacker->at("magicDefence").get<int>();

	Attacker->at("attack") = Attacker->at("attack").get<int>() + (defence -5);
	Attacker->at("magicAttack") = Attacker->at("magicAttack").get<int>() + (magicDefence -5);
	Attacker->at("magicDefence") = 5;
	Attacker->at("defence") = 5;
}
