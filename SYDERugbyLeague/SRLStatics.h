#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;


class SRLStatics
{
public:
	static int loadConstSetting(string key, int defaultVal)
	{
		try
		{
			std::ifstream ifs{ "EngineFiles\\Settings\\luckValues.json" };
			json save_file = json::parse(ifs);
			return save_file[key];
		}
		catch (exception ex)
		{
			////
		}
		return defaultVal;
	}
};