#include "ScaryFaceMove.h"

bool ScaryFaceMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
	return Defender->at("defence").get<int>() > 5;
}

void ScaryFaceMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
	int defence = Defender->at("defence").get<int>();
	defence -= 15;
	if (defence < 5)
	{
		defence = 5;
	}
	Defender->at("defence") = defence;
}
