#include "pch.h"
#include "SYDETime.h"

void SYDETIME::initialise(std::chrono::high_resolution_clock::time_point time)
{
	timeprev = time;
}

void SYDETIME::refreshTime()
{
	std::chrono::high_resolution_clock currentTime;
	std::chrono::duration<float> diff = currentTime.now() - timeprev;
	deltaTime = diff.count();
	timeprev = std::chrono::high_resolution_clock::now();
}

