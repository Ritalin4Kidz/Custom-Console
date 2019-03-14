#include "pch.h"
#include "Activation.h"


ConsoleWindow Activation::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (!_setUp)
	{
		window.ClearWindow(true);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.addToLine(m, " ", BLACK);
			}
		}
		_setUp = true;
	}
	else 
	{
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
			}
		}
		//ACTIVATION UI
		window.setTextAtPoint(Vector2(0, 1), "*ACTIVATION REQUIRED*", BLACK_WHITE_BG);

		window.setTextAtPoint(Vector2(0, 3), "Use:", BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(0, 4), "'SYDEGamePlay::opening_splashscreens()'", BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(0, 5), "To Activate The Engine", BLACK_WHITE_BG);

		window.setTextAtPoint(Vector2(0, 18), "Z: Exit", BLACK_WHITE_BG);
		inputVoids(windowWidth, windowHeight);
	}
	return window;
}

void Activation::inputVoids(int windowWidth, int windowHeight)
{
	if (GetKey('Z'))
	{
		exit(NULL);
	}
}

bool Activation::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}

bool Activation::_setUp = false;