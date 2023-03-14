#pragma once
#include "ItemClass.h",
#include "Move.h"

#include "SydeRogueLikeStatics.h"

/*
THESE ITEMS NEED TO BE USED IN BATTLE AS WELL
THE BEST WAY AROUND THIS IS TO ASSOCIATE THEM WITH A MOVE
ONCE THEY GET USED IN BATTLE, ACT AS A MOVE
THEN REMOVE FROM THE INVENTORY
*/
class MoveItemClass : public ItemClass
{
public:
	MoveItemClass() {}
	MoveItemClass(std::shared_ptr<Move> m, int width, int height, vector<ColourClass> colour_array, string name)
	{
		m_Name = name;
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"FAKEITEMBMPSTR", 100, 180, 20, 20, 0, 45));
		m_CanBeUsedInBattle = false;
		m_Move = m;
		m_ItemIcon.setAsset(width, height, colour_array);
	}
	void decrementUsages() override {}

	void useItem(json* Attacker) override;

	std::shared_ptr<Move> getMove() { return m_Move; }

	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override {
		return true;
	};
	void Execute(json* Attacker, json* Defender, std::string* tag) override {}
private:
	std::shared_ptr<Move> m_Move;
};