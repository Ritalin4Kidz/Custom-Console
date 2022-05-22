#include "Character.h"
AssetsClass BattleFunctions::astVars = AssetsClass();
int Player::minimumDefence = 3;
int Player::minimumAttack = 5;

int LevelUPRates::FAST_LEVEL_UP_GROUP_START = 200;
int LevelUPRates::NORMAL_LEVEL_UP_GROUP_START = 800;
int LevelUPRates::SLOW_LEVEL_UP_GROUP_START = 1600;

float LevelUPRates::FAST_LEVEL_UP_GROUP_RATE = 1.25f;
float LevelUPRates::NORMAL_LEVEL_UP_GROUP_RATE = 1.5f;
float LevelUPRates::SLOW_LEVEL_UP_GROUP_RATE = 2.0f;


float BattleFunctions::DetermineMultiplier(Move* Attack, Character* Defender)
{
    if (Attack->getType() == Water)
    {
        switch (Defender->getType())
        {
            case Fire:
                return 3.0f;
            case Grass:
                return 0.75f;
            case Metal:
                return 1.5f;
            case Electric:
                return 1.25f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Fire)
    {
        switch (Defender->getType())
        {
            case Grass:
                return 3.0f;
            case Water:
                return 0.5f;
            case Snow:
                return 2.0f;
            case Metal:
                return 2.5f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Grass)
    {
        switch (Defender->getType())
        {
            case Water:
                return 2.0f;
            case Fire:
                return 0.25f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Air)
    {
        switch (Defender->getType())
        {
            case Melee:
                return 1.5f;
            case Grass:
                return 2.5f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Metal)
    {
        switch (Defender->getType())
        {
            case Fire:
                return 0.5f;
            case Water:
                return 0.5f;
            case Metal:
                return 0.5f;
            case Telekinetic:
                return 3.0f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Melee)
    {
        switch (Defender->getType())
        {
            case Fire:
                return 1.25f;
            case Air:
                return 0.25f;
            case Melee:
                return 3.0f;
            case Telekinetic:
                return 0.5f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Electric)
    {
        switch (Defender->getType())
        {
            case Air:
                return 3.0f;
            case Electric:
                return 0;
            case Telekinetic:
                return 2;
            case Water:
                return 4;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Snow)
    {
        switch (Defender->getType())
        {
            case Fire:
                return 0.5f;
            case Grass:
                return 2.5f;
            case Telekinetic:
                return 2;
            case Air:
                return 3;
            case Metal:
                return 0.75f;
            default:
                return 1;
        }
    }
    else if (Attack->getType() == Telekinetic)
    {
        switch (Defender->getType())
        {
            case Melee:
                return 2.5f;
            case Telekinetic:
                return 0;
            case Air:
                return 2.25f;
            case Electric:
                return 1.25f;
            case Snow:
                return 0.25f;
            case Metal:
                return 0;
            default:
                return 1;
        }
    }
    return 1;
}

void Enemy::init(int lvl)
{
    for (int i = 0; i < lvl; i++)
    {
        this->AddHealth(3);
        int StatUpgrade = rand() % 4;
        switch (StatUpgrade)
        {
        case 0:
            this->m_Attack++;
        case 1:
            this->m_Defence++;
        case 2:
            this->m_MagicAttack++;
        case 3:
            this->m_MagicDefence++;
        }
    }
    this->setMaxHealth(this->getHealth());
}

int Character::getAttack(_SQType MoveType)
{
    if (getAbility() == Ability_NaturalBoost && MoveType == getType())
    {
        return m_Attack + 20;
    }
    return m_Attack;
}

int Character::getMagicAttack(_SQType MoveType)
{
    if (getAbility() == Ability_NaturalBoost && MoveType == getType())
    {
        return m_MagicAttack + 20;
    }
    return m_MagicAttack;
}

void Character::setStatus(_SQStatus _status)
{
    {
        if (m_Ability == Ability_Immunity)
        {
            m_Status == Status_None;
            return;
        }
        if (m_Status == Status_None)
            m_Status = _status;
    }
}

void Enemy::to_json(json& j)
{
  
    j = json{
        {"type",static_cast<int>(m_Type)},
        {"health",m_Health},
        {"maxHealth",m_MaxHealth},
        {"attack",m_Attack},
        {"defence",m_Defence},
        {"magicAttack",m_MagicAttack},
        {"magicDefence",m_MagicDefence},
        {"speed",m_Speed},
        {"level",m_Level},
        {"name",m_Name},
        {"statIncrease",static_cast<int>(m_StatToIncrease)},
        {"ability", static_cast<int>(m_Ability)},
        {"tag",Tag},
        {"runchance", runChance}
   };
  
}

void Enemy::from_json(const json& j)
{
    this->m_Name = j.at("name").get<std::string>();
    this->Tag = j.at("tag").get<std::string>();
    this->m_Type = static_cast<_SQType>(j.at("type").get<int>());
    this->m_StatToIncrease = static_cast<_SQ_Stat_Increase>(j.at("statIncrease").get<int>());
    this->m_Ability = static_cast<_SQAbility>(j.at("ability").get<int>());
    this->m_Health = j.at("health").get<int>();
    this->m_MaxHealth =  j.at("maxHealth").get<int>();
    this->m_Attack = j.at("attack").get<int>();
    this->m_Defence = j.at("defence").get<int>();
    this->m_MagicAttack = j.at("magicAttack").get<int>();
    this->m_MagicDefence = j.at("magicDefence").get<int>();
    this->m_Speed = j.at("speed").get<int>();
    this->m_Level = j.at("level").get<int>();
    this->runChance = j.at("runchance").get<int>();
}

#pragma region EnemyInits
Crab::Crab(int lvl)
{
    this->setLevel(lvl);
    this->setHealth(70); //70
    this->setAttack(100); //170
    this->setDefence(100); //270
    this->setMagicAttack(40); //310
    this->setMagicDefence(40); //350
    this->setName("Crab");
    this->setType(Water);
    this->setStatToIncrease(STATINCREASE_ATTACK);
    this->setTag("CRAB;"
        + std::to_string(static_cast<int>(_SQ_Bone_Club)) + ";"
        + std::to_string(static_cast<int>(_SQ_Smoke_Break)) + ";"
        + std::to_string(static_cast<int>(_SQ_Slash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Entangle)) + ";"
        + std::to_string(static_cast<int>(_SQ_Growth)) + ";");
    this->init(lvl);
}
Smoking_Crab::Smoking_Crab(int lvl)
{
    this->runChance = 0;
    this->setLevel(lvl);
    this->setHealth(70); //70
    this->setAttack(100); //170
    this->setDefence(100); //270
    this->setMagicAttack(40); //310
    this->setMagicDefence(40); //350
    this->setName("Smoking Crab");
    this->setType(Water);
    this->setAbility(Ability_ChainSmoker);
    this->setTag("SMOKE_CRAB;"
        + std::to_string(static_cast<int>(_SQ_Water_Blast)) + ";"
        + std::to_string(static_cast<int>(_SQ_Smoke_Break)) + ";"
        + std::to_string(static_cast<int>(_SQ_Smoke_Cloud)) + ";"
        + std::to_string(static_cast<int>(_SQ_Wave_Splash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Ciggie_Rain)) + ";");
    this->init(lvl);
}
Orc::Orc(int lvl)
{
    //Define ORC Enemy Type Base Stats
    //TOTAL = 300
    this->setLevel(lvl);
    this->setHealth(30); //70
    this->setAttack(50); //120
    this->setDefence(100); //220
    this->setMagicAttack(70); //290
    this->setMagicDefence(10); //300
    this->setName("Orc");
    this->setType(Grass);
    this->setStatToIncrease(STATINCREASE_DEFENCE);
    this->setTag("ORC;"
        + std::to_string(static_cast<int>(_SQ_Bone_Club)) + ";"
        + std::to_string(static_cast<int>(_SQ_Smoke_Break)) + ";"
        + std::to_string(static_cast<int>(_SQ_Slash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Entangle)) + ";"
        + std::to_string(static_cast<int>(_SQ_Growth)) + ";");
    this->init(lvl);

}
Bee::Bee(int lvl)
{
    this->runChance = 0;
    this->setLevel(lvl);
    this->setHealth(30); //70
    this->setAttack(40); //170
    this->setDefence(20); //270
    this->setMagicAttack(10); //310
    this->setMagicDefence(10); //350
    this->setSpeed(90); //350
    this->setName("Bee");
    this->setType(Air);
    this->setStatToIncrease(STATINCEASE_SPEED);
    this->setAbility(Ability_Hasten);
    this->setTag("BEE;"
        + std::to_string(static_cast<int>(_SQ_Gust)) + ";"
        + std::to_string(static_cast<int>(_SQ_Garden)) + ";"
        + std::to_string(static_cast<int>(_SQ_Poison_Flower)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bee_Sting)) + ";"
        + std::to_string(static_cast<int>(_SQ_Slash)) + ";");
    this->init(lvl);
}
Freebee::Freebee(int lvl)
{
    this->runChance = 0;
    this->setLevel(lvl);
    this->setHealth(70); //70
    this->setAttack(120); //170
    this->setDefence(100); //270
    this->setMagicAttack(40); //310
    this->setMagicDefence(40); //350
    this->setSpeed(90); //350
    this->setName("Freebee");
    this->setType(Air);
    this->setAbility(Ability_Hasten);
    this->setTag("FREEBEE;"
        + std::to_string(static_cast<int>(_SQ_Gust)) + ";"
        + std::to_string(static_cast<int>(_SQ_Garden)) + ";"
        + std::to_string(static_cast<int>(_SQ_Poison_Flower)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bee_Sting)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bulk_Up)) + ";");
    this->init(lvl);
}
Rabbit::Rabbit(int lvl)
{
    this->runChance = 0;
    this->setLevel(lvl);
    this->setHealth(15);
    this->setAttack(70);
    this->setDefence(10);
    this->setMagicAttack(40);
    this->setMagicDefence(10);
    this->setSpeed(190);
    this->setName("Bunny");
    this->setType(Snow);
    this->setStatToIncrease(STATINCREASE_HEALTH);
    this->setAbility(Ability_Insomnia);
    this->setTag("RABBIT;"
        + std::to_string(static_cast<int>(_SQ_Rabbit_Food)) + ";"
        + std::to_string(static_cast<int>(_SQ_Snowball)) + ";"
        + std::to_string(static_cast<int>(_SQ_Garden)) + ";"
        + std::to_string(static_cast<int>(_SQ_Scary_Face)) + ";"
        + std::to_string(static_cast<int>(_SQ_Sing)) + ";");
    this->init(lvl);
}
Blue_Fish::Blue_Fish(int lvl)
{
    //Define FISH Enemy Type Base Stats
    //TOTAL = 230
    this->setLevel(lvl);
    this->setHealth(20); //30
    this->setAttack(40); //70
    this->setDefence(70); //140
    this->setMagicAttack(20); //160
    this->setMagicDefence(70); //230
    this->setSpeed(45);
    this->setName("Blue Fish");
    this->setType(Water);
    this->setStatToIncrease(STATINCREASE_HEALTH);
    this->setTag("BLUE_FISH;"
        + std::to_string(static_cast<int>(_SQ_Wave_Splash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Water_Blast)) + ";"
        + std::to_string(static_cast<int>(_SQ_Slash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Swarm)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bubble)) + ";");
    this->init(lvl);
}

Wolf::Wolf(int lvl)
{
    //Define FISH Enemy Type Base Stats
    //TOTAL = 330
    this->setLevel(lvl);
    this->setHealth(90); //90
    this->setAttack(110); //200
    this->setDefence(50); //250
    this->setMagicAttack(40); //290
    this->setMagicDefence(40); //330
    this->setName("Wolf");
    this->setType(Melee);
    this->setStatToIncrease(STATINCREASE_MAGIC_ATTACK);
    this->setTag("WOLF;"
        + std::to_string(static_cast<int>(_SQ_Bite)) + ";"
        + std::to_string(static_cast<int>(_SQ_Slash)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bone_Club)) + ";"
        + std::to_string(static_cast<int>(_SQ_Scary_Face)) + ";"
        + std::to_string(static_cast<int>(_SQ_Bulk_Up)) + ";");
    this->init(lvl);
}
#pragma endregion

#pragma region MoveDictionary

void Move::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

float Move::BaseDamageCalculation(int level, float AttackStat, float DefenceStat, float Bonus_Damage)
{
    //Can't Do Damage Regardless
    if (Bonus_Damage == 0)
    {
        return Bonus_Damage;
    }
    //RANGE BONUS DAMAGE
    float range = ((float)rand() / RAND_MAX) + 0.5;
    Bonus_Damage *= range; //RANGE BETWEEN 0.5-1.5 Multiplier

    //BASED OFF POKEMON https://bulbapedia.bulbagarden.net/wiki/Damage
    float damage_dealt = ((((((2 * level) / 5) + 2) * this->BasePower * (AttackStat / DefenceStat)) / 50) + 2) * Bonus_Damage;
    //MINIMUM OF 1 DAMAGE IF ATTACK CAN HIT
    if (damage_dealt < 1 && Bonus_Damage != 0)
    {
        damage_dealt = 1;
    }

    return damage_dealt;
}

std::string Move::toStatsJsonString()
{
    json j = json{
    {"type",static_cast<int>(m_Type)},
    {"basepower",BasePower},
    {"name",m_Name},
    {"teachable",m_TeachAbleTypes},
    {"info",m_Info}
    };
    return j.dump();
}

void Smoke_Break::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = ((Attacker->getAttack(this->getType()) / Defender->getDefence()) + this->BasePower) * Bonus_Damage;
    Attacker->AddHealth(Attacker->getMaxHealth() / 5);
    if (Attacker->getHealth() > Attacker->getMaxHealth())
    {
        Attacker->setHealth(Attacker->getMaxHealth());
    }
    //SMOKE ATTACKS GIVE HEALTH, BUT LOWER DEFENCE STAT
    if (Attacker->getDefence() > Player::getMinimumDefence() && Attacker->getAbility() != Ability_ChainSmoker)
    {
        Attacker->setDefence(Attacker->getDefence() - 1);
        if (Attacker->getDefence() < Player::getMinimumDefence())
        {
            Attacker->setDefence(Player::getMinimumDefence());
        }
    }
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Water_Blast::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    //float totalDamage = ((Attacker->getAttack() / Defender->getDefence()) + this->BasePower) * Bonus_Damage;
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Smoke_Cloud::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(),Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    Attacker->AddHealth(Attacker->getMaxHealth() / 10);
    if (Attacker->getHealth() > Attacker->getMaxHealth())
    {
        Attacker->setHealth(Attacker->getMaxHealth());
    }
    if (Attacker->getDefence() > Player::getMinimumDefence() && Attacker->getAbility() != Ability_ChainSmoker)
    {
        Attacker->setDefence(Attacker->getDefence() - 2);
        if (Attacker->getDefence() < Player::getMinimumDefence())
        {
            Attacker->setDefence(Player::getMinimumDefence());
        }
    }
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Self_Destruct::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    //CONGRATS, YOU JUST PLAYED YOURSELF
    if (Defender->getHealth() > 0)
    {
        Attacker->setHealth(0);
    }
}

void Entangle::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Lightning_Slime::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Water_Slime::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Fireball::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    //THAW OUT A FROZEN ENEMY, BUT DO MORE DAMAGE TO THEM IN THE PROCESS
    if (Defender->getStatus() == Status_Frozen)
    {
        Defender->clearStatus();
        f->AddFString(Defender->getName() + " Has Thawed Out");
        Bonus_Damage * 1.5f;
    }
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    int Chance_One = rand() % 3;
    int Chance_Two = rand() % 3;
    if (Chance_One == Chance_Two)
    {
        Defender->setStatus(Status_Burnt);
        f->AddFString(Defender->getName() + " Was Burnt");
    }
}

