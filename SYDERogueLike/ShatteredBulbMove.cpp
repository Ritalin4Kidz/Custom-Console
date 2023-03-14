#include "ShatteredBulbMove.h"

bool ShatteredBulbMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void ShatteredBulbMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	int defence = Attacker->at("defence").get<int>();
	if (defence < 5)
	{
		defence = 5;
	}
	int magicDefence = Attacker->at("magicDefence").get<int>();
	if (magicDefence < 5)
	{
		magicDefence = 5;
	}
	Attacker->at("attack") = Attacker->at("magicAttack").get<int>() + (defence -5);
	Attacker->at("magicDefence") = Attacker->at("magicDefence").get<int>() + (magicDefence -5);
	Attacker->at("magicDefence") = 5;
	Attacker->at("defence") = 5;
}
