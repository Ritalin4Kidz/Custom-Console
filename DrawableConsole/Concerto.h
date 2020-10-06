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
#include "SYDEButton.h"
#include "SYDEMenu.h"
#include "SYDEClock.h"
#include "SYDEParticle.h"
using namespace std;
using namespace Gdiplus;

void TickFunc();

class Concerto : public SYDEWindowGame {
public:
	Concerto() { Initialize(); }
	virtual ~Concerto() {}

	//DRAW
	void Initialize();
	void m_Button_Press();
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static void setBG(ColourClass c) { _bg = c; }
private:
	SYDETextBox m_TextBox = SYDETextBox(Vector2(4, 5), Vector2(10, 2), BLACK_BRIGHTWHITE_BG);
	SYDELabel m_Label = SYDELabel("Q:Start,E:Stop,W:Increase,S:Decrease",  Vector2(0, 19), Vector2(40, 1), WHITE, true);
	SYDEButton m_Button;
	//WE WANT TO START THE MENU AT y=1.
	SYDEMenu _MENU = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Test Text", Vector2(0, 1), Vector2(10, 1), BLACK, true),
		SYDEButton("New Text", Vector2(0, 2), Vector2(10, 1), BLACK, true)
	});
	string m_LabelText = "Test Text";
	void(buttonPressFunc)() { m_Button_Press(); }
	SYDEClock_Timer _t = SYDEClock_Timer(0.5f);
	SYDEParticleEmitter _e = SYDEParticleEmitter(Vector2(20,-3), Vector2(-2, 1), Vector2(2, 1));
	SYDEParticleBurst _b = SYDEParticleBurst(Vector2(0, 0), Vector2(-2, -2), Vector2(2, 2));
	static ColourClass _bg;
};