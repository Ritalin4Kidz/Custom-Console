#pragma once
#include <string>
#include <vector>
#include "SYDEstdafx.h"
#include "json.hpp"
#include "FightWindow.h"

class LevelUPRates {
public:
	static int FAST_LEVEL_UP_GROUP_START;
	static int NORMAL_LEVEL_UP_GROUP_START;
	static int SLOW_LEVEL_UP_GROUP_START;

	static float FAST_LEVEL_UP_GROUP_RATE;
	static float NORMAL_LEVEL_UP_GROUP_RATE;
	static float SLOW_LEVEL_UP_GROUP_RATE;
};

using nlohmann::json;
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
	Status_Sleep
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


enum _SQMoves {
	_SQ_Water_Blast = 0,
	_SQ_Smoke_Cloud,
	_SQ_Smoke_Break,
	_SQ_Slash,
	_SQ_Bone_Club,
	_SQ_Sudden_Cold,
	_SQ_Swarm,
	_SQ_Self_Destruct,
	_SQ_Entangle,
	_SQ_Lightning_Slime,
	_SQ_Water_Slime,
	_SQ_Heal_Slime,
	_SQ_Hope_Slime,
	_SQ_Fireball,
	_SQ_Wave_Splash,
	_SQ_Pitch_Black,
	_SQ_Flashbang,
	_SQ_Growth,
	_SQ_Lightning_Bolt,
	_SQ_Lightning_Punch,
	_SQ_Rainbow,
	_SQ_Knights_Sword,
	_SQ_BrightIdea,
	_SQ_ShatteredBulb,
	_SQ_SourNote,
	_SQ_BellRing,
	_SQ_Sing,
	_SQ_Sabotage,
	_SQ_Volt_Tackle,
	_SQ_Self_Change,
	_SQ_Type_Swap,
	_SQ_Bide,
	_SQ_Ember,
	_SQ_Poison_Flower,
	_SQ_Garden,
	_SQ_Icicle_Beam,
	_SQ_Snowball,
	_SQ_Psybeam,
	_SQ_Snowman,
	_SQ_Gust,
	_SQ_Scary_Face,
	_SQ_Bubble,
	_SQ_Bite,
	_SQ_Loose_Match,
	_SQ_Waterboard,
	_SQ_Marked,
	_SQ_Skull_Pierce,
	_SQ_Ciggie_Rain,
	_SQ_Bee_Sting,
	_SQ_Bulk_Up,
	_SQ_Rabbit_Food
};

class Character {
public:
	Character() {}
	virtual ~Character() {}
	void setHealth(int HP) { m_Health = HP; }
	void AddHealth(int _Add) { m_Health += _Add; }
	void setMaxHealth(int HP_Max) { m_MaxHealth = HP_Max; }
	int getMaxHealth() { return m_MaxHealth; }
	int getHealth() { return m_Health; }
	void setAttack(int Atk) { m_Attack = Atk; }
	int getAttack() { return m_Attack; }
	int getAttack(_SQType MoveType);
	void setDefence(int Dfc) { m_Defence = Dfc; }
	int getDefence() { return m_Defence; }
	void setMagicAttack(int mAtk) { m_MagicAttack = mAtk; }
	int getMagicAttack() { return m_MagicAttack; }
	int getMagicAttack(_SQType MoveType);
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

	void setJSONTag(std::string t) { m_JSONTag = t; }
	std::string getJSONTag() { return m_JSONTag; }

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
	std::string m_JSONTag = "";
};

class Move {
public:
	Move() {}
	virtual ~Move() { }
	virtual void Execute(Character* Attacker, Character* Defender, FightWindow* f);
	_SQType getType() { return m_Type; }
	std::string getName() { return m_Name; }

	float getPower() { return BasePower; }

	CustomAnimationAsset getAnimation() { return m_Animation; }
	float BaseDamageCalculation(int level, float AttackStat, float DefenceStat, float Bonus_Damage);

	_SQMoves getMoveInt() { return m_Move; }
	bool getIfTeachable(_SQType s) { for (int i = 0; i < m_TeachAbleTypes.size(); i++) { if (m_TeachAbleTypes[i] == s) return true; } return false; }

