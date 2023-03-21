#pragma once
#include "Move.h"
class SourNoteMove : public Move {
public:
	SourNoteMove()
	{
		m_Name = "Sour Note";
		m_Type = Air;
		BasePower = 80;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\SourNote.bmp", 260, 100, 20, 20, 0, 65));
		maxUsages = 10;
		usagesLeft = maxUsages;
		m_TM_Identifier = "TM_007";
	}
	bool isSuccessful(json* Attacker, json* Defender, std::string* tag) override;
protected:
};