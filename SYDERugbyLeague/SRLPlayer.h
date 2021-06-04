#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "SYDEFileDefaults.h"
using namespace std;
using json = nlohmann::json;
class SRLPlayer {
public:
	SRLPlayer();
	SRLPlayer(string name, int speed, int attack, int defence);


	virtual ~SRLPlayer();


	string getName() { return m_PlayerName; }
	void setName(string name) { m_PlayerName = name; }
	int getSpeed() { return m_BaseSpeed; }

	int getAttack() { return m_BaseAttack; }

	int getDefence() { return m_BaseDefence; }

	int getID() { return id; }

	void loadPlayer(string path);
	void savePlayer();
private:

	string m_PlayerName;
	//HOW FAST THE PLAYER RUNS
	int m_BaseSpeed;
	//GENERAL ATTACKING STAT
	int m_BaseAttack;
	//GENERAL DEFENSIVE STAT
	int m_BaseDefence;


	int id = 0;
};