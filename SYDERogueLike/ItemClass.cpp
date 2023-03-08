#include "ItemClass.h"

void ItemClass::setFunction_Tag(std::function<void()> f, string tag)
{
	m_ItemIcon.SetFunc(f);
	m_ItemIcon.setTag(tag);
}
