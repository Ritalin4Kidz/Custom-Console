#include "SQFunctions.h"

std::string SQFunctions::TypeToString(_SQType s)
{
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
	switch (s)
	{
	case Fire:
		return "Fire";
	case Water:
		return "Water";
	case Air:
		return "Air";
	case Grass:
		return "Grass";
	case Metal:
		return "Metal";
	case Melee:
		return "Melee";
	case Snow:
		return "Snow";
	case Electric:
		return "Electric";
	case Telekinetic:
		return "Telekinetic";
	default:
		return "Typeless";
	}
	return "Typeless";
}
