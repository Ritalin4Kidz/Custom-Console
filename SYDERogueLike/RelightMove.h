#pragma once
#include "Move.h"
class RelightMove : public Move {
public:
	RelightMove()
	{
		m_Name = "Relight";
		m_Type = Typeless;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Typeless\\Relight.bmp", 100, 100, 20, 20, 0, 25));
		lastEffortMove = true;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override { return true; }
	void Execute(json* Attacker, json* Defender, std::string* tag) override
	{
		tag->append(std::string("RELIGHT"));
	}
protected:
};