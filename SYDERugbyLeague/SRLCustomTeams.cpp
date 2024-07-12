#include "SRLCustomTeams.h"

SRLTeam SRLCustomTeamGenerator::generateCustomTeamFreebeeNetwork(string& team)
{
	vector<SRLPlayer> TeamList;
	TeamList.push_back(SRLPlayer("Callum Hands", "Australia", 45, 88, 35, 79, 83, 99, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 4));
	TeamList.push_back(SRLPlayer("Luke Alexander", "Australia", 85, 65, 75, 29, 33, 87, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 1));
	TeamList.push_back(SRLPlayer("Peter Waterhouse", "Australia", 50, 78, 72, 48, 22, 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 40));
	TeamList.push_back(SRLPlayer("Ali Viana", "Australia", 95, 93, 65, 20, 25, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 68));
	TeamList.push_back(SRLPlayer("Ashleigh Allsopp", "Australia", 65, 68, 95, 29, 23, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, PURPLE_PURPLE_BG, 17));
	TeamList.push_back(SRLPlayer("Ryan Mallett", "Australia", 25, 48, 85, 39, 45, 63, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 5));
	TeamList.push_back(SRLPlayer("Simon Armstrong", "Australia", 78, 22, 78, 22, 78, 22, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 38));
	TeamList.push_back(SRLPlayer("Lindsay Hands", "Australia", 25, 38, 75, 55, 55, 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 11));
	TeamList.push_back(SRLPlayer("Kelin Miao", "Australia", 99, 99, 25, 21, 33, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 33));
	TeamList.push_back(SRLPlayer("Kyle Phillips", "Australia", 59, 59, 59, 59, 59, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 28));
	TeamList.push_back(SRLPlayer("Andrew Russell", "Australia", 45, 88, 35, 79, 83, 99, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 15));
	TeamList.push_back(SRLPlayer("Cameron Rose", "Australia", 65, 34, 88, 30, 23, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 18));
	TeamList.push_back(SRLPlayer("Dominic Chicocki", "Australia", 25, 35, 78, 65, 57, 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 70));
	TeamList.push_back(SRLPlayer("Trixie Emerson", "Australia", 23, 24, 75, 45, 63, 35, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 55));
	TeamList.push_back(SRLPlayer("Addison Stewart", "Australia", 90, 90, 90, 21, 22, 50, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 3));
	TeamList.push_back(SRLPlayer("Alex Armstrong", "Australia", 22, 78, 22, 78, 22, 78, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 2));
	TeamList.push_back(SRLPlayer("Mitchell Lynn", "Australia", 35, 50, 80, 80, 33, 67, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 20));
	SRLTeam FreebeeNetwork = SRLTeam(TeamList, "Freebee Network", "Suoonnia Park");
	FreebeeNetwork.setJersey(BRIGHTWHITE_BRIGHTWHITE_BG, BRIGHTRED_BRIGHTRED_BG, YELLOW_YELLOW_BG, 4);
	FreebeeNetwork.setLogoCustom("TeamFreebee");
	team = "SRL_FREEBEE_NETWORK";
	return FreebeeNetwork;
}

