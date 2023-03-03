#pragma once
#include "Move.h"
class BurntStatus : public Move {
public:
	BurntStatus()
	{
		m_Name = "Burnt";
		m_Type = Air;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Burnt.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 00;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override { return true; };
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
	void decrementUsages() override;
protected:
};