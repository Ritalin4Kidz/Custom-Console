#pragma once
#include "SYDEstdafx.h"
#include "json.hpp"

using nlohmann::json;

class Bounties {
public:
	static void Save();
	static void Load();

	static void UnlockBounty(string msg, bool &bounty);

	static bool CrabBounty_Unlocked;
};