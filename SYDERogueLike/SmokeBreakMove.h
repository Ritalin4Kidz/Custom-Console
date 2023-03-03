#pragma once
#include "SmokeMoveType.h"
class SmokeBreakMove : public SmokeMoveType {
public:
	SmokeBreakMove()
	{
		m_Name = "Smoke Break";
		m_Type = Air;
		BasePower = 5;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\SmokeBreak.bmp", 200, 280, 20, 20, 0, 137));
		maxUsages = 10;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};