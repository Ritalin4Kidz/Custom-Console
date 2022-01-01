#pragma once
#include "Scene.h"
#include "SYDEstdafx.h"
#include "StatusAnimations.h"
#include "Character.h"
#include "SYDEQuestGame.h"
#include "Bounties.h"

struct Char_Stats {
	Char_Stats(_SQType type, int health, int atk, int def, int matk, int mdef) { m_hp = health; m_atk = atk; m_def = def; m_matk = matk; m_mdef = mdef; m_Type = type; m_speed = 30; }
	Char_Stats(_SQType type, int health, int atk, int def, int matk, int mdef, int speed) { m_hp = health; m_atk = atk; m_def = def; m_matk = matk; m_mdef = mdef; m_Type = type; m_speed = speed; }
	_SQType m_Type;
	int m_hp;
	int m_atk;
	int m_def;
	int m_matk;
	int m_mdef;
	int m_speed;
};

class BuildCharacter : public GameScene {
public:
	BuildCharacter();
	~BuildCharacter();
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;

	void SetPlayer();
private:
	SYDEAdaptiveMenu _TypeOptions;

	vector<Char_Stats> Character_Stats = vector<Char_Stats>{
		//WATER
		Char_Stats(Water, 100,100,120,70,30),
		//GRASS
		Char_Stats(Grass, 100,70,70,120,100),
		//FIRE
		Char_Stats(Fire, 90,100,55,100,55),
		//METAL
		Char_Stats(Metal, 150,110,110,20,80),
		//MELEE
		Char_Stats(Melee, 70,200,200,15,15),
		//ELECTRIC
		Char_Stats(Electric, 100,100,30,100,70),
		//TELEKINESIS
		Char_Stats(Telekinetic, 40,115,115,115,115),
		//SNOW
		Char_Stats(Snow, 120,20,20,120,120),
		//AIR
		Char_Stats(Air, 30,150,50,150,20,70),
		//CRAB
		Char_Stats(Water, 70,100,100,40,40),
	};
};