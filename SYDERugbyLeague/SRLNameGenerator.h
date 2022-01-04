#pragma once

#include <string>
#include "SYDEFileDefaults.h"
#include <deque>

using namespace std;



class SRLNameGenerator
{
public:
	static string generateRandomOriginCountry();
	static string generateRandomName();
	static string generateRandomTeamName();

	static string generateRandomHomeGround();

	static string generateRandomTeamNameSafe();

	static void generateAndAddToVector(deque<string>& vec);
	static string getTimeBasedOffRoundSizeAndGame(int roundSize, int game);
private:
	static string generateRandomFirstName();
	static string generateRandomMiddleName();
	static string generateRandomLastName();

	static string generateRandomCity();
	static string generateRandomTeam();

	static deque<string> FirstNames;
	static deque<string> MiddleNames;
	static deque<string> LastNames;
	static deque<string> CityNames;
	static deque<string> HomeGroundStart;
	static deque<string> HomeGroundEnd;
	static deque<string> TeamNames;
	static deque<string> countriesOfOrigin;

	static deque<deque<string>> BetSentence;
};