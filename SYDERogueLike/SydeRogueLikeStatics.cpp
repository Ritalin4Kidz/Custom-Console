#include "SydeRogueLikeStatics.h"

std::string SydeRogueLikeStatics::m_SceneTag = "";
std::string SydeRogueLikeStatics::m_BattleTag = "";
std::string SydeRogueLikeStatics::m_LevelSceneTag = "";

std::shared_ptr<Player> SydeRogueLikeStatics::m_Player = nullptr;

std::shared_ptr<Enemy> SydeRogueLikeStatics::m_Enemy = nullptr;

bool SydeRogueLikeStatics::initializeMap = false;

bool SydeRogueLikeStatics::fightSuccess = true;