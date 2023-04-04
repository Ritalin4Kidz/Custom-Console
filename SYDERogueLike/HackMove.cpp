#include "HackMove.h"
#pragma once

bool HackMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return true;
}

void HackMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	int attackerStatpool = Attacker->at("defence").get<int>() + Attacker->at("magicDefence").get<int>() + Attacker->at("attack").get<int>() + Attacker->at("magicAttack").get<int>() +
		Attacker->at("speed").get<int>() + Attacker->at("maxHealth").get<int>();
	int defenderStatpool = Defender->at("defence").get<int>() + Defender->at("magicDefence").get<int>() + Defender->at("attack").get<int>() + Defender->at("magicAttack").get<int>() +
		Defender->at("speed").get<int>() + Defender->at("maxHealth").get<int>();

	float aHthPercent = ((float)Attacker->at("health").get<int>()) / ((float)Attacker->at("maxHealth").get<int>());
	float dHthPercent = ((float)Defender->at("health").get<int>()) / ((float)Defender->at("maxHealth").get<int>());

	//ATTACKER STEALS STAT POINTS
	attackerStatpool -= 10;
	defenderStatpool -= 50;

	defaultStats(Attacker);
	defaultStats(Defender);

	addStats(Attacker, attackerStatpool);
	addStats(Defender, defenderStatpool);

	int attkHealth = ((float)Attacker->at("maxHealth").get<int>()) * aHthPercent;
	if (attkHealth == 0)
	{
		attkHealth = 1;
	}
	Attacker->at("health") = attkHealth;
	int defHealth = ((float)Defender->at("maxHealth").get<int>()) * dHthPercent;
	if (defHealth == 0)
	{
		defHealth = 1;
	}
	Defender->at("health") = defHealth;

}

void HackMove::defaultStats(json* a)
{
	a->at("attack") = 5;
	a->at("defence") = 5;
	a->at("magicAttack") = 5;
	a->at("magicDefence") = 5;
	a->at("speed") = 5;
	a->at("maxHealth") = 5;
}

void HackMove::addStats(json* a, int points)
{
	while (points > 0)
	{
		int statToIncrease = rand() % 6;
		switch (statToIncrease)
		{
		case 0:
			a->at("maxHealth") = a->at("maxHealth").get<int>() + 1;
			break;
		case 1:
			a->at("attack") = a->at("attack").get<int>() + 1;
			break;
		case 2:
			a->at("defence") = a->at("defence").get<int>() + 1;
			break;
		case 3:
			a->at("magicAttack") = a->at("magicAttack").get<int>() + 1;
			break;
		case 4:
			a->at("magicDefence") = a->at("magicDefence").get<int>() + 1;
			break;
		case 5:
		default:
			a->at("speed") = a->at("speed").get<int>() + 1;
			break;
		}
		points--;
	}
}
