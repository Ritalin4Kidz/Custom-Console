#pragma once

#include <string>
#include "SYDEFileDefaults.h"
#include <vector>

using namespace std;



class SRLNameGenerator
{
public:
	static string generateRandomOriginCountry();
	static string generateRandomName();
	static string generateRandomTeamName();

	static string generateRandomHomeGround();

	static string generateRandomTeamNameSafe();

	static void generateAndAddToVector(vector<string>& vec);
	static string getTimeBasedOffRoundSizeAndGame(int roundSize, int game);
private:
	static string generateRandomFirstName();
	static string generateRandomMiddleName();
	static string generateRandomLastName();

	static string generateRandomCity();
	static string generateRandomTeam();

	static vector<string> FirstNames;
	static vector<string> MiddleNames;
	static vector<string> LastNames;
	static vector<string> CityNames;
	static vector<string> HomeGroundStart;
	static vector<string> HomeGroundEnd;
	static vector<string> TeamNames;
	static vector<string> countriesOfOrigin;

	static vector<vector<string>> BetSentence;
};