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
#include "Defaults.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "SYDEWindowGame.h"
#include "SYDEKeyCode.h"
#include "SYDETextBox.h"
#include "SYDELabel.h"
using namespace std;
using namespace Gdiplus;

class Concerto : public SYDEWindowGame {
public:
	Concerto() { Initialize(); }
	virtual ~Concerto() {}

	//DRAW
	void Initialize();
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	SYDETextBox m_TextBox = SYDETextBox(Vector2(4, 5), Vector2(10, 2), BLACK_BRIGHTWHITE_BG);
	SYDELabel m_Label = SYDELabel("Test Text",  Vector2(4, 10), Vector2(10, 1), BLACK, true);
};