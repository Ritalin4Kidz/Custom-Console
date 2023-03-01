#pragma once
#include "Move.h"
class WaveMove : public Move {
public:
	WaveMove()
	{
		m_Name = "Wave";
		m_Type = Water;
		BasePower = 45;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Water\\WaveAttack.bmp", 60, 140, 20, 20, 0, 21));
		maxUsages = 10;
		useMagicAttack = false;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};
