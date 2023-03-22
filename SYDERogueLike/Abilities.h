#pragma once
#include "GameTypes.h"
#include <string>

struct AbilityStruct
{
	AbilityStruct() 
	{
		m_Ability = Ability_None;
		m_AbilityName = "N/A";
		m_Description = "";
	}
	AbilityStruct(_SQAbility a, std::string ability, std::string desc)
	{
		m_Ability = a;
		m_AbilityName = ability;
		m_Description = desc;
	}
	_SQAbility m_Ability;
	std::string m_AbilityName;
	std::string m_Description;
};

class SYDEQuestAbilites
{
public:
	static AbilityStruct SQA_None;
	static AbilityStruct SQA_Hasten;
	static AbilityStruct SQA_ChainSmoker;
	static AbilityStruct SQA_Immunity;
	static AbilityStruct SQA_Insomnia;
	static AbilityStruct SQA_NaturalBoost;
	static AbilityStruct SQA_ConstantStruggle;
};