#pragma once
#include "Move.h"
class FailedMove : public Move {
public:
	FailedMove()
	{
		m_Name = "A Failed Move";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\FailedMove.bmp", 100, 180, 20, 20, 0, 45));
		maxUsages = 0;
		usagesLeft = maxUsages;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override { return true; };
	void Execute(json* Attacker, json* Defender, std::string* tag) override {};
protected:
};