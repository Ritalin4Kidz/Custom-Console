#include "SydeRogueLikeStatics.h"

std::string SydeRogueLikeStatics::m_SceneTag = "";

Player* SydeRogueLikeStatics::m_Player = new Player();

Enemy* SydeRogueLikeStatics::m_Enemy = nullptr;

bool SydeRogueLikeStatics::initializeMap = false;

bool SydeRogueLikeStatics::fightSuccess = true;