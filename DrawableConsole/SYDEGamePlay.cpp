#include "pch.h"
#include "SYDEGamePlay.h"
#include "SYDETime.h"
#include "Defaults.h"

using namespace std;

bool SYDEGamePlay::_activated = false;

void SYDEGamePlay::opening_splashscreens(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars)
{
	_introductionScript();
	_introCreditsScript(window);
	bool setUp = true;
	for (int i = -10; i < 5; i++)
	{
		_drawBee(i, 9, setUp, start, hOut, window, windowWidth, windowHeight, artVars);
		setUp = false;
		Sleep(50);
	}

	PlaySound(chimePath, NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1250);
	for (int i = 5; i < 22; i++)
	{
		_drawBee(i, 9, setUp, start, hOut, window, windowWidth, windowHeight, artVars);
		Sleep(50);
	}
	for (int i = -10; i < 5; i++)
	{
		_poweredBySYDEEngine(i, 15, setUp, start, hOut, window, windowWidth, windowHeight, artVars);
		Sleep(50); 
	}
	PlaySound(chimePath, NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1250);
	for (int i = 5; i < 22; i++)
	{
		_poweredBySYDEEngine(i, 15, setUp, start, hOut, window, windowWidth, windowHeight, artVars);
		Sleep(50);
	}
	_activated = true;
}
void SYDEGamePlay::hidden_splashsceen_001(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow & window, int windowWidth, int windowHeight, AssetsClass astVars)
{
	//SCENE 10
	CustomAnimationAsset PIXAR;
	PIXAR.setAsset(vector<CustomAsset> {	CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_001.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_002.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_003.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_004.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_005.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_006.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_007.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_008.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_009.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_010.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_011.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_012.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20)),
											CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\DinseyPlanes\\Pixar\\Scene_013.bmp", 22, 20))
	});
	while (PIXAR.getFrame() < PIXAR.getFrameSize() - 1)
	{
		if (PIXAR.getFrame() == 9)
		{
			PlaySound(chimePath, NULL, SND_FILENAME | SND_ASYNC);
		}
		CONSOLE_CURSOR_INFO cInfo;
		GetConsoleCursorInfo(hOut, &cInfo);
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
		cout.flush();
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_BRIGHTWHITE_BG);
			}
		}
		window = PIXAR.draw_asset(window, SYDEDefaults::v2_Zero);
		window.writeConsole();
		Sleep(50);
	}
}
ConsoleWindow SYDEGamePlay::play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight,  SYDETIME& deltaTime)
{
	deltaTime.refreshTime();
	SYDEDefaults::setDeltaTime(deltaTime.getDeltaTime());
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	SetConsoleCursorPosition(hOut, start);
	if (!_activated)
	{
		return Activation::window_draw_game(window, windowWidth, windowHeight);
	}
	return SYDE_GAME->window_draw_game(window, windowWidth, windowHeight);
}

