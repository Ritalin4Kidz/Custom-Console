#include "BloodPactMove.h"

bool BloodPactMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	int h = Attacker->at("health");
	int mH = Attacker->at("maxHealth");
	return (h > mH / 2);
}


void BloodPactMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	int h = Attacker->at("health");
	int mH = Attacker->at("maxHealth");
	h -= mH / 2;
	Attacker->at("attack") = Attacker->at("attack").get<int>() + 150;
	Attacker->at("magicAttack") = Attacker->at("magicAttack").get<int>() + 150;
	Attacker->at("health") = h;
}
