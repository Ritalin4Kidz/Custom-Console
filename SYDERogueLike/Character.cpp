#include "Character.h"

json Character::getJSONTag()
{
    return m_JSONTag;
}

void Character::validateCurrentJsonTag()
{
   m_JSONTag = json{
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
         {"ability", static_cast<int>(m_Ability)},
         {"status",static_cast<int>(getStatus())}
    };
}

void Character::validateFromJson(const json& j)
{
    this->m_Name = j.at("name").get<std::string>();
    this->m_Type = static_cast<_SQType>(j.at("type").get<int>());
    this->m_Ability = static_cast<_SQAbility>(j.at("ability").get<int>());
    this->m_Status = static_cast<_SQStatus>(j.at("status").get<int>());
    this->m_Health = j.at("health").get<int>();
    this->m_MaxHealth = j.at("maxHealth").get<int>();
    this->m_Attack = j.at("attack").get<int>();
    this->m_Defence = j.at("defence").get<int>();
    this->m_MagicAttack = j.at("magicAttack").get<int>();
    this->m_MagicDefence = j.at("magicDefence").get<int>();
    this->m_Speed = j.at("speed").get<int>();
    this->m_Level = j.at("level").get<int>();
    m_JSONTag = j;
}

void Character::SetMoves(std::vector<Move*> _Moves)
{
    if (_Moves.size() > 5)
    {
        throw new exception("Amount Too Large For Move Array");
    }
   m_MoveArray = _Moves;
}

void Character::SetMoveAtIndex(int index, Move* m)
{
    this->m_MoveArray[index] = m;
}

void Character::init(int lvl)
{
}
