#pragma once
#include "SYDEstdafx.h"
class StatusAnimations {
public:
	static void LoadAnimations();
	static void UnLoadAnimations();
	static CustomAnimationAsset m_FrozenAnimation;
	static CustomAnimationAsset m_BurntAnimation;
	static CustomAnimationAsset m_ParalyzedAnimation;
	static CustomAnimationAsset m_SleepAnimation;
	static CustomAnimationAsset m_ThawedAnimation;
	static	CustomAnimationAsset m_AwakeAnimation;
};