	std::string toStatsJsonString();
protected:
	_SQType m_Type;
	std::string m_Name;
	float BasePower;
	CustomAnimationAsset m_Animation;
	_SQMoves m_Move;
	std::vector<_SQType> m_TeachAbleTypes;
	std::string m_Info = "";
};

class Player : public Character {
public:
	Player() { xp_to_next_level = LevelUPRates::NORMAL_LEVEL_UP_GROUP_START; levelUpRate = LevelUPRates::NORMAL_LEVEL_UP_GROUP_RATE; }
	virtual ~Player() { }
	static int getMinimumDefence() { return minimumDefence; }
	static int getMinimumAttack() { return minimumAttack; }

	void AddXP(int xp, _SQ_Stat_Increase s);


	std::vector<Move*> getMoves() { return _MoveArray; }
	void SetMoves(std::vector<Move*> _Moves);
	void ClearMoves() { for (int i = 0; i < _MoveArray.size(); i++) { delete _MoveArray[i]; }_MoveArray.clear(); }
	void SetMoveAtIndex(int index, Move* m);

	bool HasMove(Move m) { for (int i = 0; i < _MoveArray.size(); i++) { if (_MoveArray[i]->getMoveInt() == m.getMoveInt()) return true; } return false; }
	bool HasMove(_SQMoves m) { for (int i = 0; i < _MoveArray.size(); i++) { if (_MoveArray[i]->getMoveInt() == m) return true; } return false; }

	void setXP_To_Next_Level(int xp, float rate) { xp_to_next_level = xp; levelUpRate = rate; }

	Move* getMoveAtIndex(int index) { return _MoveArray[index]; }
	std::vector<_SQMoves> getUnlockedMoves() { return UnlockedMoves; }
	void addUnlockedMove(_SQMoves s);
protected:
	std::vector<Move*> _MoveArray;
	int current_xp = 0;
	int xp_to_next_level;
	float levelUpRate;
	std::vector<_SQMoves> UnlockedMoves;
	static int minimumDefence;
	static int minimumAttack;
};

class Enemy : public Character {
public:
	Enemy() {}
	virtual ~Enemy() { }
	void SetAnimation(CustomAnimationAsset a) { m_Animation = a; m_Animation.setFrame(0); m_Animation.setPaused(false); m_Animation.setLooping(true); }
	void init(int lvl);
	CustomAnimationAsset getAnimationAsset() { return m_Animation; }

	void setAnimationLoop(bool loop) { m_Animation.setLooping(true); }
	ConsoleWindow drawAnimationAsset(ConsoleWindow window, Vector2 v) { window = m_Animation.draw_asset(window, v); return window; }

	void setTag(std::string t) { Tag = t; }
	std::string getTag() { return Tag; }

	void to_json(json& j);

	void from_json(const json& j);

	std::vector<Move*> getMoves() { return _MoveArray; }
	void SetMoves(std::vector<Move*> _Moves);
	void ClearMoves() { for (int i = 0; i < _MoveArray.size(); i++) { delete _MoveArray[i]; }_MoveArray.clear(); }
	void SetMoveAtIndex(int index, Move* m);
	Move* getMoveAtIndex(int index) { return _MoveArray[index]; }

	_SQ_Stat_Increase getStatToIncrease() { return m_StatToIncrease; }
	void setStatToIncrease(_SQ_Stat_Increase s) { m_StatToIncrease = s; }

	int getRunChance() { return runChance; }

protected:
	int runChance = 95;
	_SQ_Stat_Increase m_StatToIncrease = STATINCREASE_HEALTH;
	std::string Tag;
	std::vector<Move*> _MoveArray;
	CustomAnimationAsset m_Animation;
};

class BattleFunctions {
public:
	static float DetermineMultiplier(Move* Attack, Character* Defender);
	static AssetsClass astVars;
};

#pragma region EnemyClasses
class Orc : public Enemy {
public:
	Orc(int lvl);
};