void Heal_Slime::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    Attacker->AddHealth(Attacker->getMaxHealth() / 2.5f);
    if (Attacker->getHealth() > Attacker->getMaxHealth())
    {
        Attacker->setHealth(Attacker->getMaxHealth());
    }
}

void Hope_Slime::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    int Chance_One = rand() % 20;
    int Chance_Two = rand() % 20;
    if (Chance_One == Chance_Two)
    {
        float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
        float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
        if (totalDamage > 0)
        {
            Defender->AddHealth(-totalDamage);
        }
    }
}

void Sudden_Cold::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    int Chance_One = rand() % 1;
    int Chance_Two = rand() % 1;

    //DESTROY CROPS
    json j;
    if (Attacker->getJSONTag() != "")
    {
        j = json::parse(Attacker->getJSONTag());
        if (j.find("Flowers_Placed") != j.end())
            j["Flowers_Placed"] = 0;

        std::string jsonData = j.dump();
        Attacker->setJSONTag(jsonData);
    }
    if (Defender->getJSONTag() != "")
    {
        j = json::parse(Defender->getJSONTag());
        if (j.find("Flowers_Placed") != j.end())
            j["Flowers_Placed"] = 0;

        std::string jsonData = j.dump();
        Defender->setJSONTag(jsonData);
    }




    if (Chance_One == Chance_Two)
    {
        Defender->setStatus(Status_Frozen);
        f->AddFString(Defender->getName() + " Was Frozen");
        if (Defender->getDefence() > Player::getMinimumDefence())
        {
            Defender->setDefence(Defender->getDefence() - 1);
            if (Defender->getDefence() < Player::getMinimumDefence())
            {
                Defender->setDefence(Player::getMinimumDefence());
            }
        }
    }
}

