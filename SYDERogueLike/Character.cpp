#include "Character.h"

json Character::getJSONTag()
{
	json j;
	return j;
}

void Character::validateFromJson(json t)
{
	m_JSONTag = t;
	//TODO: Make character stats change based off json
}
