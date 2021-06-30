#pragma once
#include "SRLTeam.h"


class SRLCustomTeamGenerator
{
public:
	static SRLTeam generateCustomTeamFreebeeNetwork(string& team);
	static SRLTeam generateCustomTeamAusmusicCommunity(string& team);

	static SRLTeam generateRandomCustomTeam(string& team);
};