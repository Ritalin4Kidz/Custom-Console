#include "EnchantmentMove.h"
bool EnchantmentMove::isSuccessful(json* Attacker, json* Defender, std::string* tag)
{
    return static_cast<_SQStatus>(Attacker->at("status").get<int>()) != Status_Enchanted;
}

void EnchantmentMove::Execute(json* Attacker, json* Defender, std::string* tag)
{
    _SQStatus status = static_cast<_SQStatus>(Attacker->at("status").get<int>());

    Attacker->at("status") = static_cast<int>(Status_Enchanted);
}
