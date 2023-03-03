#pragma once
#include "Move.h"
class SleepStatus : public Move {
public:
	SleepStatus()
	{
		m_Name = "Sleep";
		m_Type = Air;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Sleep.bmp", 160, 140, 20, 20, 0, 56));
		maxUsages = 00;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override { return true; };
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
	void decrementUsages() override;
protected:
};