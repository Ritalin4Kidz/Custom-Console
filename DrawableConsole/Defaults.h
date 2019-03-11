#pragma once
class RTWDefaults {
public:
	const static float getJumpPower() { return -3.0f; }
};

static class SYDEDefaults {
public:
	static float deltaTime;
	static void setDeltaTime(float time) { deltaTime = time; }
	static float getDeltaTime() { return deltaTime; }
};