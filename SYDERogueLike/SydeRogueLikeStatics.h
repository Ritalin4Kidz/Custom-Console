#pragma once
#include <string>
#include "Enemy.h"
#include "Player.h"
class SydeRogueLikeStatics
{
public:
	static void setSceneTag(std::string sceneTag) { m_SceneTag = sceneTag; }
	static std::string getSceneTag() { return m_SceneTag; }

	static void setPlayer(Player* newPlayer) { m_Player = newPlayer; }
	static Player* getPlayer() { return m_Player; }

	static void setEnemy(Enemy* newEnemy) { m_Enemy = newEnemy; }
	static Enemy* getEnemy() { return m_Enemy; }

	static void toggleInitMap(bool isOn) { initializeMap = isOn; }
	static bool getInitMap() { return initializeMap; }

	static void toggleFightSuccess(bool isOn) { fightSuccess = isOn; }
	static bool getFightSuccess() { return fightSuccess; }

private:
	static std::string m_SceneTag;
	static Player* m_Player;
	static Enemy* m_Enemy;

	static bool initializeMap;

	static bool fightSuccess;

};