void Growth::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Multiplier = 1.0f;
    if (Attacker->getType() == Grass)
        Multiplier = 2.0f;

    Attacker->setAttack(Attacker->getAttack() + (1 * Multiplier));
    f->AddFString(Attacker->getName() + " Increased Attack");
    Attacker->setDefence(Attacker->getDefence() + (1 * Multiplier));
    f->AddFString(Attacker->getName() + " Increased Defence");
    Attacker->AddHealth(Attacker->getMaxHealth() / (10 / Multiplier));
    f->AddFString(Attacker->getName() + " Recovered Health");
    if (Attacker->getHealth() > Attacker->getMaxHealth())
    {
        Attacker->setHealth(Attacker->getMaxHealth());
    }

    //ADD 1 TO THE AMOUNT OF FLOWERS
    json j;
    if (Attacker->getJSONTag() != "")
        j = json::parse(Attacker->getJSONTag());

    int _FlowerAmt = 0;
    if (j.find("Flowers_Placed") != j.end())
        _FlowerAmt = j["Flowers_Placed"];

    _FlowerAmt++;
    j["Flowers_Placed"] = _FlowerAmt;

    std::string jsonData = j.dump();
    Attacker->setJSONTag(jsonData);

}

void Flashbang::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    if (Defender->getType() != Electric && Defender->getStatus() == Status_None)
    {
        Defender->setStatus(Status_Paralyzed);
        f->AddFString(Defender->getName() + " Is Paralyzed");
    }
    else
    {
        f->AddFString("Flashbang Failed");
    }
}

