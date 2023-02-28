#pragma once
#include "Move.h"
class BoneClubMove : public Move {
public:
	BoneClubMove()
	{
		m_Name = "Bone Club";
		m_Type = Melee;
		BasePower = 65;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Melee\\BoneAttack.bmp", 80, 160, 20, 20, 0, 32));
		maxUsages = 15;
		usagesLeft = maxUsages;
	}
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};