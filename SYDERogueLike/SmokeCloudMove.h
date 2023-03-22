#pragma once
#include "SmokeMoveType.h"
class SmokeCloudMove : public SmokeMoveType {
public:
	SmokeCloudMove()
	{
		m_Name = "Smoke Cloud";
		m_Type = Air;
		BasePower = 55;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\SmokeCloud.bmp", 200, 80, 20, 20, 0, 37));
		maxUsages = 10;
		useMagicAttack = true;
		usagesLeft = maxUsages;
	}
protected:
};