void Lightning_Punch::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    if (Attacker->getType() == Electric && Defender->getStatus() == Status_None)
    {
        Defender->setStatus(Status_Paralyzed);
        f->AddFString(Defender->getName() + " Was Paralyzed");
    }
}

void Lightning_Bolt::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    int Chance_One = rand() % 4;
    int Chance_Two = rand() % 4;
    if (Chance_One == Chance_Two && Defender->getStatus() == Status_None)
    {
        Defender->setStatus(Status_Paralyzed);
        f->AddFString(Defender->getName() + " Was Paralyzed");
    }
}


void Rainbow::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    if (Defender->getStatus() != Status_None)
    {
        Defender->clearStatus();
        f->AddFString(Defender->getName() + " Is Now Healthy");
    }
}

void Pitch_Black::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    if (Defender->getDefence() > Player::getMinimumDefence())
    {
        Defender->setDefence(Attacker->getDefence() - 2);
        if (Defender->getDefence() < Player::getMinimumDefence())
        {
            Defender->setDefence(Player::getMinimumDefence());
        }
    }
    f->AddFString(Defender->getName() + "'s Defence Down");
    int Chance_One = rand() % 3;
    int Chance_Two = rand() % 3;
    if (Defender->getStatus() == Status_None && Chance_One == Chance_Two)
    {
        Defender->setStatus(Status_Paralyzed);
        f->AddFString(Defender->getName() + " Is Paralyzed");
    }
}