class Blue_Fish : public Enemy {
public:
	Blue_Fish(int lvl);
};
class Wolf : public Enemy {
public:
	Wolf(int lvl);
};

class Crab : public Enemy {
public:
	Crab(int lvl);
};
class Smoking_Crab : public Enemy {
public:
	Smoking_Crab(int lvl);
};
class Bee : public Enemy {
public:
	Bee(int lvl);
};
class Rabbit : public Enemy {
public:
	Rabbit(int lvl);
};
class Freebee : public Enemy {
public:
	Freebee(int lvl);
};
#pragma endregion


#pragma region Move Dictionary

class Water_Blast: public Move {
public:
	Water_Blast() 
	{ 
		m_Move = _SQ_Water_Blast; 
		m_Name = "Water Blast"; 
		m_Type = Water; 
		BasePower = 50; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\WaterBlast.bmp", BattleFunctions::astVars, 200, 100, 20, 20, 0, 45));
		m_TeachAbleTypes = std::vector<_SQType>{Water};
	}
	virtual ~Water_Blast() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Smoke_Break : public Move {
public:
	Smoke_Break() 
	{ 
		m_Move = _SQ_Smoke_Break;
		m_Name = "Smoke Break";
		m_Type = Air; 
		BasePower = 5;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\ItemUseAnimations\\CigaretteUseAnimation.bmp", BattleFunctions::astVars, 200, 280, 20, 20, 0, 137)); 
		m_TeachAbleTypes = std::vector<_SQType>{Air,Fire};
	}
	virtual ~Smoke_Break() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Smoke_Cloud : public Move {
public:
	Smoke_Cloud() 
	{ 
		m_Move = _SQ_Smoke_Cloud; 
		m_Name = "Smoke Cloud"; 
		m_Type = Air; 
		BasePower = 25; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SmokeCloud.bmp", BattleFunctions::astVars, 200, 80, 20, 20, 0, 37)); 
		m_TeachAbleTypes = std::vector<_SQType>{Air,Fire};
	}
	virtual ~Smoke_Cloud() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Swarm : public Move {
public:
	Swarm() 
	{
		m_Move = _SQ_Swarm; 
		m_Name = "Swarm";
		m_Type = Water;
		BasePower = 10;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SwarmAttack.bmp", BattleFunctions::astVars, 100, 240, 20, 20, 0, 57)); 
		m_TeachAbleTypes = std::vector<_SQType>{Water};
	}
	virtual ~Swarm() {}
protected:
};
class Slash : public Move {
public:
	Slash() 
	{ 
		m_Move = _SQ_Slash; 
		m_Name = "Slash"; 
		m_Type = Melee; 
		BasePower = 80; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SlashAnimation.bmp", BattleFunctions::astVars, 200, 80, 20, 20, 0, 40));
		m_TeachAbleTypes = std::vector<_SQType>{Grass,Melee,Fire,Water,Snow,Metal};
	}
	virtual ~Slash() {}
protected:
};
class Bone_Club : public Move {
public:
	Bone_Club() 
	{ 
		m_Move = _SQ_Bone_Club;
		m_Name = "Bone Club";
		m_Type = Melee;
		BasePower = 65;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BoneAttack.bmp", BattleFunctions::astVars, 80, 160, 20, 20, 0, 32)); 
		m_TeachAbleTypes = std::vector<_SQType>{Melee};
	}
	virtual ~Bone_Club() {}
protected:
};

class Self_Destruct : public Move {
public:
	Self_Destruct() 
	{ 
		m_Move = _SQ_Self_Destruct; 
		m_Name = "Self Destruct"; 
		m_Type = Fire; 
		BasePower = 150;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Explosion.bmp", BattleFunctions::astVars, 110, 140, 22, 20, 0, 32));
		m_TeachAbleTypes = std::vector<_SQType>{Fire,Metal};
	}
	virtual ~Self_Destruct() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Entangle : public Move {
public:
	Entangle() 
	{ 
		m_Move = _SQ_Entangle;
		m_Name = "Entangle";
		m_Type = Grass;
		BasePower = 35;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\GrassAttack.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Grass,Telekinetic};
	}
	virtual ~Entangle() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Lightning_Slime : public Move {
public:
	Lightning_Slime() 
	{ 
		m_Move = _SQ_Lightning_Slime; 
		m_Name = "Slime of Lightning";
		m_Type = Electric;
		BasePower = 70;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\LightningSlime.bmp", BattleFunctions::astVars, 240, 160, 20, 20, 0, 91)); 
		m_TeachAbleTypes = std::vector<_SQType>{
			Electric
		};
	}
	virtual ~Lightning_Slime() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Water_Slime : public Move {
public:
	Water_Slime() 
	{ 
		m_Move = _SQ_Water_Slime;
		m_Name = "Slime of Water"; 
		m_Type = Water; 
		BasePower = 65;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BlueSlime.bmp", BattleFunctions::astVars, 100, 400, 20, 20, 0, 100));
		m_TeachAbleTypes = std::vector<_SQType>{
		Water
		};
	}
	virtual ~Water_Slime() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Heal_Slime : public Move {
public:
	Heal_Slime() 
	{ 
		m_Move = _SQ_Heal_Slime;
		m_Name = "Slime of Healing";
		m_Type = Melee; 
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\HealSlime.bmp", BattleFunctions::astVars, 100, 360, 20, 20, 0, 90)); 
		m_TeachAbleTypes = std::vector<_SQType>{Melee};
	}
	virtual ~Heal_Slime() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Hope_Slime : public Move {
public:
	Hope_Slime() 
	{ 
		m_Move = _SQ_Hope_Slime;
		m_Name = "Slime of Hope";
		m_Type = Grass;
		BasePower = 300;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BlueSlime.bmp", BattleFunctions::astVars, 100, 400, 20, 20, 0, 100));
		m_TeachAbleTypes = std::vector<_SQType>{Grass};
	}
	virtual ~Hope_Slime() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Fireball : public Move {
public:
	Fireball() 
	{ 
		m_Move = _SQ_Fireball;
		m_Name = "Fireball"; 
		m_Type = Fire; 
		BasePower = 50;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fireball.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 40));	
		m_TeachAbleTypes = std::vector<_SQType>{Fire};
	}
	virtual ~Fireball() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Wave_Splash : public Move {
public:
	Wave_Splash() 
	{ 
		m_Move = _SQ_Wave_Splash; 
		m_Name = "Wave Splash"; 
		m_Type = Water; BasePower = 20; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\WaveAttack.bmp", BattleFunctions::astVars, 60, 140, 20, 20, 0, 21)); 
		m_TeachAbleTypes = std::vector<_SQType>{Water};
	}
	virtual ~Wave_Splash() {}
protected:
};
class Sudden_Cold : public Move {
public:
	Sudden_Cold() 
	{ 
		m_Move = _SQ_Sudden_Cold;
		m_Name = "Sudden Cold";
		m_Type = Snow;
		BasePower = 40; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SuddenCold.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 40)); 
		m_TeachAbleTypes = std::vector<_SQType>{Snow, Water};
	}
	virtual ~Sudden_Cold() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Pitch_Black : public Move {
public:
	Pitch_Black() 
	{ 
		m_Move = _SQ_Pitch_Black;
		m_Name = "Pitch Black"; 
		m_Type = Telekinetic; 
		BasePower = 30;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\PitchBlack.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Telekinetic};
	}
	virtual ~Pitch_Black() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Lightning_Bolt : public Move {
public:
	Lightning_Bolt() 
	{ 
		m_Move = _SQ_Lightning_Bolt; 
		m_Name = "Lightning Bolt"; 
		m_Type = Electric; 
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\LightningBolt.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25)); 
		m_TeachAbleTypes = std::vector<_SQType>{Electric,Telekinetic};
	}
	virtual ~Lightning_Bolt() {}

	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Lightning_Punch : public Move {
public:
	Lightning_Punch() 
	{ 
		m_Move = _SQ_Lightning_Punch;
		m_Name = "Lightning Punch";
		m_Type = Electric;
		BasePower = 55;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\LightningPunch.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25)); 
		m_TeachAbleTypes = std::vector<_SQType>{Electric,Melee};
	}
	virtual ~Lightning_Punch() {}

	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Rainbow : public Move {
public:
	Rainbow() 
	{ 
		m_Name = "Rainbow";
		m_Move = _SQ_Rainbow;
		m_Type = Telekinetic;
		BasePower = 60; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\RainbowAttack.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Water,Telekinetic};
	}
	virtual ~Rainbow() {}

	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Knights_Sword : public Move {
public:
	Knights_Sword() 
	{ 
		m_Move = _SQ_Knights_Sword;
		m_Name = "Knight's Sword"; 
		m_Type = Metal;
		BasePower = 75;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SwordAnimation.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Metal,Melee};
	}
	virtual ~Knights_Sword() {}
protected:
};
class Growth : public Move {
public:
	Growth() 
	{ 
		m_Move = _SQ_Growth;
		m_Name = "Growth";
		m_Type = Grass;
		BasePower = 0; 
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Growth.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Grass};
	}
	virtual ~Growth() {}

	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Flashbang : public Move {
public:
	Flashbang() 
	{ 
		m_Move = _SQ_Flashbang; 
		m_Name = "Flashbang"; 
		m_Type = Electric; 
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Flashbang.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Electric,Telekinetic};
	}
	virtual ~Flashbang() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Bright_Idea : public Move {
public:
	Bright_Idea() 
	{ 
		m_Move = _SQ_BrightIdea;
		m_Name = "Bright Idea";
		m_Type = Electric;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BrightIdea.bmp", BattleFunctions::astVars, 80, 160, 20, 20, 0, 32));
		m_TeachAbleTypes = std::vector<_SQType>{Electric,Telekinetic};
	}
	virtual ~Bright_Idea() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Shattered_Bulb : public Move {
public:
	Shattered_Bulb() 
	{
		m_Move = _SQ_ShatteredBulb; 
		m_Name = "Shattered Bulb";
		m_Type = Telekinetic;
		BasePower = 30;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\ShatteredBulb.bmp", BattleFunctions::astVars, 120, 120, 20, 20, 0, 36));
		m_TeachAbleTypes = std::vector<_SQType>{Electric,Telekinetic};
	}
	virtual ~Shattered_Bulb() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Bell_Ring : public Move {
public:
	Bell_Ring() 
	{
		m_Move = _SQ_BellRing;
		m_Name = "Bell Ring";
		m_Type = Metal; 
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BellRing.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{Metal,Melee};
	}
	virtual ~Bell_Ring() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Sing : public Move {
public:
	Sing() 
	{
		m_Move = _SQ_Sing;
		m_Name = "Sing"; 
		m_Type = Air; 
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Sing.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 40));
		m_TeachAbleTypes = std::vector<_SQType>{Water,Grass,Air};
	}
	virtual ~Sing() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Sour_Note : public Move {
public:
	Sour_Note() 
	{ 
		m_Move = _SQ_SourNote;
		m_Name = "Sour Note";
		m_Type = Air; 
		BasePower = 30;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SourNote.bmp", BattleFunctions::astVars, 260, 100, 20, 20, 0, 65));
		m_TeachAbleTypes = std::vector<_SQType>{Metal,Air};
	}
	virtual ~Sour_Note() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Sabotage : public Move {
public:
	Sabotage() 
	{ 
		m_Move = _SQ_Sabotage;
		m_Name = "Sabotage";
		m_Type = Metal; 
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Sabotage.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 45));
		m_TeachAbleTypes = std::vector<_SQType>{Metal,Melee};
	}
	virtual ~Sabotage() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Sabotaged_Move : public Move {
public:
	Sabotaged_Move(std::string n) 
	{ 
		m_Info = "This is the move that is used when your move has been sabotaged";
		m_Name = n;
		m_Type = Typeless; 
		BasePower = 40;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Explosion.bmp", BattleFunctions::astVars, 110, 140, 22, 20, 0, 32));
	}
	virtual ~Sabotaged_Move() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Volt_Tackle : public Move {
public:
	Volt_Tackle()
	{
		m_Move = _SQ_Volt_Tackle;
		m_Name = "Volt Tackle";
		m_Type = Electric;
		BasePower = 90;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\VoltTackle.bmp", BattleFunctions::astVars, 120, 120, 20, 20, 0, 36));
		m_TeachAbleTypes = std::vector<_SQType>{ Electric };
	}
	virtual ~Volt_Tackle() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Self_Change : public Move {
public:
	Self_Change()
	{
		m_Move = _SQ_Self_Change;
		m_Name = "Self Change";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SelfChange.bmp", BattleFunctions::astVars, 100, 180, 20, 20, 0, 45));
		m_TeachAbleTypes = std::vector<_SQType>{ Telekinetic, Metal,Melee };
	}
	virtual ~Self_Change() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Type_Swap : public Move {
public:
	Type_Swap()
	{
		m_Move = _SQ_Type_Swap;
		m_Name = "Type Swap";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\TypeSwap.bmp", BattleFunctions::astVars, 120, 120, 20, 20, 0, 36));
		m_TeachAbleTypes = std::vector<_SQType>{ Telekinetic };
	}
	virtual ~Type_Swap() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Bide : public Move {
public:
	Bide()
	{
		m_Move = _SQ_Bide;
		m_Name = "Bide";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Bide.bmp", BattleFunctions::astVars, 100, 180, 20, 20, 0, 45));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Metal };
	}
	virtual ~Bide() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Ember : public Move {
public:
	Ember()
	{
		m_Move = _SQ_Ember;
		m_Name = "Ember";
		m_Type = Fire;
		BasePower = 30;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Ember.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Fire };
	}
	virtual ~Ember() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Poison_Flower : public Move {
public:
	Poison_Flower()
	{
		m_Move = _SQ_Poison_Flower;
		m_Name = "Poison Flower";
		m_Type = Grass;
		BasePower = 20;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\PoisonFlower.bmp", BattleFunctions::astVars, 100, 140, 20, 20, 0, 35));
		m_TeachAbleTypes = std::vector<_SQType>{ Grass };
	}
	virtual ~Poison_Flower() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Garden : public Move {
public:
	Garden()
	{
		m_Move = _SQ_Garden;
		m_Name = "Garden";
		m_Type = Grass;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Garden.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Grass };
	}
	virtual ~Garden() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};

class Icicle_Beam : public Move {
public:
	Icicle_Beam()
	{
		m_Move = _SQ_Icicle_Beam;
		m_Name = "Icicle Beam";
		m_Type = Snow;
		BasePower = 80;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\IceBeam.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Snow };
	}
	virtual ~Icicle_Beam() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Snowball : public Move {
public:
	Snowball()
	{
		m_Move = _SQ_Snowball;
		m_Name = "Snowball";
		m_Type = Snow;
		BasePower = 40;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Snowball.bmp", BattleFunctions::astVars, 180, 80, 20, 20, 0, 36));
		m_TeachAbleTypes = std::vector<_SQType>{ Snow };
	}
	virtual ~Snowball() {}
protected:
};
class Psybeam : public Move {
public:
	Psybeam()
	{
		m_Move = _SQ_Psybeam;
		m_Name = "Psybeam";
		m_Type = Telekinetic;
		BasePower = 90;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Psybeam.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Telekinetic };
	}
	virtual ~Psybeam() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Snowman : public Move {
public:
	Snowman()
	{
		m_Move = _SQ_Snowman;
		m_Name = "Snowman";
		m_Type = Snow;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\CollapsedSnowman.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 40));
		m_TeachAbleTypes = std::vector<_SQType>{ Snow };
	}
	virtual ~Snowman() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Gust : public Move {
public:
	Gust()
	{
		m_Move = _SQ_Gust;
		m_Name = "Gust";
		m_Type = Air;
		BasePower = 40;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Gust.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Air };
	}
	virtual ~Gust() {}
protected:
};
class Scary_Face : public Move {
public:
	Scary_Face()
	{
		m_Move = _SQ_Scary_Face;
		m_Name = "Scary Face";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\ScaryFace.bmp", BattleFunctions::astVars, 100, 220, 20, 20, 0, 55));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Telekinetic };
	}
	virtual ~Scary_Face() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Bubble : public Move {
public:
	Bubble()
	{
		m_Move = _SQ_Bubble;
		m_Name = "Bubble";
		m_Type = Water;
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\WaterAttack.bmp", BattleFunctions::astVars, 100, 140, 20, 20, 0, 35));
		m_TeachAbleTypes = std::vector<_SQType>{ Water };
	}
	virtual ~Bubble() {}
protected:
};
class Bite : public Move {
public:
	Bite()
	{
		m_Move = _SQ_Bite;
		m_Name = "Bite";
		m_Type = Melee;
		BasePower = 75;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Bite.bmp", BattleFunctions::astVars, 100, 60, 20, 20, 0, 35));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Grass };
	}
	virtual ~Bite() {}
protected:
};
class Loose_Match : public Move {
public:
	Loose_Match()
	{
		m_Move = _SQ_Loose_Match;
		m_Name = "Loose Match";
		m_Type = Fire;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\LooseMatch.bmp", BattleFunctions::astVars, 100, 160, 20, 20, 0, 40));
		m_TeachAbleTypes = std::vector<_SQType>{ Fire };
	}
	virtual ~Loose_Match() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Waterboard : public Move {
public:
	Waterboard()
	{
		m_Move = _SQ_Waterboard;
		m_Name = "Waterboard";
		m_Type = Water;
		BasePower = 90;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Waterboard.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Water };
	}
	virtual ~Waterboard() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Marked : public Move {
public:
	Marked()
	{
		m_Move = _SQ_Marked;
		m_Name = "Marked";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Marked.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee };
	}
	virtual ~Marked() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Skull_Pierce : public Move {
public:
	Skull_Pierce()
	{
		m_Move = _SQ_Skull_Pierce;
		m_Name = "Skull Pierce";
		m_Type = Metal;
		BasePower = 100;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SkullPiercer.bmp", BattleFunctions::astVars, 160, 100, 20, 20, 0, 40));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Metal };
	}
	virtual ~Skull_Pierce() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Ciggie_Rain : public Move {
public:
	Ciggie_Rain()
	{
		m_Move = _SQ_Ciggie_Rain;
		m_Name = "Ciggie Rain";
		m_Type = Air;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\CiggieRain.bmp", BattleFunctions::astVars, 100, 180, 20, 20, 0, 45));
		m_TeachAbleTypes = std::vector<_SQType>{ Fire, Air, Melee};
	}
	virtual ~Ciggie_Rain() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Bee_Sting : public Move {
public:
	Bee_Sting()
	{
		m_Move = _SQ_Bee_Sting;
		m_Name = "Bee Sting";
		m_Type = Air;
		BasePower = 60;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BeeSting.bmp", BattleFunctions::astVars, 100, 100, 20, 20, 0, 25));
		m_TeachAbleTypes = std::vector<_SQType>{ Air };
	}
	virtual ~Bee_Sting() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Bulk_Up : public Move {
public:
	Bulk_Up()
	{
		m_Move = _SQ_Bulk_Up;
		m_Name = "Bulk Up";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BulkUp.bmp", BattleFunctions::astVars, 120, 140, 20, 20, 0, 42));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Air, Telekinetic, Metal, Water, Fire, Grass, Electric };
	}
	virtual ~Bulk_Up() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
class Rabbit_Food : public Move {
public:
	Rabbit_Food()
	{
		m_Move = _SQ_Rabbit_Food;
		m_Name = "Rabbit Food";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\RabbitFood.bmp", BattleFunctions::astVars, 200, 160, 20, 20, 0, 73));
		m_TeachAbleTypes = std::vector<_SQType>{ Melee, Snow };
	}
	virtual ~Rabbit_Food() {}
	void Execute(Character* Attacker, Character* Defender, FightWindow* f) override;
protected:
};
#pragma endregion






class SQMoveFunctions {
public:
	static Move* IntToMove(int i);
};
