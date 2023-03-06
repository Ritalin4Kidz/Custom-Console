#pragma once
#include "SYDEstdafx.h"

class ItemClass
{
public:
	ItemClass() {}

	CustomAsset getItemIcon() { return m_ItemIcon; }
protected:
	CustomAsset m_ItemIcon;
};