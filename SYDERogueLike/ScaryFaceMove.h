#pragma once
#include "Move.h"
class ScaryFaceMove : public Move {
public:
	ScaryFaceMove()
	{
		m_Name = "Scary Face";
		m_Type = Telekinetic;
		BasePower = 0;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Telekinetic\\ScaryFace.bmp", 100, 280, 20, 20, 0, 70));
		maxUsages = 25;
		usagesLeft = maxUsages;
		m_Accuracy = 100;
		useMagicAttack = true;
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
	void Execute(json* Attacker, json* Defender, std::string* tag) override;
protected:
};