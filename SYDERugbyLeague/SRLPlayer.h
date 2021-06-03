#pragma once
#include <string>
#include <vector>

using namespace std;

class SRLPlayer {
public:
	SRLPlayer();

	virtual ~SRLPlayer();
private:

	string m_PlayerName;
	//HOW FAST THE PLAYER RUNS
	int m_BaseSpeed;
	//GENERAL ATTACKING STAT
	int m_BaseAttack;
	//GENERAL DEFENSIVE STAT
	int m_BaseDefence;
	//GENERAL STAMINA PERCENTAGE
	int m_BaseStamina;
};