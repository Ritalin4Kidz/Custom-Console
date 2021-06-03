#pragma once
#include <string>
#include <vector>

using namespace std;

class SRLPlayer {
public:
	SRLPlayer();
	SRLPlayer(string name, int speed, int attack, int defence);


	virtual ~SRLPlayer();


	string getName() { return m_PlayerName; }

	int getSpeed() { return m_BaseSpeed; }

	int getAttack() { return m_BaseAttack; }

	int getDefence() { return m_BaseDefence; }
private:

	string m_PlayerName;
	//HOW FAST THE PLAYER RUNS
	int m_BaseSpeed;
	//GENERAL ATTACKING STAT
	int m_BaseAttack;
	//GENERAL DEFENSIVE STAT
	int m_BaseDefence;
};