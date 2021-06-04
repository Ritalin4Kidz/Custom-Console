#pragma once
#include <string>
#include <vector>

#include "SRLPlayer.h"

using namespace std;


class SRLTeam {
public:
	SRLTeam();
	SRLTeam(string name) {m_Name= name;}
	SRLTeam(vector<SRLPlayer> a_TeamList, string name);
	virtual ~SRLTeam();

	string Interchange();

	SRLPlayer getRandomPlayer();

	string getName() { return m_Name; }
	void setName(string name) { m_Name = name; }
	void loadTeam(string path);
	void saveTeam();

private:

	string m_Name;

	vector<SRLPlayer> m_TeamList = vector<SRLPlayer>();
	int m_Interchanges = 0;
};