void Bright_Idea::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    Attacker->setAttack(Attacker->getAttack() + 3);
    f->AddFString(Attacker->getName() + " Increased Attack");
    Attacker->setAttack(Attacker->getMagicAttack() + 3);
    f->AddFString(Attacker->getName() + " Increased Magic Atk");

    if (Attacker->getType() == Electric)
    {
        json j;
        if (Attacker->getJSONTag() != "")
            j = json::parse(Attacker->getJSONTag());

        int _ChargeAmt = 0;
        if (j.find("Bulb_Charges") != j.end())
            _ChargeAmt = j["Bulb_Charges"];

        _ChargeAmt++;
       j["Bulb_Charges"] = _ChargeAmt;

        std::string jsonData = j.dump();
        Attacker->setJSONTag(jsonData);
    }
}

void Shattered_Bulb::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    json j;
    if (Attacker->getJSONTag() != "")
        j = json::parse(Attacker->getJSONTag());

    int _ChargeAmt = 0;
    if (j.find("Bulb_Charges") != j.end())
        _ChargeAmt = j["Bulb_Charges"];

    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    if (_ChargeAmt > 0)
    {
        float totalDamage = BaseDamageCalculation(Attacker->getLevel() + _ChargeAmt, Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
        if (totalDamage > 0)
        {
            Defender->AddHealth(-totalDamage);
        }
        _ChargeAmt = 0;
        j["Bulb_Charges"] = _ChargeAmt;
        std::string jsonData = j.dump();
        Attacker->setJSONTag(jsonData);
    }
    else
    {
        float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
        if (totalDamage > 0)
        {
            Defender->AddHealth(-totalDamage);
        }
    }
}

void Bell_Ring::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    Attacker->setAttack(Attacker->getAttack() + 25);
    Defender->setAttack(Attacker->getAttack() + 25);
    f->AddFString("Attack Raised!");
}

void Sour_Note::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    if (Defender->getStatus() == Status_Sleep)
    {
        //SOUR NOTE AVOIDS ALL TYPE CALCULATIONS, AND ONLY HURTS SLEEPING ENEMIES
        float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), 2);
        if (totalDamage > 0)
        {
            Defender->AddHealth(-totalDamage);
            f->AddFString(Defender->getName() + " Woke Up");
        }
        Defender->clearStatus();
    }
    else
        f->AddFString(Attacker->getName() + "'s Attack Failed");
}

void Sing::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    if (Defender->getStatus() == Status_None)
    {
        Defender->setStatus(Status_Sleep);
        f->AddFString(Defender->getName() + " Fell Asleep");
    }
}

void Sabotage::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    json j;
    if (Defender->getJSONTag() != "")
        j = json::parse(Defender->getJSONTag());
    if (j.find("SabotagedMove") == j.end())
    {
        if (dynamic_cast<Enemy*>(Defender) != nullptr)
        {
            Enemy* e = dynamic_cast<Enemy*>(Defender);
            int smIndex = rand() % e->getMoves().size();
            j["SabotagedMove"] = static_cast<int>(e->getMoveAtIndex(smIndex)->getMoveInt());
            j["SabotagedMoveIndex"] = smIndex;
            e->SetMoveAtIndex(smIndex, new Sabotaged_Move(e->getMoveAtIndex(smIndex)->getName()));
        }
        else if (dynamic_cast<Player*>(Defender) != nullptr)
        {
            Player* p = dynamic_cast<Player*>(Defender);
            int smIndex = rand() % p->getMoves().size();
            j["SabotagedMove"] = static_cast<int>(this->getMoveInt());
            j["SabotagedMoveIndex"] = smIndex;
            p->SetMoveAtIndex(smIndex, new Sabotaged_Move(p->getMoveAtIndex(smIndex)->getName()));
        }
        else
        {
            throw new std::exception("error thrown in battle");
        }
        std::string jsonData = j.dump();
        Defender->setJSONTag(jsonData);
    }
    else
    {
        f->AddFString("Sabotage Failed!");
    }
}

