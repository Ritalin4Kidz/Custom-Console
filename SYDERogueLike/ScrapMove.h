#pragma once
#include "Move.h"
class ScrapMove : public Move {
public:
	ScrapMove()
	{
		m_Name = "Scrap";
		m_Type = Typeless;
		BasePower = 25;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\Scrap.bmp", 100, 180, 20, 20, 0, 45));
		lastEffortMove = true;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};