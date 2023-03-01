#include "SleepStatus.h"

void SleepStatus::Execute(json* Attacker, json* Defender, std::string* tag)
{
	//GIVE A CHANCE TO BREAK OUT
	int Chance = rand() % 100;
	if (Chance > 55)
	{
		Attacker->at("status") = static_cast<int>(Status_None);
	}
}

void SleepStatus::decrementUsages()
{
}
