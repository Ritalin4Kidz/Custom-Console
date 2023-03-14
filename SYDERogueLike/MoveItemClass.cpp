#include "MoveItemClass.h"

void MoveItemClass::useItem(json* Attacker)
{
	SydeRogueLikeStatics::addPlayerMove(m_Move);
}
