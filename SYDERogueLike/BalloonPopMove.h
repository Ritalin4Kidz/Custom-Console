#pragma once
#include "Move.h"
class BalloonPopMove : public Move {
public:
	BalloonPopMove()
	{
		m_Name = "Balloon Pop";
		m_Type = Air;
		BasePower = 20;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\BalloonPop.bmp", 100, 120, 20, 20, 0, 30));
		maxUsages = 20;
		usagesLeft = maxUsages;
	}
	virtual ~BalloonPopMove() {}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};