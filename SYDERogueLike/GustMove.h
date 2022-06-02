#pragma once
#include "Move.h"
class GustMove : public Move {
public:
	GustMove()
	{
		m_Name = "Gust";
		m_Type = Air;
		BasePower = 15;
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Air\\Gust.bmp", 100, 100, 20, 20, 0, 25));
		maxUsages = 10;
		usagesLeft = maxUsages;
	}
	virtual ~GustMove() {}
protected:
};