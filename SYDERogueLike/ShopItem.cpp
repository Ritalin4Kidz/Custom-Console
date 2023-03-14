#include "pch.h"
#include "ShopItem.h"

ShopItem::ShopItem(int a_price, CustomAsset a_icon, ShopItemRarity a_rarity, string name, std::shared_ptr<ItemClass> item)
{
	itemRarity = a_rarity;
	if (itemRarity == SIR_COMMON)
	{
		backIcon = CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\Rarity\\common.bmp", 5, 5));
	}
	else if (itemRarity == SIR_UNCOMMON)
	{
		backIcon = CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\Rarity\\uncommon.bmp", 5, 5));
	}
	else if (itemRarity == SIR_RARE)
	{
		backIcon = CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\Rarity\\rare.bmp", 5, 5));
	}
	else if (itemRarity == SIR_LEGEND)
	{
		backIcon = CustomAsset(10, 5, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ShopIcons\\Rarity\\legend.bmp", 5, 5));
	}
	price = a_price;
	icon = a_icon;
	displayName = name;
	m_InventoryItem = item;
}
