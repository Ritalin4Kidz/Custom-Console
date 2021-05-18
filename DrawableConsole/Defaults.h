#pragma once
#include "Vector2.h"
#include <Windows.h>
class RTWDefaults {
public:
	const static float getJumpPower() { return -3.0f; }
};

static class SYDEDefaults {
public:
	static float deltaTime;

	/// <summary>
	/// set the time between frames (note: this is called in gameplay loop already)
	/// </summary>
	/// <param name="time"></param>
	static void setDeltaTime(float time) { deltaTime = time; }
	/// <summary>
	/// get the current time between frames
	/// </summary>
	/// <returns></returns>
	static float getDeltaTime() { return deltaTime; }
	static Vector2 v2_Zero;

	/// <summary>
	/// send a console command
	/// </summary>
	/// <param name="cmd"></param>
	static void consoleCommand(const char* cmd);

	static int mouseInputWaitTime;
};

class SYDEFunctions {
public:
	/// <summary>
	/// send the application to sleep for a period of time
	/// </summary>
	/// <param name="time"></param>
	/// <param name="deltaTime"></param>
	static void SYDESleep(int time, float deltaTime);
};