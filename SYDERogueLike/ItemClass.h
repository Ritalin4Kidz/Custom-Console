#pragma once
#include "SYDEstdafx.h"
#include "Move.h"
#include <functional>
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

	CustomAsset_Clickable getItemIcon() { return m_ItemIcon; }
	bool isUsableInBattle() {
		return m_CanBeUsedInBattle;
	}
	void decrementUsages() override {}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override {
		return false;
	};
	void Execute(json* Attacker, json* Defender, std::string* tag) override {}

	void setFunction_Tag(std::function<void()> f, string tag);

protected:
	CustomAsset_Clickable m_ItemIcon;
	bool m_CanBeUsedInBattle = false;
};