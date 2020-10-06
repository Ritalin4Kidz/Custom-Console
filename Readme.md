# SYDE ENGINE LIBRARY

## Introduction

SYDE Engine Framework for creating small games to run inside the windows console

## Neccessary Declarations

```cpp
#include "pch.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
using namespace std;
using namespace Gdiplus;
//INITIALIZING VARIABLES
int windowWidth = 40;
const int windowHeight = 20;
Settings config("EngineFiles\\Settings\\configSettings.sc");
ConsoleWindow window(windowHeight);
//OTHER ASSETS
AssetsClass astVars;

//GDI VALUES
ULONG_PTR gdiplusToken;
GdiplusStartupInput startupInput;

//GAME VALUES
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

```

Important Variables for running the framework

```
	LPCWSTR title = L"Concerto";
	SYDECredits::_GAMETITLE = "Concerto";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SetConsoleTitleW(title);
```

Example for setting variables for application name in window + splashscreens

```
	config.volumeControl(0);
	config.ColourPalette(hOut);
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	srand(time(NULL));
```

Example for config initialisation

## Example Code

Included are a couple of SYDEWindowGame classes that you can try out the framework with. In This Example, we're going to be using the Concerto.h file.

```cpp
class Concerto : public SYDEWindowGame {
public:
	Concerto() { Initialize(); }
	virtual ~Concerto() {}

	//DRAW
	void Initialize();
	void m_Button_Press();
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	SYDETextBox m_TextBox = SYDETextBox(Vector2(4, 5), Vector2(10, 2), BLACK_BRIGHTWHITE_BG);
	SYDELabel m_Label = SYDELabel("Test Text",  Vector2(4, 10), Vector2(10, 1), BLACK, true);
	SYDEButton m_Button;
	//WE WANT TO START THE MENU AT y=1.
	SYDEMenu _MENU = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Test Text", Vector2(0, 1), Vector2(10, 1), BLACK, true),
		SYDEButton("New Text", Vector2(0, 2), Vector2(10, 1), BLACK, true)
	});
	string m_LabelText = "Test Text";
	void(buttonPressFunc)() { m_Button_Press(); }
};
```

Concerto is used for testing certain elements of the Engine, so there are a couple of functions in there that are not relevant for this example. The only function that is important for this example is the 'window_draw_game function'

```cpp
ConsoleWindow Concerto::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	return window;
}
```

In this case, the window_draw_game function is setting each point of the window to be a solid white colour, with no text to display. This is good as a background template to draw assets over.

```
window = m_Label.draw_ui(window);
if (SYDEKeyCode::get('M')._CompareState(KEYDOWN))
{
	_MENU.nextSelect();
}
```

We can call assets draw functions as well before returning the window, and also check for inputs

```cpp
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	Concerto m_Concerto;
	SYDEGamePlay::initialize_window(hOut, window);
	SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	while (true)
	{
		window = SYDEGamePlay::play(&m_Concerto, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsole();
		SYDEFunctions::SYDESleep(30, SYDEDefaults::getDeltaTime());
	}
```

Inside our main function, we can initialize all of our variables and call up SYDEGamePlay::play_game or SYDEGamePlay::play to run the game.


## Release Notes

### 1.1.3.0 6/10/2020
- SYDEParticle header added
- SYDEParticle & SYDEParticleEmitter classes

### 1.1.2.0
- SYDEClock_Timer added
- Timer can do a function on each tik and display itself on the window
- More Function Descriptions

### 1.1.1.0 5/10/2020
- SYDEFPS Counter asset added
- SYDEFPS option added to SYDEGamePlay::play function
- Function descriptions added to certain files in the library
- SYDELabel can now adjust position an colour to already created labels

### 1.1.0.0 ?????
- SYDEShapes assets added
- - Circle, Square & Rectangle

### 1.0.0.0 ?????
- First Official Release Of SYDE Engine
```