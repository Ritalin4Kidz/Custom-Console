#pragma once
#include "Move.h"
class SmokeMoveType : public Move {
public:
	SmokeMoveType(){}

	void doDefenseDrop(json* Attacker, json* Defender, std::string* tag);

	bool ExecuteMove(json* Attacker, json* Defender, std::string* tag) override;
protected:
};