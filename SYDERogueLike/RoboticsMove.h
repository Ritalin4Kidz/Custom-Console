#pragma once
#include "Move.h"
class RoboticsMove : public Move {
public:
	RoboticsMove()
	{
		m_Name = "Robotics";
		m_Type = Electric;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Electric\\Robotics.bmp", 120, 80, 20, 20, 0, 24));
		maxUsages = 15;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		useMagicAttack = true;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};