void Sabotaged_Move::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()) + Defender->getAttack(this->getType()), Attacker->getDefence(), 1);
    if (totalDamage > 0)
    {
        Attacker->AddHealth(-totalDamage);
        f->AddFString("Move Was Sabotaged");
    }
    json j;
    if (Attacker->getJSONTag() != "")
        j = json::parse(Attacker->getJSONTag());
    else
        throw new std::exception("error thrown in battle");

    _SQMoves m = static_cast<_SQMoves>(j["SabotagedMove"]);
    int smIndex = j["SabotagedMoveIndex"];
    if (dynamic_cast<Enemy*>(Attacker) != nullptr)
    {
        Enemy* e = dynamic_cast<Enemy*>(Attacker);
        e->SetMoveAtIndex(smIndex, SQMoveFunctions::IntToMove(m));
    }
    else if (dynamic_cast<Player*>(Attacker) != nullptr)
    {
        Player* p = dynamic_cast<Player*>(Attacker);
        p->SetMoveAtIndex(smIndex, SQMoveFunctions::IntToMove(m));
    }
    else
    {
        throw new std::exception("error thrown in battle");
    }
    j.erase("SabotagedMove");
    j.erase("SabotagedMoveIndex");
    Attacker->setJSONTag(j.dump());
}


void Volt_Tackle::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    //BASE DAMAGE
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    //WE THEN DO ELECTRIC DAMAGE BACK
    Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    totalDamage = BaseDamageCalculation(Attacker->getLevel(), (Attacker->getAttack()/2), Attacker->getDefence(), Bonus_Damage);
    //BASE DAMAGE
    if (totalDamage > 0)
    {
        Attacker->AddHealth(-totalDamage);
    }
}

void Self_Change::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    int AmountOfTypes = Typeless;
    _SQType newType = static_cast<_SQType>(rand() % AmountOfTypes);
    Attacker->setType(newType);
    f->AddFString("Type Is Now: " + newType);
}

void Type_Swap::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    _SQType temp = Attacker->getType();
    Attacker->setType(Defender->getType());
    Defender->setType(temp);
    f->AddFString("Types Were Swapped!");
}


void Bide::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    //json j;
    //if (Attacker->getJSONTag() != "")
    //    j = json::parse(Attacker->getJSONTag());
}


void Ember::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    //THAW OUT A FROZEN ENEMY, BUT DO MORE DAMAGE TO THEM IN THE PROCESS
    if (Defender->getStatus() == Status_Frozen)
    {
        Defender->clearStatus();
        f->AddFString(Defender->getName() + " Has Thawed Out");
        Bonus_Damage * 1.5f;
    }
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    //CHANCE FOR EMBER TO BURN
    int Chance_One = rand() % 8;
    int Chance_Two = rand() % 8;
    if (Chance_One == Chance_Two)
    {
        Defender->setStatus(Status_Burnt);
        f->AddFString(Defender->getName() + " Was Burnt");
    }
}

void Poison_Flower::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{

    json j;
    if (Attacker->getJSONTag() != "")
        j = json::parse(Attacker->getJSONTag());

    int _FlowerAmt = 0;
    if (j.find("Flowers_Placed") != j.end())
        _FlowerAmt = j["Flowers_Placed"];

    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    if (_FlowerAmt > 0)
    {
        //INCREASE THE BONUS BY THE AMOUNT OF FLOWERS PLANTED
        Bonus_Damage += _FlowerAmt;
        _FlowerAmt = 0;
        j["Flowers_Placed"] = _FlowerAmt;
        std::string jsonData = j.dump();
        Attacker->setJSONTag(jsonData);
    }
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Garden::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    //ADD 5 TO THE AMOUNT OF FLOWERS
    json j;
    if (Attacker->getJSONTag() != "")
        j = json::parse(Attacker->getJSONTag());

    int _FlowerAmt = 0;
    if (j.find("Flowers_Placed") != j.end())
        _FlowerAmt = j["Flowers_Placed"];

    _FlowerAmt += 5;
    j["Flowers_Placed"] = _FlowerAmt;

    std::string jsonData = j.dump();
    Attacker->setJSONTag(jsonData);

    f->AddFString("Flowers Planted!");
}

void Icicle_Beam::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Psybeam::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getMagicAttack(this->getType()), Defender->getMagicDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}


void Snowman::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    f->AddFString("Nothing Happened!");
}

void Scary_Face::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    if (Defender->getStatus() == Status_None)
    {
        Defender->setStatus(Status_Paralyzed);
        f->AddFString(Defender->getName() + " Is Paralyzed");
    }
    else
    {
        f->AddFString("Attack Failed!");
    }

}

