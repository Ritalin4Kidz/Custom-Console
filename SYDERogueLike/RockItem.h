#pragma once
#include "ConsumableItem.h"
class RockItem : public ConsumableItem
{
public:
	RockItem()
	{
		m_ItemIcon = CustomAsset_Clickable(16, 8, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ItemIcons\\Rock.bmp", 8, 8));
		m_Name = "A Rock";
		m_Type = Typeless;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\ItemUseAnimations\\RockItem.bmp", 100, 140, 20, 20, 0, 35));
		m_CanBeUsedOutsideBattle = false;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
private:

};