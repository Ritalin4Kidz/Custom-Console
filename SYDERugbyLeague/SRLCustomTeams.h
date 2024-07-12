#pragma once
#include "SRLTeam.h"
#include "SRLNameGenerator.h"

class SRLCustomTeamGenerator
{
public:
	static SRLTeam generateCustomTeamFreebeeNetwork(string& team);
	static SRLTeam generateCustomTeamAusmusicCommunity(string& team);
	static SRLTeam generateCustomTeamMinimmeCommunity(string& team);

	static SRLTeam generateRandomCustomTeam(string& team);

	static SRLTeam generateNRLPPBaseRandomTeam();

	static SRLPlayer generateNRLRandomInterchange(string playerName);
};