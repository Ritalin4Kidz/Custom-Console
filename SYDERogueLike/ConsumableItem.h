#pragma once
#include "ItemClass.h",
#include "Move.h"
/*
THESE ITEMS NEED TO BE USED IN BATTLE AS WELL
THE BEST WAY AROUND THIS IS TO ASSOCIATE THEM WITH A MOVE
ONCE THEY GET USED IN BATTLE, ACT AS A MOVE
THEN REMOVE FROM THE INVENTORY
*/
class ConsumableItem : public ItemClass, public Move
{
public:
	ConsumableItem()
	{
		m_Name = "AN ITEM";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"FAKEITEMBMPSTR", 100, 180, 20, 20, 0, 45));
	}
	void decrementUsages() override {}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override {
		return true;
	};
	void Execute(json* Attacker, json* Defender, std::string* tag) override {}
private:

};