#pragma once
#include <string>
#include "GameTypes.h"
#include "Move.h"

class Character {
public:
	Character() {}
	virtual ~Character() {}
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

	void validateFromJson(json t);


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

	vector<Move*> m_MoveTags = vector<Move*>();
};