#include "SmokeBreakMove.h"

void SmokeBreakMove::Execute(Character* Attacker, Character* Defender)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(), Attacker->getDefence(), Bonus_Damage);
    Attacker->AddHealth(Attacker->getMaxHealth() / 5);
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (Attacker->getDefence() > 5 && Attacker->getAbility() != Ability_ChainSmoker)
    {
        Attacker->setDefence(Attacker->getDefence() - 1);
        if (Attacker->getDefence() < 5)
        {
            Attacker->setDefence(5);
        }
    }
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}
