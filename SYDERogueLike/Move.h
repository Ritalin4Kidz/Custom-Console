#pragma once

#include "GameTypes.h"
#include <string>
#include "SYDEEngineAssets.h"
#include "json.hpp"
using json = nlohmann::json;
/*
TODO: DESIGN HOW MOVES WILL WORK PROPERLY
*/
class Move {
public:
	Move() {}
	_SQType getType() { return m_Type; }
	std::string getName() { return m_Name; }
	/// <summary>
	/// Execute the move
	/// </summary>
	/// <param name="Attacker"></param>
	/// <param name="Defender"></param>
	/// <param name="tag">Optional parameter if we need toi return anything</param>

	//CAN BE OVERRIDEN BY OTHER MOVES
	virtual bool isSuccessful(json* Attacker, json* Defender, std::string* tag);

	float getPower() { return BasePower; }
	float BaseDamageCalculation(json* Attacker, json* Defender, float Bonus_Damage, bool usesMagic);

	bool setStatus(_SQStatus newStatus, json* charac, int chanceRoll);

	virtual bool ExecuteMove(json* Attacker, json* Defender, std::string* tag);

	void refreshUsages() { usagesLeft = maxUsages; }

	CustomAnimationAsset getAnimation() { return m_Animation; }
	ConsoleWindow drawAnimation(ConsoleWindow window, Vector2 point) { return m_Animation.draw_asset(window, point); }

	void resetAnimation() { m_Animation.setFrame(0); }

	/// <summary>
	/// LAST EFFORT MOVES CAN BE USED WHEN ALL OTHER MOVES USED UP
	/// THEY HAVE NO USAGE LIMIT
	/// </summary>
	/// <returns></returns>
	bool isLastEffortMove() { return lastEffortMove; }

	virtual void decrementUsages() { usagesLeft--; }
	int getUsagesLeft() { return usagesLeft; }

	int getMaxUsages() { return maxUsages; }

	string getTMId() { return m_TM_Identifier; }

protected:
	virtual void Execute(json* Attacker, json* Defender, std::string* tag);
	_SQType m_Type;
	std::string m_Name;
	float BasePower;
	std::string m_Info = "";

	std::string m_TM_Identifier = "";

	int usagesLeft = 0;
	int maxUsages = 0;
	int m_Accuracy = 100;
	bool lastEffortMove = false;

	bool useMagicAttack = false;

	CustomAnimationAsset m_Animation;
};

class BattleFunctions {
public:
	static float DetermineMultiplier(Move* Attack, _SQType Defender);
	static AssetsClass astVars;
};