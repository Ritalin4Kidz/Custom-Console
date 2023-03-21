#include "SourNoteMove.h"

bool SourNoteMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
    //WE NEED TO VALIDATE THE JSON
 //THEN WE CAN USE THAT DATA TO AFFECT THE MOVE
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, static_cast<_SQType>(Defender->at("type").get<int>()));
    if (Bonus_Damage == 0)
    {
        return false;
    }
    int randNum = rand() % 100;

	_SQStatus status = static_cast<_SQStatus>(Defender->at("status").get<int>());
	return status == Status_Sleep && randNum < m_Accuracy;
}