void SYDEGamePlay::_introductionScript()
{
	string gameTitle = "Syde";
	int scriptLoad = rand() % 15;
	switch (scriptLoad)
	{
	case 0:
		cout << "Initializing Window...%" << endl;
		Sleep(250);
		cout << "Loading Up Quake Engine...0%" << endl;
		Sleep(40);
		cout << "Quake Engine Load Failure @ 7%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Engine...0%" << endl;
		Sleep(40);
		cout << "Backup Engine Load Failure @ 13%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Backup Engine...0%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Backup Engine...25%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Backup Engine...50%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Backup Engine...75%" << endl;
		Sleep(40);
		cout << "Loading Up Backup Backup Engine...100%" << endl;
		Sleep(40);
		cout << "Backup Backup Engine Load Success!%" << endl;
		Sleep(40);
		cout << "Generating Menus...%" << endl;
		Sleep(70);
		cout << "Generating Graphics...%" << endl;
		Sleep(70);
		cout << "Generating Levels...%" << endl;
		Sleep(70);
		cout << "Generating Fake Text...%" << endl;
		Sleep(70);
		cout << "Checking CPU Temperature For Some Reason%" << endl;
		Sleep(40);
		cout << "CPU Overheating For Some Reason%" << endl;
		Sleep(40);
		cout << "Decreasing Graphics Levels To Compensate%" << endl;
		Sleep(80);
		cout << "Removing Cool Features%" << endl;
		Sleep(40);
		cout << "Adding Extremely Bland Features%" << endl;
		Sleep(40);
		cout << "Adding A Jetpack & Grappling Hook%" << endl;
		cout << "For Uniqueness%" << endl;
		Sleep(40);
		cout << "Adding Memes From 2006 To Sound Funny%" << endl;
		Sleep(40);
		cout << "Not Actually Doing Anything%" << endl;
		Sleep(40);
		cout << "Making It Look Like I Am%" << endl;
		Sleep(40);
		cout << "Finally Launching The Game!%" << endl;
		Sleep(40);
		break;
	case 1:
		cout << "Trying To Open The Terminal...%" << endl;
		Sleep(250);
		cout << "So No One Is Reading This%" << endl;
		Sleep(40);
		cout << "But It Looks Like A Boot Up%" << endl;
		Sleep(40);
		cout << "For That Good Ol' Retro Feel%" << endl;
		Sleep(40);
		cout << "Back When Holt Was Our Prime Minister%" << endl;
		Sleep(40);
		cout << "I Still Leave My Porch%" << endl;
		Sleep(40);
		cout << "Light On Every Night%" << endl;
		Sleep(40);
		cout << "Hawky Was A Better PM Though%" << endl;
		Sleep(40);
		cout << "Doing Kickflips To Win The Election%" << endl;
		Sleep(40);
		cout << "What A Top Bloke Honestly%" << endl;
		Sleep(40);
		cout << "Can't Believe That He Has So%" << endl;
		Sleep(40);
		cout << "Many Games Based Off Him%" << endl;
		Sleep(40);
		cout << "How Many Does George Bush Have?%" << endl;
		Sleep(40);
		cout << "Exactly...%" << endl;
		Sleep(70);
		cout << "Anyways Since No One Is Reading%" << endl;
		Sleep(70);
		cout << "............%" << endl;
		Sleep(70);
		cout << "Boobs%" << endl;
		Sleep(70);
		cout << "Oh Damn You Probably Saw That%" << endl;
		Sleep(40);
		cout << "Please Don't Tell Mum%" << endl;
		Sleep(40);
		cout << "Oh No Please Don't I Beg You%" << endl;
		Sleep(80);
		cout << "I Didn't Mean It!!!%" << endl;
		Sleep(40);
		cout << ".................%" << endl;
		Sleep(40);
		cout << "I'm In So Much Trouble%" << endl;
		Sleep(40);
		cout << "I Gotta Go Now, Have Fun Kiddo%" << endl;
		Sleep(40);
		cout << "Finally Launching The Game!%" << endl;
		Sleep(40);
		break;
	case 2:
		cout << "00001000%" << endl;
		Sleep(250);
		cout << "10100111%" << endl;
		Sleep(40);
		cout << "01010101%" << endl;
		Sleep(40);
		cout << "10011001%" << endl;
		Sleep(40);
		cout << "01000001%" << endl;
		Sleep(40);
		cout << "11110001%" << endl;
		Sleep(40);
		cout << "10101010%" << endl;
		Sleep(40);
		cout << "11001111%" << endl;
		Sleep(40);
		cout << "00111110%" << endl;
		Sleep(40);
		cout << "10010011%" << endl;
		Sleep(40);
		cout << "00000000%" << endl;
		Sleep(40);
		cout << "10110001%" << endl;
		Sleep(70);
		cout << "01111111%" << endl;
		Sleep(70);
		cout << "01110001%" << endl;
		Sleep(70);
		cout << "11111110%" << endl;
		Sleep(70);
		cout << "01100110%" << endl;
		Sleep(40);
		cout << "11100000%" << endl;
		Sleep(40);
		cout << "10001100%" << endl;
		Sleep(80);
		cout << "11010011%" << endl;
		Sleep(40);
		cout << "00110001%" << endl;
		Sleep(40);
		cout << "01011101%" << endl;
		Sleep(40);
		cout << "11010110%" << endl;
		Sleep(40);
		cout << "11211011%" << endl;
		Sleep(40);
		cout << "Wait Hold On I Screwed Up%" << endl;
		Sleep(40);
		break;
	case 3:
		Sleep(40);
		cout << "Loading Up 16-Bit Colour%" << endl;
		Sleep(40);
		cout << "Loading Up Terminal%" << endl;
		Sleep(40);
		cout << "Loading Up Load Up Jokes%" << endl;
		Sleep(40);
		cout << "Buying Fresh Stock Of % Signs%" << endl;
		Sleep(40);
		cout << "Launching Matrix%" << endl;
		Sleep(40);
		cout << "Benchmarking Graphics Card%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...0%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...2%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...5%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...3%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...8%" << endl;
		Sleep(40);
		cout << "Downloading Extra Colours...13%" << endl;
		Sleep(40);
		cout << "Download Failure at 15%" << endl;
		Sleep(40);
		cout << "Reverting Back To 16-Bit Colour%" << endl;
		Sleep(40);
		cout << "Oh Well%" << endl;
		Sleep(40);
		break;
	default:
		for (int i = 0; i < 30; i++)
		{
			Sleep(40);
			cout << _returnRandomNonsense() << endl;
		}
		break;
	}
	cout << "Launching " << gameTitle << "...0%" << endl;
	Sleep(100);
	cout << "Launching " << gameTitle << "...25%" << endl;
	Sleep(100);
	cout << "Launching " << gameTitle << "...50%" << endl;
	Sleep(100);
	cout << "Launching " << gameTitle << "...75%" << endl;
	Sleep(100);
	cout << "Launching " << gameTitle << "...100%" << endl;
	Sleep(100);
	cout << "Starting...%" << endl;
	Sleep(50);
}