SRLTeam SRLCustomTeamGenerator::generateCustomTeamAusmusicCommunity(string& team)
{
	vector<SRLPlayer> TeamList;
	TeamList.push_back(SRLPlayer("Psychopanda", "Australia", 75, 48, 25, 29, 63, 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 59));
	TeamList.push_back(SRLPlayer("Puddinghead", "Australia", 85, 65, 75, 29, 33, 87, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 9));
	TeamList.push_back(SRLPlayer("iMagic", "United States", 50, 78, 72, 48, 22, 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 41));
	TeamList.push_back(SRLPlayer("Efanga", "Australia", 95, 93, 65, 20, 25, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 38));
	TeamList.push_back(SRLPlayer("Connor Green", "Australia", 65, 68, 95, 29, 23, 59, GREEN_GREEN_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 19));
	TeamList.push_back(SRLPlayer("Nige", "Australia", 25, 48, 85, 39, 45, 63, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 0));
	TeamList.push_back(SRLPlayer("Reuben", "Australia", 78, 22, 78, 22, 78, 22, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 29));
	TeamList.push_back(SRLPlayer("Franbae", "Australia", 25, 38, 75, 55, 55, 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 16));
	TeamList.push_back(SRLPlayer("Hamishwich", "Australia", 99, 99, 25, 21, 33, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 33));
	TeamList.push_back(SRLPlayer("Mikayler", "Australia", 59, 59, 59, 59, 59, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 17));
	TeamList.push_back(SRLPlayer("Ellipsis", "Australia", 45, 88, 35, 79, 83, 99, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 15));
	TeamList.push_back(SRLPlayer("Jooshr!", "Australia", 65, 34, 88, 30, 23, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 18));
	TeamList.push_back(SRLPlayer("Glassesboi", "Australia", 25, 35, 78, 65, 57, 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 34));
	TeamList.push_back(SRLPlayer("Spencer", "Australia", 23, 24, 75, 45, 63, 35, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 1));
	TeamList.push_back(SRLPlayer("Rit@lin", "Australia", 90, 90, 90, 21, 22, 50, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 20));
	TeamList.push_back(SRLPlayer("Zombino", "Australia", 79, 78, 72, 78, 72, 78, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 2));
	TeamList.push_back(SRLPlayer("Hingers", "Australia", 35, 50, 80, 80, 33, 67, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 3));
	SRLTeam AusMusic = SRLTeam(TeamList, "AusMusic Community", "AusMusic Super Stadium");
	AusMusic.setJersey(LIGHTGREY_LIGHTGREY_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, 70);
	AusMusic.setLogoCustom("Ausmusic");
	team = "SRL_AUSMUSIC_TEAM";
	return AusMusic;
}

SRLTeam SRLCustomTeamGenerator::generateCustomTeamMinimmeCommunity(string& team)
{
	//TODO: Properly adjust variables
	vector<SRLPlayer> TeamList;
	TeamList.push_back(SRLPlayer("Minimme", "Australia", 75, 48, 25, 29, 63, 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 59));
	TeamList.push_back(SRLPlayer("Arcana", "England", 85, 65, 75, 29, 33, 87, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 9));
	TeamList.push_back(SRLPlayer("Xindictive", "United States", 50, 78, 72, 48, 22, 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 41));
	TeamList.push_back(SRLPlayer("Golden Bolt", "Australia", 95, 93, 65, 20, 25, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 38));
	TeamList.push_back(SRLPlayer("Evilchickon", "Australia", 65, 68, 95, 29, 23, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 19));
	TeamList.push_back(SRLPlayer("Firstforecast", "United States", 25, 48, 85, 39, 45, 63, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 0));
	TeamList.push_back(SRLPlayer("Dr. Smoothy", "United States", 78, 22, 78, 22, 78, 22, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 29));
	TeamList.push_back(SRLPlayer("Jordan", "United States", 25, 38, 75, 55, 55, 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 16));
	TeamList.push_back(SRLPlayer("Labcat", "United States", 99, 99, 25, 21, 33, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 33));
	TeamList.push_back(SRLPlayer("Tricksmusic", "United States", 59, 59, 59, 59, 59, 59, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 17));
	TeamList.push_back(SRLPlayer("Jdthmas", "United States", 45, 88, 35, 79, 83, 99, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 15));
	TeamList.push_back(SRLPlayer("Schelgo", "United States", 65, 34, 88, 30, 23, 49, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 18));
	TeamList.push_back(SRLPlayer("Jeff Schleg", "United States", 25, 35, 78, 65, 57, 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 34));
	TeamList.push_back(SRLPlayer("Dominic", "United States", 23, 24, 75, 45, 63, 35, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 1));
	TeamList.push_back(SRLPlayer("Rit@lin", "Australia", 90, 90, 90, 21, 22, 50, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 20));
	TeamList.push_back(SRLPlayer("Mrs. Minimme", "Australia", 79, 78, 72, 78, 72, 78, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 2));
	TeamList.push_back(SRLPlayer("Deleted User", "?????", 35, 50, 80, 80, 33, 67, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 3));
	SRLTeam MinimmeCommunity = SRLTeam(TeamList, "Minimme Community", "West Dinsey Oval");
	MinimmeCommunity.setJersey(BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, BRIGHTWHITE_BRIGHTWHITE_BG, 11);
	MinimmeCommunity.setLogoCustom("Minimme");
	team = "SRL_MINIMME_COMM";
	return MinimmeCommunity;
}

SRLTeam SRLCustomTeamGenerator::generateRandomCustomTeam(string& team)
{
	int chance = rand() % 3;
	switch (chance)
	{
	case 0:
		return generateCustomTeamFreebeeNetwork(team);
	case 1:
		return generateCustomTeamAusmusicCommunity(team);
	case 2:
		return generateCustomTeamMinimmeCommunity(team);
	}
	return generateCustomTeamFreebeeNetwork(team);
}

