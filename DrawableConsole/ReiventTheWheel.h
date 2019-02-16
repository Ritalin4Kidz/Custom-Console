#pragma once
#include "pch.h"
#include <iostream>
#include "ConsoleWindow.h"
#include <math.h>
#include <time.h>
#include "Vector2.h"
#include "Board.h"
#include <stdlib.h> 
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <fstream>
#include "AI.h"
#include "Settings.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "BackgroundObj.h"
#include "Background.h"
#include "Characters.h"
#include "Artwork.h"
#include "AssetsClass.h"
#include "CustomAsset.h"
#include "CustomAnimationAsset.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;

class GAME_RTW_PIXEL {
public:
	GAME_RTW_PIXEL();
	GAME_RTW_PIXEL(Vector2 a_Point);

	void setColour(ColourClass newColour) { m_color = newColour; }
	
	Vector2 getPoint() { return m_point; }
	ColourClass getColour() { return m_color; }
	virtual ~GAME_RTW_PIXEL() {}
private:
	Vector2 m_point;
	ColourClass m_color;
};

class GAME_RTW {
public:
	GAME_RTW() { generalConstructor(); setUpPaintArray(40,20); }
	GAME_RTW(int windowWidth, int windowHeight) { generalConstructor(); setUpPaintArray(windowWidth, windowHeight); }
	virtual ~GAME_RTW() {}
	void generalConstructor();
	void setUpPaintArray(int windowWidth, int windowHeight);
	void setPaintArrayAtPoint(Vector2 aPoint, ColourClass colour);
	//GAME WINDOW
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight);
	//Game Voids
	void inputVoids();
	void nextColour();
	bool GetKey(char KeyCode);
private:
	int colourcode = 0;
	Vector2 m_CursorPoint;
	vector<GAME_RTW_PIXEL> m_PaintingArray;
	ColourClass m_PaintColour = BLACK;
	vector<ColourClass> m_paintColours = { BLACK, BLUE_BLUE_BG, RED_RED_BG, YELLOW_YELLOW_BG, GREEN_GREEN_BG, PURPLE_PURPLE_BG, BRIGHTWHITE_BRIGHTWHITE_BG, LIGHTBLUE_LIGHTBLUE_BG,
											DARKBLUE_DARKBLUE_BG, BRIGHTRED_BRIGHTRED_BG, BRIGHTGREEN_BRIGHTGREEN_BG, BRIGHTYELLOW_BRIGHTYELLOW_BG, LIGHTPURPLE_LIGHTPURPLE_BG, LIGHTGREY_LIGHTGREY_BG,
											NULLCOLOUR};
};