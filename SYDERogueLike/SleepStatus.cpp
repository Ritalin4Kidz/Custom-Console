#include "SleepStatus.h"

void SleepStatus::Execute(json* Attacker, json* Defender, std::string* tag)
{
	//GIVE A CHANCE TO BREAK OUT
	int Chance = rand() % 100;
	int turns = Attacker->at("turnsSleeping").get<int>();
	if (turns > 1)
	{
		if (Chance > 55 || turns > 4)
		{
			Attacker->at("status") = static_cast<int>(Status_None);
		}
	}
	Attacker->at("turnsSleeping") = turns + 1;
}

void SleepStatus::decrementUsages()
{
}
