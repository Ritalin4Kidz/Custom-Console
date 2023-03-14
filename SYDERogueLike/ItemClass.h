#pragma once
#include "SYDEstdafx.h"
#include "Move.h"
#include <functional>
#include <memory>
class ItemClass : public Move
{
public:
	ItemClass()
	{
		m_Name = "AN ITEM";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"FAKEITEMBMPSTR", 100, 180, 20, 20, 0, 45));
	}

	/// <summary>
	/// FOR USING THE ITEM OUTSIDE OF BATTLE
	/// </summary>
	virtual void useItem(json* Attacker) {}
	CustomAsset_Clickable getItemIcon() { return m_ItemIcon; }
	void setIcon(int width, int height, vector<ColourClass> colour_array) { m_ItemIcon.setAsset(width, height, colour_array); }
	bool isUsableInBattle() {
		return m_CanBeUsedInBattle;
	}
	void decrementUsages() override {}

	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override {
		return false;
	};
	void Execute(json* Attacker, json* Defender, std::string* tag) override {}

	void setFunction_Tag(std::function<void()> f, string tag);

	bool isUsableOutBattle() { return m_CanBeUsedOutsideBattle; }

protected:
	CustomAsset_Clickable m_ItemIcon;
	bool m_CanBeUsedInBattle = false;
	bool m_CanBeUsedOutsideBattle = true;
};