#pragma once
enum _SQType {
	Fire = 0,
	Water,
	Air,
	Grass,
	Metal,
	Melee,
	Snow,
	Electric,
	Telekinetic,
	Typeless
};

enum _SQStatus {
	Status_None = 0,
	Status_Frozen,
	Status_Burnt,
	Status_Paralyzed,
	Status_Sleep,
	Status_Sabotaged
};
enum _SQ_Stat_Increase {
	STATINCREASE_HEALTH = 0,
	STATINCREASE_ATTACK,
	STATINCREASE_DEFENCE,
	STATINCREASE_MAGIC_ATTACK,
	STATINCREASE_MAGIC_DEFENCE,
	STATINCEASE_SPEED
};

enum _SQAbility
{
	Ability_None,
	//ATTACK IS INCREASED WHEN USING MOVE OF SAME TYPE
	Ability_Hasten,
	//DEFENCE DOESN'T DECREASE WHEN SMOKING
	Ability_ChainSmoker,
	//STATUS EFFECTS DON'T OCCUR
	Ability_Immunity,
	//CHARACTER CANNOT SLEEP
	Ability_Insomnia,
	//ATTACK BOOSTED WHEN MOVE IS SAME TYPE AS CHARACTER
	Ability_NaturalBoost
};