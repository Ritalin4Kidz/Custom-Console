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

	static string generateRandomTeamNameSafe();

private:
	static string generateRandomFirstName();
	static string generateRandomLastName();

	static string generateRandomCity();
	static string generateRandomTeam();

	static vector<string> FirstNames;
	static vector<string> LastNames;
	static vector<string> CityNames;
	static vector<string> TeamNames;
	static vector<string> countriesOfOrigin;
};