void Loose_Match::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    //DESTROY CROPS
    json j;
    if (Attacker->getJSONTag() != "")
    {
        j = json::parse(Attacker->getJSONTag());
        if (j.find("Flowers_Placed") != j.end())
            j["Flowers_Placed"] = 0;

        std::string jsonData = j.dump();
        Attacker->setJSONTag(jsonData);
    }
    if (Defender->getJSONTag() != "")
    {
        j = json::parse(Defender->getJSONTag());
        if (j.find("Flowers_Placed") != j.end())
            j["Flowers_Placed"] = 0;

        std::string jsonData = j.dump();
        Defender->setJSONTag(jsonData);
    }


    f->AddFString("The Fire Spread!");
}

void Waterboard::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);

    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    if (Defender->getDefence() > Player::getMinimumDefence())
    {
        Defender->setDefence(Defender->getDefence() - 5);
        if (Defender->getDefence() < Player::getMinimumDefence())
        {
            Defender->setDefence(Player::getMinimumDefence());
        }
    }

}

void Marked::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    json j;
    if (Defender->getJSONTag() != "")
    {
        j = json::parse(Defender->getJSONTag());
    }
    
    j["Marked"] = 1;

    std::string jsonData = j.dump();
    Defender->setJSONTag(jsonData);
    f->AddFString("Target Marked");
}

void Skull_Pierce::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    if (Defender->getType() == Telekinetic)
    {
        Bonus_Damage *= 2;
    }
    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
    if (Attacker->getAttack() > Player::getMinimumAttack())
    {
        Attacker->setAttack(Attacker->getAttack() - 5);
        if (Attacker->getAttack() < Player::getMinimumAttack())
        {
            Attacker->setAttack(Player::getMinimumAttack());
        }
    }
}

void Ciggie_Rain::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    Attacker->setAttack(Attacker->getAttack() + 15);
    Attacker->setAttack(Attacker->getMagicAttack() + 15);
    f->AddFString("Increased Attack");
}

void Bee_Sting::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    float Bonus_Damage = BattleFunctions::DetermineMultiplier(this, Defender);
    //DAMAGE IS HIGHER THE FASTER THE SPEED
    int SpeedMultiplier = Attacker->getSpeed() / 10;
    Bonus_Damage += SpeedMultiplier;
    //Defender Get Attacked By Water
    float totalDamage = BaseDamageCalculation(Attacker->getLevel(), Attacker->getAttack(this->getType()), Defender->getDefence(), Bonus_Damage);
    if (totalDamage > 0)
    {
        Defender->AddHealth(-totalDamage);
    }
}

void Bulk_Up::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    Attacker->setAttack(Attacker->getAttack() + 15);
    Attacker->setDefence(Attacker->getDefence() + 15);
    f->AddFString("Bulked Up");
}

#pragma endregion


void Player::AddXP(int xp, _SQ_Stat_Increase s)
{
    current_xp += xp; 
    while (current_xp >= xp_to_next_level) 
    { 
        current_xp -= xp_to_next_level; 
        xp_to_next_level *= levelUpRate;
        m_Level++; 
        switch (s)
        {
        case STATINCREASE_ATTACK:
            m_MaxHealth++;
            m_Attack += 2;
            break;
        case STATINCREASE_MAGIC_ATTACK:
            m_MaxHealth++;
            m_MagicAttack += 2;
            break;
        case STATINCREASE_DEFENCE:
            m_MaxHealth++;
            m_Defence += 2;
            break;
        case STATINCREASE_MAGIC_DEFENCE:
            m_MaxHealth++;
            m_MagicDefence += 2;
            break;
        case STATINCEASE_SPEED:
            m_MaxHealth++;
            m_Speed += 2;
            break;
        case STATINCREASE_HEALTH:
            m_MaxHealth += 3;
            break;
        default:
            m_MaxHealth++;
            break;
        }
        m_Health = m_MaxHealth;
    } 
}

void Player::SetMoves(std::vector<Move*> _Moves)
{
    if (_Moves.size() > 5)
    {
        throw new exception("Amount Too Large For Move Array");
    }
    _MoveArray = _Moves;
}

void Player::SetMoveAtIndex(int index, Move* m)
{
    this->_MoveArray[index] = m;
}

void Player::addUnlockedMove(_SQMoves s)
{
    for (int i = 0; i < UnlockedMoves.size(); i++)
    {
        if (UnlockedMoves[i] == s)
            return;
    }
    UnlockedMoves.push_back(s);
}

void Enemy::SetMoves(std::vector<Move*> _Moves)
{
    if (_Moves.size() > 5)
    {
        throw new exception("Amount Too Large For Move Array");
    }
    _MoveArray = _Moves;
}

void Enemy::SetMoveAtIndex(int index, Move* m)
{
    this->_MoveArray[index] = m;
}


