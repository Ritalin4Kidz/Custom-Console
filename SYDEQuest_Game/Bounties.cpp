#include "Bounties.h"

bool Bounties::CrabBounty_Unlocked = false;

void Bounties::Save()
{
	//TODO
	json save_file;
	save_file["Bounties"]["CrabUnlocked"] = CrabBounty_Unlocked;

	std::ofstream ofs("EngineFiles\\Settings\\SQ_SaveFile.sc");
	ofs << save_file;
}

void Bounties::Load()
{
	try {
		std::ifstream ifs{ "EngineFiles\\Settings\\SQ_SaveFile.sc" };
		json save_file = json::parse(ifs);

		CrabBounty_Unlocked = save_file["Bounties"]["CrabUnlocked"].get<bool>();
	}
	catch (std::exception e)
	{

	}
}

void Bounties::UnlockBounty(string msg, bool &bounty)
{
	if (!bounty)
	{
		bounty = true;
		//display temp label
		Save();
	}
}
