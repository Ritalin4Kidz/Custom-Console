#include "PotionItem.h"

void PotionItem::Execute(json* Attacker, json* Defender, std::string* tag)
{
    int healthAttk = Attacker->at("health").get<int>();
    int maxHealthAttk = Attacker->at("maxHealth").get<int>();

    healthAttk += 20;

    if (healthAttk > maxHealthAttk)
    {
        healthAttk = maxHealthAttk;
    }

    Attacker->at("health") = healthAttk;
}

void PotionItem::useItem(json* Attacker)
{
    int healthAttk = Attacker->at("health").get<int>();
    int maxHealthAttk = Attacker->at("maxHealth").get<int>();

    healthAttk += 20;

    if (healthAttk > maxHealthAttk)
    {
        healthAttk = maxHealthAttk;
    }

    Attacker->at("health") = healthAttk;
}
