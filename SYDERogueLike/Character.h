#pragma once
#include "SYDEEngineAssets.h"
#include <string>
#include "GameTypes.h"
#include "Move.h"
#include "ItemClass.h"
#include <memory>
/*
TODO:
- MOVE POOL, VECTOR OF STRING OF LEARNABLE MOVES
*/
class Character {
public:
	Character() {}
	void setHealth(int HP) { m_Health = HP; }
	void AddHealth(int _Add) { m_Health += _Add; if (m_Health > m_MaxHealth) { m_Health = m_MaxHealth; } }
	void setMaxHealth(int HP_Max) { m_MaxHealth = HP_Max; }
	int getMaxHealth() { return m_MaxHealth; }
	int getHealth() { return m_Health; }
	void setAttack(int Atk) { m_Attack = Atk; }
	int getAttack() { return m_Attack; }
	void setDefence(int Dfc) { m_Defence = Dfc; }
	int getDefence() { return m_Defence; }
	void setMagicAttack(int mAtk) { m_MagicAttack = mAtk; }
	int getMagicAttack() { return m_MagicAttack; }
	void setMagicDefence(int mDfc) { m_MagicDefence = mDfc; }
	int getMagicDefence() { return m_MagicDefence; }
	void setLevel(int lvl) { m_Level = lvl; }
	int getLevel() { return m_Level; }
	void setType(_SQType type) { m_Type = type; }

	_SQAbility getAbility() { return m_Ability; }
	void setAbility(_SQAbility a) { m_Ability = a; }

	void setSpeed(int speed) { m_Speed = speed; }
	int getSpeed() { return m_Speed; }

	_SQType getType() { return m_Type; }
	void setName(std::string n) { m_Name = n; }
	std::string getName() { return m_Name; }

	void setStatus(_SQStatus _status);
	void clearStatus() { m_Status = Status_None; }
	_SQStatus getStatus() { return m_Status; };

	void setJSONTag(json t) { m_JSONTag = t; }
	json getJSONTag();

	void validateCurrentJsonTag();

	void validateFromJson(const json& j);

	void SetMoves(vector<std::shared_ptr<Move>> _Moves);
	void SetMoveAtIndex(int index, std::shared_ptr<Move> m);
	std::shared_ptr<Move> getMoveAtIndex(int index) { return m_MoveArray[index]; }
	vector<std::shared_ptr<Move>> getMoves() { return m_MoveArray; }
	void ClearMoves() { m_MoveArray.clear(); }

	void AddInventory(std::shared_ptr<ItemClass> item) { m_Inventory.push_back(item); }
	void SetInventory(vector<std::shared_ptr<ItemClass>> _Inv);
	void SetInventoryAtIndex(int index, std::shared_ptr<ItemClass> i);
	std::shared_ptr<ItemClass> getInventoryAtIndex(int index) { return m_Inventory[index]; }
	vector<std::shared_ptr<ItemClass>> getInventory() { return m_Inventory; }
	void ClearInventory() { m_Inventory.clear(); }

	void SetAnimation(CustomAnimationAsset a) { m_Animation = a; m_Animation.setFrame(0); m_Animation.setPaused(false); m_Animation.setLooping(true); }
	void init(int lvl);
	CustomAnimationAsset getAnimationAsset() { return m_Animation; }

	void setAnimationLoop(bool loop) { m_Animation.setLooping(true); }
	ConsoleWindow drawAnimationAsset(ConsoleWindow window, Vector2 v) { return m_Animation.draw_asset(window, v); }

	vector<std::shared_ptr<Move>> getUsableMoves();
	std::shared_ptr<Move> getLastEffortMove() { return m_LastEffortMove; }
protected:
	_SQType m_Type = Melee;
	_SQStatus m_Status = Status_None;
	_SQAbility m_Ability = Ability_None;

	int m_Health = 1;
	int m_MaxHealth = 1;
	int m_Attack = 1;
	int m_Defence = 1;
	int m_MagicAttack = 1;
	int m_MagicDefence = 1;
	int m_Level = 1;
	int m_Speed = 30;
	std::string m_Name = "N/A";
	json m_JSONTag;

	vector<std::shared_ptr<Move>> m_MoveArray = vector<std::shared_ptr<Move>>();
	vector<std::shared_ptr<ItemClass>> m_Inventory = vector<std::shared_ptr<ItemClass>>();
	CustomAnimationAsset m_Animation;

	std::shared_ptr<Move> m_LastEffortMove;
};