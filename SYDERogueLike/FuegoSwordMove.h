#pragma once
#include "Move.h"
class FuegoSwordMove : public Move {
public:
	FuegoSwordMove()
	{
		m_Name = "Fuego's Sword";
		m_Type = Metal;
		BasePower = 25;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Metal\\SwordAnimation.bmp", 100, 100, 20, 20, 0, 25));
		lastEffortMove = true;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};