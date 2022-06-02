#pragma once
#include <string>
#include "Player.h"
class SydeRogueLikeStatics
{
public:
	static void setSceneTag(std::string sceneTag) { m_SceneTag = sceneTag; }
	static std::string getSceneTag() { return m_SceneTag; }

	static void setPlayer(Player* newPlayer) { m_Player = newPlayer; }
	static Player* getPlayer() { return m_Player; }

private:
	static std::string m_SceneTag;
	static Player* m_Player;
};