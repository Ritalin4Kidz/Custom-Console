#pragma once
#include "ShopItemRarity.h"
#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include "ItemClass.h"


class ShopItem
{
public:
	ShopItem() {}
	ShopItem(int a_price, CustomAsset a_icon, ShopItemRarity a_rarity, string name, std::shared_ptr<ItemClass> item);
	CustomAsset getIcon() { return icon; }
	void setIcon(CustomAsset newIcon) { icon = newIcon; }
	void setName(string name) { displayName = name; }
	CustomAsset getBackIcon() { return backIcon; }

	std::shared_ptr<ItemClass> getItem() { return m_InventoryItem; }

	int getPrice() { return price; }
	void setPrice(int newPrice) { price = newPrice; }

	ShopItemRarity getRarity() { return itemRarity; }

	string getName() { return displayName; }
protected:
	ShopItemRarity itemRarity;
	CustomAsset icon;
	CustomAsset backIcon;
	int price;
	string displayName;
	std::shared_ptr<ItemClass> m_InventoryItem;
};