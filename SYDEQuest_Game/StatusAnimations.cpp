#include "StatusAnimations.h"
CustomAnimationAsset StatusAnimations::m_FrozenAnimation = CustomAnimationAsset();
CustomAnimationAsset StatusAnimations::m_BurntAnimation = CustomAnimationAsset();
CustomAnimationAsset StatusAnimations::m_ParalyzedAnimation = CustomAnimationAsset();
CustomAnimationAsset StatusAnimations::m_SleepAnimation = CustomAnimationAsset();
CustomAnimationAsset StatusAnimations::m_ThawedAnimation = CustomAnimationAsset();
CustomAnimationAsset StatusAnimations::m_AwakeAnimation = CustomAnimationAsset();
void StatusAnimations::LoadAnimations()
{
	AssetsClass astVars;
	m_FrozenAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\FrozenTemp.bmp", astVars, 100, 100, 20, 20, 0, 25));
	m_BurntAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Burnt.bmp", astVars, 100, 100, 20, 20, 0, 25));
	m_ParalyzedAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Paralyzed.bmp", astVars, 100, 100, 20, 20, 0, 25));
	m_SleepAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Sleep.bmp", astVars, 160, 140, 20, 20, 0, 56));
	m_AwakeAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Awake.bmp", astVars, 100, 100, 20, 20, 0, 25));
	m_ThawedAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\StatusAnimations\\Thawed.bmp", astVars, 100, 140, 20, 20, 0, 35));
}

void StatusAnimations::UnLoadAnimations()
{
}
