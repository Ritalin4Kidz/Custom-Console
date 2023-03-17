#pragma once
#include "Move.h"
class DefaultSlimeMove : public Move {
public:
	DefaultSlimeMove()
	{
		m_Name = "Harmless Slime";
		m_Type = Melee;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\SlimeAnimation.bmp", 200, 360, 20, 20, 0, 180));
		m_Accuracy = 100;
		lastEffortMove = true;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		//NOTHING CAN HAPPEN
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override
	{
		return false;
	}
protected:
};