SRLTeam SRLCustomTeamGenerator::generateNRLPPBaseRandomTeam()
{
	vector<SRLPlayer> TeamList;
	//SPEED, ATTACK, DEFENCE, KICK, GOAL, HANDLE
	TeamList.push_back(SRLPlayer("Fullback", "Australia", (rand() % 10 + 85), (rand() % 10 + 85), 45, 40, (rand() % 40 + 20), 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 59));
	TeamList.push_back(SRLPlayer("Left Wing", "Australia", 70, (rand() % 10 + 85), 55, 40, (rand() % 40 + 20), 70, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 9));
	TeamList.push_back(SRLPlayer("Left Centre", "Australia",60, 75, 65, 50, (rand() % 40 + 20), 70, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 8));
	TeamList.push_back(SRLPlayer("Right Centre", "Australia", 60, 75, 65, 50, (rand() % 40 + 20), 70, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 14));
	TeamList.push_back(SRLPlayer("Right Wing", "Australia", 70, (rand() % 10 + 85), 55, 40, (rand() % 40 + 20), 70, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 17));

	TeamList.push_back(SRLPlayer("Five Eigth", "Australia", 55, 60, 60, 80, (rand() % 40 + 20), 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 23));
	TeamList.push_back(SRLPlayer("Halfback", "Australia", 60, 65, 75, (rand() % 10 + 85), (rand() % 40 + 20), 65, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 27));

	TeamList.push_back(SRLPlayer("Prop", "Australia", 60, 60, (rand() % 10 + 85), 35, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 30));
	TeamList.push_back(SRLPlayer("Hooker", "Australia", 60, 65, 75, 65, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 6));
	TeamList.push_back(SRLPlayer("Prop", "Australia", 60, 60, (rand() % 10 + 85), 35, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 50));
	TeamList.push_back(SRLPlayer("Second Row", "Australia", 60, 60, (rand() % 10 + 85), 35, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 17));
	TeamList.push_back(SRLPlayer("Second Row", "Australia", 60, 60, (rand() % 10 + 85), 35, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 1));
	TeamList.push_back(SRLPlayer("Lock", "Australia", 60, 60, (rand() % 10 + 85), 35, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 2));

	TeamList.push_back(generateNRLRandomInterchange("Interchange 1"));
	TeamList.push_back(generateNRLRandomInterchange("Interchange 2"));
	TeamList.push_back(generateNRLRandomInterchange("Interchange 3"));
	TeamList.push_back(generateNRLRandomInterchange("Interchange 4"));

	TeamList.push_back(SRLPlayer("Unknown", "Australia", 75, 48, 25, 29, (rand() % 40 + 20), 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 35));
	TeamList.push_back(SRLPlayer("Unknown", "Australia", 75, 48, 25, 29, (rand() % 40 + 20), 69, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 42));
	TeamList.push_back(SRLPlayer("Unknown", "Australia", 75, 48, 25, 29, (rand() % 40 + 20), 64, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 42));
	return SRLTeam(TeamList, SRLNameGenerator::generateRandomTeamNameSafe(), SRLNameGenerator::generateRandomHomeGround());
}

SRLPlayer SRLCustomTeamGenerator::generateNRLRandomInterchange(string playerName)
{
	int num = rand() % 4;
	if (num == 0)
	{
		return SRLPlayer(playerName, "Australia", 64, 64, 64, 64, (rand() % 40 + 20), 64, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 13);
	}
	if (num == 1)
	{
		return SRLPlayer(playerName, "Australia", 90, 75, 34, 34, (rand() % 40 + 20), 55, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 13);
	}
	if (num == 2)
	{
		return SRLPlayer(playerName, "Australia", 60, 60, 60, 90, (rand() % 40 + 20), 90, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 13);
	}
	if (num == 3)
	{
		return SRLPlayer(playerName, "Australia", 30, 40, 90, 20, (rand() % 40 + 20), 90, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 13);
	}
	return 	SRLPlayer(playerName, "Australia", 64, 64, 64, 64, (rand() % 40 + 20), 64, BRIGHTYELLOW_BRIGHTYELLOW_BG, BLUE_BLUE_BG, LIGHTGREY_LIGHTGREY_BG, 13);
}
