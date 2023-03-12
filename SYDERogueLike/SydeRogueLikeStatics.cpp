#include "SydeRogueLikeStatics.h"

std::string SydeRogueLikeStatics::m_SceneTag = "";
std::string SydeRogueLikeStatics::m_BattleTag = "";
std::string SydeRogueLikeStatics::m_LevelSceneTag = "";

std::shared_ptr<Player> SydeRogueLikeStatics::m_Player = nullptr;

std::shared_ptr<Enemy> SydeRogueLikeStatics::m_Enemy = nullptr;

bool SydeRogueLikeStatics::initializeMap = false;

bool SydeRogueLikeStatics::fightSuccess = true;

string SydeRogueLikeStatics::TypeToString(_SQType type)
{
	switch (type)
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
	}
	return "Typeless";
}
