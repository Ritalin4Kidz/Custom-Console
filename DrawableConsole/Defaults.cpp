#include "pch.h"
#include "Defaults.h"

float SYDEDefaults::deltaTime = 0;
Vector2 SYDEDefaults::v2_Zero = Vector2(0, 0);

void SYDEFunctions::SYDESleep(int time, float deltaTime)
{
	int _SLEEP = time - (deltaTime * 1000);
	if (_SLEEP < 0)
	{
		_SLEEP = 0;
	}
	Sleep(_SLEEP);
}
