#pragma once
#include <string>
#include "Enemy.h"
#include "Player.h"
class SydeRogueLikeStatics
{
public:
	static void setSceneTag(std::string sceneTag) { m_SceneTag = sceneTag; }
	static std::string getSceneTag() { return m_SceneTag; }

	static void setLevelSceneTag(std::string levelSceneTag) { m_LevelSceneTag = levelSceneTag; }
	static std::string getLevelSceneTag() { return m_LevelSceneTag; }

	static void setBattleTag(std::string battleTag) { m_BattleTag = battleTag; }
	static std::string getBattleTag() { return m_BattleTag; }

	static void setPlayer(std::shared_ptr<Player> newPlayer) { m_Player = newPlayer; }
	static void addPlayerXP(int xp) { m_Player->addXPToPlayer(xp); }
	static std::shared_ptr<Player> getPlayer() { return m_Player; }

	static void addPlayerInv(std::shared_ptr<ItemClass> newItem) { m_Player->AddInventory(newItem); }
	static void removePlayerInv(int index) { m_Player->removeInventoryAtIndex(index); }
	static void addPlayerMove(std::shared_ptr<Move> newMove) { m_Player->addMove(newMove); }
	static void removePlayerMove(int index) { m_Player->removeMoveAtIndex(index); }

	static void addPlayerMoney(int m) { m_Player->addMoney(m); }
	static bool spendPlayerMoney(int m) {return m_Player->removeMoney(m); }

	static void validatePlayerJson() { m_Player->validateCurrentJsonTag(); }
	static void validatePlayerFromJson(json j) { m_Player->validateFromJson(j); }

	static void setEnemy(std::shared_ptr<Enemy> newEnemy) { m_Enemy = newEnemy; }
	static std::shared_ptr<Enemy> getEnemy() { return m_Enemy; }

	static void toggleInitMap(bool isOn) { initializeMap = isOn; }
	static bool getInitMap() { return initializeMap; }

	static void toggleFightSuccess(bool isOn) { fightSuccess = isOn; }
	static bool getFightSuccess() { return fightSuccess; }

	static string TypeToString(_SQType type);

private:
	static std::string m_SceneTag;
	static std::string m_BattleTag;
	static std::string m_LevelSceneTag;
	static std::shared_ptr<Player> m_Player;
	static std::shared_ptr<Enemy> m_Enemy;

	static bool initializeMap;

	static bool fightSuccess;

};