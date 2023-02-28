#pragma once
#include "ShopItemRarity.h"
#include "SYDEstdafx.h"
#include "SYDEUI.h"

class ShopItem
{
public:
	ShopItem() {}

	CustomAsset getIcon() { return icon; }
	void setIcon(CustomAsset newIcon) { icon = newIcon; }

	CustomAsset getBackIcon() { return backIcon; }

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
};

class MoveShopItem : public ShopItem
{
public:
	MoveShopItem() {}
	MoveShopItem(int a_price, CustomAsset a_icon, ShopItemRarity a_rarity, string name);
protected:
};