Move* SQMoveFunctions::IntToMove(int i)
{
    switch (i)
    {
    case _SQ_Water_Blast:
        return new Water_Blast();
    case _SQ_Smoke_Cloud:
        return new Smoke_Cloud();
    case _SQ_Smoke_Break:
        return new Smoke_Break();
    case _SQ_Slash:
        return new Slash();
    case _SQ_Bone_Club:
        return new Bone_Club();
    case _SQ_Sudden_Cold:
        return new Sudden_Cold();
    case _SQ_Swarm:
        return new Swarm();
    case _SQ_Self_Destruct:
        return new Self_Destruct();
    case _SQ_Entangle:
        return new Entangle();
    case _SQ_Lightning_Slime:
        return new Lightning_Slime();
    case _SQ_Water_Slime:
        return new Water_Slime();
    case _SQ_Heal_Slime:
        return new Heal_Slime();
    case _SQ_Hope_Slime:
        return new Hope_Slime();
    case _SQ_Fireball:
        return new Fireball();
    case _SQ_Wave_Splash:
        return new Wave_Splash();
    case _SQ_Pitch_Black:
        return new Pitch_Black();
    case _SQ_Flashbang:
        return new Flashbang();
    case _SQ_Growth:
        return new Growth();
    case _SQ_Lightning_Bolt:
        return new Lightning_Bolt();
    case _SQ_Lightning_Punch:
        return new Lightning_Punch();
    case _SQ_Rainbow:
        return new Rainbow();
    case _SQ_Knights_Sword:
        return new Knights_Sword();
    case _SQ_BellRing:
        return new Bell_Ring();
    case _SQ_BrightIdea:
        return new Bright_Idea();
    case _SQ_ShatteredBulb:
        return new Shattered_Bulb();
    case _SQ_SourNote:
        return new Sour_Note();
    case _SQ_Sing:
        return new Sing();
    case _SQ_Sabotage:
        return new Sabotage();
    case _SQ_Volt_Tackle:
        return new Volt_Tackle();
    case _SQ_Self_Change:
        return new Self_Change();
    case _SQ_Type_Swap:
        return new Type_Swap();
    case _SQ_Bide:
        return new Bide();
    case _SQ_Ember:
        return new Ember();
    case _SQ_Poison_Flower:
        return new Poison_Flower();
    case _SQ_Garden:
        return new Garden();
    case _SQ_Icicle_Beam:
        return new Icicle_Beam();
    case _SQ_Snowball:
        return new Snowball();
    case _SQ_Psybeam:
        return new Psybeam();
    case _SQ_Snowman:
        return new Snowman();
    case _SQ_Gust:
        return new Gust();
    case _SQ_Scary_Face:
        return new Scary_Face();
    case _SQ_Bubble:
        return new Bubble();
    case _SQ_Bite:
        return new Bite();
    case _SQ_Waterboard:
        return new Waterboard();
    case _SQ_Marked:
        return new Marked();
    case _SQ_Ciggie_Rain:
        return new Ciggie_Rain();
    case _SQ_Bee_Sting:
        return new Bee_Sting();
    case _SQ_Bulk_Up:
        return new Bulk_Up();
    case _SQ_Rabbit_Food:
        return new Rabbit_Food();
    }
    return new Water_Blast();
}

void Rabbit_Food::Execute(Character* Attacker, Character* Defender, FightWindow* f)
{
    /*
    * THIS MOVE DESTROYS ALL FLOWERS FROM THE ATTACKER & DEFENDER AND INCREASES ALL STATS BY 5 * FLOWERS
    */
    json j;
    if (Defender->getJSONTag() != "")
        j = json::parse(Defender->getJSONTag());

    int _DefenderFlowerAmt = 0;
    if (j.find("Flowers_Placed") != j.end())
        _DefenderFlowerAmt = j["Flowers_Placed"];

    if (_DefenderFlowerAmt > 0)
    {
        j["Flowers_Placed"] = 0;
        std::string jsonData = j.dump();
        Defender->setJSONTag(jsonData);
    }

    if (Attacker->getJSONTag() != "")
        j = json::parse(Defender->getJSONTag());

    int _AttackerFlowerAmt = 0;
    if (j.find("Flowers_Placed") != j.end())
        _AttackerFlowerAmt += j["Flowers_Placed"];

    if (_AttackerFlowerAmt > 0)
    {
        j["Flowers_Placed"] = 0;
        std::string jsonData = j.dump();
        Defender->setJSONTag(jsonData);
    }

    int flowerAmount = _AttackerFlowerAmt + _DefenderFlowerAmt;

    if (flowerAmount > 0)
    {
        Attacker->setAttack(Attacker->getAttack() + (flowerAmount * 5));
        Attacker->setDefence(Attacker->getDefence() + (flowerAmount * 5));
        Attacker->setMagicAttack(Attacker->getMagicAttack() + (flowerAmount * 5));
        Attacker->setMagicDefence(Attacker->getMagicDefence() + (flowerAmount * 5));
        Attacker->setSpeed(Attacker->getSpeed() + (flowerAmount * 5));
        f->AddFString("Increased Stats");
    }
    else
    {
        f->AddFString("Had Nothing To Eat");
    }
}
