#pragma once
#include "ConsumableItem.h"
class PotionItem : public ConsumableItem
{
public:
	PotionItem()
	{
		m_ItemIcon = CustomAsset_Clickable(16, 8, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ItemIcons\\Potion.bmp", 8, 8));
		m_Name = "A Potion";
		m_Type = Typeless;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\ItemUseAnimations\\PotionUsage.bmp", 100, 180, 20, 20, 0, 45));
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
	void useItem(json* Attacker) override;
private:

};