void SYDEGamePlay::_introCreditsScript(ConsoleWindow& window)
{
	window.ClearWindow(true);
	cout << "SYDE" << endl;
	Sleep(25);
	cout << "Created By Callum Hands" << endl;
	Sleep(25);
	cout << "In Association With Team Freebee Games" << endl;
	Sleep(25);
	cout << "Programming & Art : Callum Hands" << endl;
	Sleep(25);
	cout << "Game Engine : Callum Hands" << endl;
	Sleep(25);
	cout << "'SYDE Engine' Made In Visual Studio" << endl;
	Sleep(25);
	cout << "Using C++" << endl;
	Sleep(25);

	system("pause");
}

void SYDEGamePlay::_drawBee(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars)
{
	if (setUp)
	{
		window.ClearWindow(true);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.addToLine(m, " ", BLACK);
			}
		}
	}
	else
	{
		CONSOLE_CURSOR_INFO cInfo;
		GetConsoleCursorInfo(hOut, &cInfo);
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
		cout.flush();
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_BRIGHTWHITE_BG);
			}
		}
	}
	window = artVars.draw_freebee_bee(window, baseX, baseY);
	//window.setTextAtPoint(Vector2(baseX + 2, baseY + 10), "Team Freebee Games", BLACK_BRIGHTWHITE_BG);
	window.writeConsole();
}

void SYDEGamePlay::_poweredBySYDEEngine(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars)
{
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	SetConsoleCursorPosition(hOut, start);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_BRIGHTWHITE_BG);
		}
	}
	window = artVars.draw_syde_engine_logo(window, baseX, baseY);
	window.writeConsole();
}

string SYDEGamePlay::_returnRandomNonsense()
{
	string pText = "";
	int length = (rand() % 15) + 20;
	for (int i = 0; i < length; i++)
	{
		int rNum = rand() % 21;
		switch (rNum)
		{
		case 0:
			pText += "#";
			break;
		case 1:
			pText += "A";
			break;
		case 2:
			pText += "$";
			break;
		case 3:
			pText += "<";
			break;
		case 4:
			pText += ")";
			break;
		case 5:
			pText += "C";
			break;
		case 6:
			pText += ">";
			break;
		case 7:
			pText += "?";
			break;
		case 8:
			pText += "4";
			break;
		case 9:
			pText += "T";
			break;
		case 10:
			pText += "@";
			break;
		case 11:
			pText += "!";
			break;
		case 12:
			pText += "Q";
			break;
		case 13:
			pText += "&";
			break;
		case 14:
			pText += "P";
			break;
		case 15:
			pText += "6";
			break;
		case 16:
			pText += "W";
			break;
		case 17:
			pText += "^";
			break;
		case 18:
			pText += "(";
			break;
		case 19:
			pText += "B";
			break;
		case 20:
			pText += "9";
			break;
		default:
			pText += " ";
			break;
		}
	}
	pText += "%";
	return pText;
}
