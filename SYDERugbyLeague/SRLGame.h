#pragma once
#include <string>
#include <vector>
#include "SRLTeam.h"
using namespace std;
class SRLGame {
public:
	SRLGame();

	virtual ~SRLGame();
private:

	SRLTeam m_HomeTeam;
	SRLTeam m_AwayTeam;

};