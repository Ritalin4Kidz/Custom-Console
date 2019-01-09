// DrawableConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// CODE BY CALLUM HANDS
// ritalin4kidz.github.io
// callum@hands.net.au
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

#include "PhysicsObject.h"
#include "RigidBody.h"
int windowWidth = 40;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
//WINDOW
ConsoleWindow window(windowHeight);
//SYDE VALUES
string levelBonus = "Break_Room";
string command = "";
string info = "";
string lookAngleStr = "Right";
//CHARACTER SKINS
string characterName1 = "Officer_Man";
vector<ColourClass> charSkin1 = { DARKBLUE_DARKBLUE_BG, BLACK, BRIGHTYELLOW_BRIGHTYELLOW_BG, WHITE_WHITE_BG };
string characterName2 = "Nude_Lunatic";
vector<ColourClass> charSkin2 = { WHITE_WHITE_BG, WHITE_WHITE_BG, WHITE_WHITE_BG, WHITE_WHITE_BG };
string characterName3 = "Sunday_Sport";
vector<ColourClass> charSkin3 = { BRIGHTRED_BRIGHTRED_BG, LIGHTBLUE_PURPLE_BG, LIGHTBLUE_LIGHTBLUE_BG, WHITE_WHITE_BG };
vector<vector<ColourClass>> charSkins{charSkin1, charSkin2, charSkin3};
vector<string> charNames = { characterName1, characterName2, characterName3 };
int skinNumber = 0;
//OTHER VALUES
bool isScene = true;
int XWins = 0;
int OWins = 0;
int Draws = 0;
bool watermelonIsCutScene = true;

int generations = 0;
bool foundPath = false;

//GAME VALUES
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Vector2 startPosition(5, 19);
string cutsceneStr = "SYDE_Ep1_Intro";

using namespace std;
struct Background {
	Background(ColourClass a_color, Vector2 a_pos, string text) { colour = a_color; pos = a_pos; mText = text; }
	ColourClass colour;
	Vector2 pos;
	string mText;

};
// TRIANGLE GENERATION
vector<string> Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	vector<string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}
bool GetKeyDown(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}
void drawCharacter(Vector2 point, ColourClass Clothes1, ColourClass Clothes2, ColourClass Accessory, ColourClass Skin, string lookAngle)
{
	//PANTS
	for (int i = 0; i < 4; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes2);
		}
	}
	//SHIRT
	for (int i = 3; i < 7; i++)
	{
		for (int ii = -2; ii < 6; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes1);
		}
	}
	//HEAD
	for (int i = 6; i < 8; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Skin);
		}
	}
	//BADGE
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 5), " ", Accessory);
	window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 5), " ", Accessory);
	//HANDS
	window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 3), " ", Skin);
	window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 3), " ", Skin);

	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 3), " ", Skin);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 3), " ", Skin);
	if (charNames[skinNumber] == "Nude_Lunatic")
	{
		for (int x = -2; x < 6; x++)
		{
			for (int y = 2; y < 3; y++)
			{
				window.setTextAtPoint(Vector2(point.getX() + x, point.getY() - y), " ", BLACK);
			}
		}
	}
	//HAT
	if (charNames[skinNumber] != "Nude_Lunatic")
	{
		for (int i = 8; i < 10; i++)
		{
			for (int ii = 0; ii < 4; ii++)
			{
				window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes1);
			}
		}
		if (lookAngle == "Right")
		{
			window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 8), " ", Clothes1);
			window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 8), " ", Clothes1);
		}
		else if (lookAngle == "Left")
		{
			window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 8), " ", Clothes1);
			window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 8), " ", Clothes1);
		}
	}
	if (charNames[skinNumber] == "Nude_Lunatic")
	{
		window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 1, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 8), " ", Clothes1);
	}
}
bool charHitBoxCheck(Vector2 point, Vector2 obj,int startX, int endX, int startY, int endY)
{
	for (int x = point.getX() + startX; x < point.getX() + endX; x++)
	{
		for (int y = point.getY() + startY; y > point.getY() - endY; y--)
		{
			if (obj == Vector2(x, y))
			{
				return true;
			}
		}
	}
	return false;
}
void generateTriangle()
{
	window.ClearWindow(true);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
		}
	}
	Vector2 pointA(3, 7);
	Vector2 pointB(7, 7);
	Vector2 pointC(7, 2);
	window.setTextAtPoint(pointA, "*", WHITE);
	window.setTextAtPoint(pointB, "*", WHITE);

	window.setTextAtPoint(pointC, "*", WHITE);

	// SETTING LINES
	for (int i = pointA.getX() + 1; i < pointB.getX(); i++)
	{
		window.setTextAtPoint(Vector2(i, 7), "-", WHITE);
	}
	for (int i = pointC.getY() + 1; i < pointB.getY(); i++)
	{
		window.setTextAtPoint(Vector2(7, i), "|", WHITE);
	}
	for (int i = pointA.getY() - 1, x = pointA.getX(); i > pointC.getY(); i--, x++)
	{
		window.setTextAtPoint(Vector2(x,i), "/", WHITE);
	}
	window.setLine(10, "Hypotenuse Is " + to_string(sqrtf(powf(pointA.distance(pointB),2) + powf(pointB.distance(pointC), 2))) + " Units! (Assumption)", WHITE);
	window.setLine(11, "Area Is " + to_string(0.5 * pointA.distance(pointB) * pointB.distance(pointC)) + " Units^2! (Assumption)", WHITE);
	window.writeConsole();
}

void TicTacToe(bool isAIp1, bool isAIp2, int offset, string OBrain, string XBrain)
{
	// INITIALIZE THE WINDOW FOR USAGE
	window.ClearWindow(true);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
		}
	}

	// 15 LOGIC : https://www.braingle.com/brainteasers/teaser.php?op=2&id=5388&comm=0

	// CREATE THE 9 BOARD PIECES, EACH WITH A VALUE (HAS TO BE IN THIS ORDER FOR THE 15 LOGIC)
	vector<BoardPiece> pieces = {
		BoardPiece(Vector2(0,0), 4), BoardPiece(Vector2(1,0), 3), BoardPiece(Vector2(2,0), 8),
		BoardPiece(Vector2(0,1), 9), BoardPiece(Vector2(1,1), 5), BoardPiece(Vector2(2,1), 1),
		BoardPiece(Vector2(0,2), 2), BoardPiece(Vector2(1,2), 7), BoardPiece(Vector2(2,2), 6),
	};

	// CREATE THE BOARD, TARGET VALUE OF 15, MAX 9 TURNS
	Board ticTacToeBoard(pieces, 15, 9);
	for (int i = 0; i < ticTacToeBoard.getBoard().size(); i++)
	{
		window.setTextAtPoint(ticTacToeBoard.getBoard()[i].getPos().offset(offset), "*", WHITE);
	}

	// DRAW THE BOARD ON THE TERMINAL
	window.writeConsole();

	// SET UP THE VARIABLES
	string user = "X";
	bool isGameWon = false;
	int turns = 0;
	ColourClass colour = GREEN;
	AI OAI(OBrain);
	AI XAI(XBrain);
	string boardString;
	// GAME LOOP
	while (!isGameWon && turns < ticTacToeBoard.getMaxTurns())
	{
		string input;
		// AI TURN IF AI IS ON
		if (user == "O" && isAIp2)
		{
			if (!isAIp1 || !isAIp2)
			{
				window.setLine(10, "AI's Turn", WHITE);
				window.ClearWindow(false);
				window.writeConsole();
				//system("pause");
			}

			// NEURAL NETWORK
			boardString = "";
			for (int i = 0; i < ticTacToeBoard.getBoard().size(); i++)
			{
				boardString += ticTacToeBoard.getBoard()[i].getOccupier();
				if (i != ticTacToeBoard.getBoard().size() - 1)
				{
					boardString += ',';
				}
				else
				{
					boardString += ";";
				}
			}
			// CHECKS IF ALREADY KNOWS A WINNING MOVE
			Vector2 actualChoice = OAI.bestMove(boardString);
			input = to_string(actualChoice.getX()) + "," + to_string(actualChoice.getY());
		}

		else if (user == "X" && isAIp1)
		{
			if (!isAIp1 || !isAIp2)
			{
				window.setLine(10, "AI's Turn", WHITE);
				window.ClearWindow(false);
				window.writeConsole();
				system("pause");
			}

			// NEURAL NETWORK
			boardString = "";
			for (int i = 0; i < ticTacToeBoard.getBoard().size(); i++)
			{
				boardString += ticTacToeBoard.getBoard()[i].getOccupier();
				if (i != ticTacToeBoard.getBoard().size() - 1)
				{
					boardString += ',';
				}
				else
				{
					boardString += ";";
				}
			}
			// CHECKS IF ALREADY KNOWS A WINNING MOVE
			Vector2 actualChoice = XAI.bestMove(boardString);
			input = to_string(actualChoice.getX()) + "," + to_string(actualChoice.getY());
		}

		// IF NOT AN AI TURN, USER INPUTS A CO-ORDINATE TO PLACE THEIR MARKER
		else
		{
			cin >> input;
		}
		// CO-ORDINATE IS THEN SPLIT TO MAKE A VECTOR 2
		vector<string> command = Split(input, ',');
		// MAKE SURE NOT AN INCORRECT SIZE
		if (command.size() == 2)
		{
			Vector2 choice = Vector2(stoi(command[0]), stoi(command[1]));
			// CHECK IF THE PIECE IS ON THE BOARD
			if (ticTacToeBoard.pieceExists(choice))
			{
				// THEN CHECK IF IT'S ALREADY OCCUPIED
				if (ticTacToeBoard.getPieceAt(choice).getOccupier() == " ")
				{
					// IF NOT OCCUPIED, OCCUPY THE SPOT, THEN RE-PRINT THE CONSOLE WITH THE MARKER PLACED
					ticTacToeBoard.setOccupierAt(choice, user);
					window.setTextAtPoint(choice.offset(offset), user, colour);
					// CHECK TO SEE IF A WINNING MOVE HAS BEEN MADE
					isGameWon = ticTacToeBoard.checkWinner(user);
					if (isGameWon)
					{
						if (user == "O")
						{
							OWins++;
						}
						else if (user == "X")
						{
							XWins++;
						}
						if (user == "O" && isAIp2)
						{
							if (OAI.existingMove(boardString, choice))
							{
								window.setLine(11, user + " Won By Using It's Memory Of A Winning Move", WHITE);
								window.ClearWindow(false);
								window.writeConsole();
								//system("pause");
							}
							else
							{
								OAI.addWinMove(boardString, choice);
							}
						}
						else if(user == "X" && isAIp1)
						{
							if (XAI.existingMove(boardString, choice))
							{
								window.setLine(11, user + " Won By Using It's Memory Of A Winning Move", WHITE);
								window.ClearWindow(false);
								window.writeConsole();
								//system("pause");
							}
							else
							{
								XAI.addWinMove(boardString, choice);
							}
						}
						window.setLine(12, user + " Wins The Game!", WHITE);
					}
					// ADD A TURN
					turns++;
					if (turns >= ticTacToeBoard.getMaxTurns() && !isGameWon)
					{
						if (user == "O" && isAIp2)
						{
							if (OAI.existingMove(boardString, choice))
							{
								window.setLine(11, user + " Already Knew A Draw Was Inevitable", WHITE);
								window.ClearWindow(false);
								window.writeConsole();
								//system("pause");
							}
							else
							{
								OAI.addWinMove(boardString, choice);
							}
						}
						if (user == "X" && isAIp1)
						{
							if (XAI.existingMove(boardString, choice))
							{
								window.setLine(11, user + " Already Knew A Draw Was Inevitable", WHITE);
								window.ClearWindow(false);
								window.writeConsole();
								//system("pause");
							}
							else
							{
								XAI.addWinMove(boardString, choice);
							}
						}
						Draws++;
					}
					// SWAP USERS
					if (user == "X") {
						user = "O";
						colour = YELLOW;
					}
					else {
						user = "X";
						colour = GREEN;
					};
				}
			}
		}
		window.clearLine(10);
		window.ClearWindow(false);
		window.writeConsole();
		if (isAIp1 && isAIp2)
		{
			Sleep(25);
		}
	}
	// IF TURNS UP AND NO WINNERS, GAME IS DRAWN
	if (!isGameWon)
	{
		window.setLine(12, "Drawn Game!", WHITE);
		window.ClearWindow(false);
		window.writeConsole();
	}
}

void generateart()
{
	int asciiArt = rand() % 3;
	window.ClearWindow(true);
	switch (asciiArt)
	{
	case 0:
		window.setLine(0, "WINDOWS LOGO", WHITE);
		window.setLine(1, "             _.-;;-._ ", WHITE);
		window.setLine(2, "      '-..-'|   ||   |", WHITE);
		window.setLine(3, "      '-..-'|_.-;;-._|", WHITE);
		window.setLine(4, "      '-..-'|   ||   |", WHITE);
		window.setLine(5, "      '-..-'|_.-''-._|", WHITE);
		break;
	case 1:
		window.setLine(0, "PAINTBRUSH", WHITE);
		window.setLine(1, "              .------------------....___       ", YELLOW);
		window.setLine(2, "             /                      /  /'''---", YELLOW);
		window.setLine(3, "             \\                      \\__\\...---", YELLOW);
		window.setLine(4, "              '------------------''''           ", YELLOW);

		window.addToLine(1, ",;;", WHITE);
		window.addToLine(1, ";,", RED);
		window.addToLine(2, "/;;;;", WHITE);
		window.addToLine(2, ";;,.,", RED);
		window.addToLine(3, "\\;;;;", WHITE);
		window.addToLine(3, ";;;", RED);
		window.addToLine(4, "``", WHITE);
		window.addToLine(4, "``", RED);
		break;
	default:
		window.setLine(0, "WINDOWS LOGO ", WHITE); window.addToLine(0, "R", RED); window.addToLine(0, "A", YELLOW); window.addToLine(0, "I", GREEN); window.addToLine(0, "N", BLUE); window.addToLine(0, "B", PURPLE); window.addToLine(0, "O", RED); window.addToLine(0, "W", YELLOW);
		window.setLine(1, "             _.-;;-._", PURPLE);
		window.setLine(2, "      '-..-'|   ||   |", RED);
		window.setLine(3, "      '-..-'|_.-;;-._|", YELLOW);
		window.setLine(4, "      '-..-'|   ||   |", BLUE);
		window.setLine(5, "      '-..-'|_.-''-._|", GREEN);
		break;
	}
	window.writeConsole();

}


void scene1()
{
	window.ClearWindow(true);
	// DRAW THE POLICE OFFICER
	window.setLine(0, "                ,", WHITE);
	window.setLine(1, "       __  _.-'` `'-.", WHITE);
	window.setLine(2, "      /||\\'._ __{}_(", WHITE);
	window.setLine(3, "      ||||  |'--.__\\", WHITE);
	window.setLine(4, "      |  L.(   ^_\\^", WHITE);
	window.setLine(5, "      \\ .-' |   _ |", WHITE);
	window.setLine(6, "      | |   )\\___/", WHITE);
	window.setLine(7, "      |  \\-'`:._]", WHITE);
	window.setLine(8, "      \\__/;      '-.", WHITE);
	window.setLine(9, "      |   |o     __ \\", WHITE);
	window.setLine(10, "      |   |o     )( |", WHITE);
	window.setLine(11, "      |   |o     \\/ \\", WHITE);
	window.setLine(13, "POLICE OFFICER: STOP!! YOU HAVE VIOLATED THE LAW", AQUA);

	window.writeConsole();
}

void scene2()
{
	// DRAW THE COMPUTER GUY
	window.ClearWindow(true);
	window.setLine(2, "             __    __", WHITE);
	window.setLine(3, "            /  \\ /| |'-.", WHITE);
	window.setLine(4, "           .\\__/ || |   |", WHITE);
	window.setLine(5, "        _ /  `._ \\|_|_.-'", WHITE);
	window.setLine(6, "       | /  \\__.`=._) (_", WHITE);
	window.setLine(7, "       |/ ._/  |''''''''' | ", WHITE);
	window.setLine(8, "       |'.  `\\ |         |", WHITE);
	window.setLine(9, "       ;'''/ / |         |", WHITE);
	window.setLine(10, "        ) /_/| |.-------.|", WHITE);
	window.setLine(11, "       '  `-`' '         '", WHITE);
	window.setLine(13, "Player: Man computer graphics sure are", YELLOW);
	window.setLine(14, "impressive these days! ", YELLOW);
	window.writeConsole();
}

void scene3()
{
	window.ClearWindow(true);
	window.setLine(2, "             __    __", WHITE);
	window.setLine(3, "            /  \\ /| |'-.", WHITE);
	window.setLine(4, "           .\\__/ || |   |", WHITE);
	window.setLine(5, "        _ /  `._ \\|_|_.-'", WHITE);
	window.setLine(6, "       | /  \\__.`=._) (_", WHITE);
	window.setLine(7, "       |/ ._/  |''''''''' | ", WHITE);
	window.setLine(8, "       |'.  `\\ |         |", WHITE);
	window.setLine(9, "       ;'''/ / |         |", WHITE);
	window.setLine(10, "        ) /_/| |.-------.|", WHITE);
	window.setLine(11, "       '  `-`' '         '", WHITE);
	window.setLine(13, "Player: I thought I was being arrested", YELLOW);
	window.setLine(14, "in real life! ", YELLOW);
	window.writeConsole();
}
void scene4()
{
	window.ClearWindow(false);
	window.addLayerToLine(10, "Gang Weed", GREEN, '@', 14);
	window.clearLine(13);
	window.clearLine(14);
	window.writeConsole();
}

void scenes()
{
	scene1();
	system("pause");
	scene2();
	system("pause");
	scene3();
	system("pause");
	scene4();
}
void Test()
{
	window.ClearWindow(true);
	window.setLine(0, "The quick brown fox jumped over the lazy dog", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.writeConsole();

}

void PixelArt(ColourClass skinOuter, ColourClass skinMiddle, ColourClass skinInner, ColourClass Meat, ColourClass Seed, ColourClass BG, string a_text)
{
	if (!watermelonIsCutScene)
	{
		window.ClearWindow(true);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				if (!watermelonIsCutScene) { window.addToLine(m, " ", WHITE); }
				window.setTextAtPoint(Vector2(l, m), " ", BG);
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
				window.setTextAtPoint(Vector2(l, m), " ", WHITE);
			}
		}
		//window.writeConsole();
	}
	// DRAW PIXEL ART

	//WATERMELON SKIN
	window.setTextAtPoint(Vector2(1, 11), " ", skinMiddle);
	window.setTextAtPoint(Vector2(2, 11), " ", skinMiddle);
	window.setTextAtPoint(Vector2(1, 12), " ", skinOuter);
	window.setTextAtPoint(Vector2(2, 12), " ", skinOuter);

	window.setTextAtPoint(Vector2(3, 12), " ", skinMiddle);
	window.setTextAtPoint(Vector2(4, 12), " ", skinMiddle);
	window.setTextAtPoint(Vector2(3, 13), " ", skinOuter);
	window.setTextAtPoint(Vector2(4, 13), " ", skinOuter);

	window.setTextAtPoint(Vector2(5, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(6, 13), " ", skinMiddle);

	window.setTextAtPoint(Vector2(7, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(8, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(7, 14), " ", skinOuter);
	window.setTextAtPoint(Vector2(8, 14), " ", skinOuter);

	window.setTextAtPoint(Vector2(9, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(10, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(9, 14), " ", skinOuter);
	window.setTextAtPoint(Vector2(10, 14), " ", skinOuter);

	window.setTextAtPoint(Vector2(11, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(12, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(11, 14), " ", skinOuter);
	window.setTextAtPoint(Vector2(12, 14), " ", skinOuter);
											 
	window.setTextAtPoint(Vector2(13, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(14, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(13, 14), " ", skinOuter);
	window.setTextAtPoint(Vector2(14, 14), " ", skinOuter);
											 
	window.setTextAtPoint(Vector2(15, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(16, 13), " ", skinMiddle);
	window.setTextAtPoint(Vector2(15, 14), " ", skinOuter);
	window.setTextAtPoint(Vector2(16, 14), " ", skinOuter);
											 
	window.setTextAtPoint(Vector2(17, 12), " ", skinMiddle);
	window.setTextAtPoint(Vector2(18, 12), " ", skinMiddle);
	window.setTextAtPoint(Vector2(17, 13), " ", skinOuter);
	window.setTextAtPoint(Vector2(18, 13), " ", skinOuter);

	window.setTextAtPoint(Vector2(19, 11), " ", skinMiddle);
	window.setTextAtPoint(Vector2(20, 11), " ", skinMiddle);
	window.setTextAtPoint(Vector2(19, 12), " ", skinOuter);
	window.setTextAtPoint(Vector2(20, 12), " ", skinOuter);
	window.setTextAtPoint(Vector2(19, 13), " ", skinOuter);
	window.setTextAtPoint(Vector2(20, 13), " ", skinOuter);
											 
	window.setTextAtPoint(Vector2(21, 10), " ", skinMiddle);
	window.setTextAtPoint(Vector2(22, 10), " ", skinMiddle);
	window.setTextAtPoint(Vector2(21, 11), " ", skinOuter);
	window.setTextAtPoint(Vector2(22, 11), " ", skinOuter);
	window.setTextAtPoint(Vector2(21, 12), " ", skinOuter);
	window.setTextAtPoint(Vector2(22, 12), " ", skinOuter);

	window.setTextAtPoint(Vector2(23, 9), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 9), " ", skinMiddle);
	window.setTextAtPoint(Vector2(23, 10)," ", skinOuter);
	window.setTextAtPoint(Vector2(24, 10)," ", skinOuter);
	window.setTextAtPoint(Vector2(23, 11)," ", skinOuter);
	window.setTextAtPoint(Vector2(24, 11)," ", skinOuter);
	window.setTextAtPoint(Vector2(25, 9), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 9), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(23, 8), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 8), " ", skinMiddle);
	window.setTextAtPoint(Vector2(25, 8), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 8), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(23, 7), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 7), " ", skinMiddle);
	window.setTextAtPoint(Vector2(25, 7), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 7), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(23, 6), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 6), " ", skinMiddle);
	window.setTextAtPoint(Vector2(25, 6), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 6), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(23, 5), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 5), " ", skinMiddle);
	window.setTextAtPoint(Vector2(25, 5), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 5), " ", skinOuter);

	window.setTextAtPoint(Vector2(23, 4), " ", skinMiddle);
	window.setTextAtPoint(Vector2(24, 4), " ", skinMiddle);
	window.setTextAtPoint(Vector2(25, 4), " ", skinOuter);
	window.setTextAtPoint(Vector2(26, 4), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(21, 3), " ", skinMiddle);
	window.setTextAtPoint(Vector2(22, 3), " ", skinMiddle);
	window.setTextAtPoint(Vector2(23, 3), " ", skinOuter);
	window.setTextAtPoint(Vector2(24, 3), " ", skinOuter);
										    
	window.setTextAtPoint(Vector2(19, 2), " ", skinMiddle);
	window.setTextAtPoint(Vector2(20, 2), " ", skinMiddle);
	window.setTextAtPoint(Vector2(21, 2), " ", skinOuter);
	window.setTextAtPoint(Vector2(22, 2), " ", skinOuter);

	//INSIDE LAYER OF SKIN
	window.setTextAtPoint(Vector2(19, 3), " ", skinInner);
	window.setTextAtPoint(Vector2(20, 3), " ", skinInner);
													
	window.setTextAtPoint(Vector2(19, 4), " ", skinInner);
	window.setTextAtPoint(Vector2(20, 4), " ", skinInner);
													
	window.setTextAtPoint(Vector2(21, 4), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 4), " ", skinInner);
	//9												
	window.setTextAtPoint(Vector2(21, 5), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 5), " ", skinInner);
													
	window.setTextAtPoint(Vector2(21, 6), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 6), " ", skinInner);
													
	window.setTextAtPoint(Vector2(21, 7), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 7), " ", skinInner);
													
	window.setTextAtPoint(Vector2(21, 8), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 8), " ", skinInner);
													 
	window.setTextAtPoint(Vector2(21, 9), " ", skinInner);
	window.setTextAtPoint(Vector2(22, 9), " ", skinInner);

	window.setTextAtPoint(Vector2(19, 9), " ", skinInner);
	window.setTextAtPoint(Vector2(20, 9), " ", skinInner);

	window.setTextAtPoint(Vector2(19, 10), " ", skinInner);
	window.setTextAtPoint(Vector2(20, 10), " ", skinInner);

	window.setTextAtPoint(Vector2(17, 11), " ", skinInner);
	window.setTextAtPoint(Vector2(18, 11), " ", skinInner);

	window.setTextAtPoint(Vector2(15, 11), " ", skinInner);
	window.setTextAtPoint(Vector2(16, 11), " ", skinInner);

	window.setTextAtPoint(Vector2(15, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(16, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(13, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(14, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(11, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(12, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(9, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(10, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(7, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(8, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(5, 12), " ", skinInner);
	window.setTextAtPoint(Vector2(6, 12), " ", skinInner);

	window.setTextAtPoint(Vector2(5, 11), " ", skinInner);
	window.setTextAtPoint(Vector2(6, 11), " ", skinInner);

	window.setTextAtPoint(Vector2(3, 11), " ", skinInner);
	window.setTextAtPoint(Vector2(4, 11), " ", skinInner);

	// ADD THE JUICY WATERMELON MEAT
	window.setTextAtPoint(Vector2(7, 11), " ", Meat);
	window.setTextAtPoint(Vector2(8, 11), " ", Meat);

	window.setTextAtPoint(Vector2(9, 11), " ", Meat);
	window.setTextAtPoint(Vector2(10, 11), " ", Meat);

	window.setTextAtPoint(Vector2(11, 11), " ", Meat);
	window.setTextAtPoint(Vector2(12, 11), " ", Meat);

	window.setTextAtPoint(Vector2(13, 11), " ", Meat);
	window.setTextAtPoint(Vector2(14, 11), " ", Meat);

	window.setTextAtPoint(Vector2(3, 10), " ", Meat);
	window.setTextAtPoint(Vector2(4, 10), " ", Meat);

	window.setTextAtPoint(Vector2(5, 10), " ", Meat);
	window.setTextAtPoint(Vector2(6, 10), " ", Meat);

	window.setTextAtPoint(Vector2(7, 10), " ", Meat);
	window.setTextAtPoint(Vector2(8, 10), " ", Meat);

	window.setTextAtPoint(Vector2(9, 10), " ", Meat);
	window.setTextAtPoint(Vector2(10, 10), " ", Meat);

	window.setTextAtPoint(Vector2(11, 10), " ", Meat);
	window.setTextAtPoint(Vector2(12, 10), " ", Meat);

	window.setTextAtPoint(Vector2(13, 10), " ", Meat);
	window.setTextAtPoint(Vector2(14, 10), " ", Meat);

	window.setTextAtPoint(Vector2(15, 10), " ", Meat);
	window.setTextAtPoint(Vector2(16, 10), " ", Meat);

	window.setTextAtPoint(Vector2(17, 10), " ", Meat);
	window.setTextAtPoint(Vector2(18, 10), " ", Meat);

	window.setTextAtPoint(Vector2(5, 9), " ", Meat);
	window.setTextAtPoint(Vector2(6, 9), " ", Meat);

	window.setTextAtPoint(Vector2(7, 9), " ", Meat);
	window.setTextAtPoint(Vector2(8, 9), " ", Meat);

	window.setTextAtPoint(Vector2(9, 9), " ", Meat);
	window.setTextAtPoint(Vector2(10, 9), " ", Meat);

	window.setTextAtPoint(Vector2(11, 9), " ", Meat);
	window.setTextAtPoint(Vector2(12, 9), " ", Meat);

	window.setTextAtPoint(Vector2(13, 9), " ", Meat);
	window.setTextAtPoint(Vector2(14, 9), " ", Meat);

	window.setTextAtPoint(Vector2(15, 9), " ", Meat);
	window.setTextAtPoint(Vector2(16, 9), " ", Meat);

	window.setTextAtPoint(Vector2(17, 9), " ", Meat);
	window.setTextAtPoint(Vector2(18, 9), " ", Meat);

	window.setTextAtPoint(Vector2(7, 8), " ", Meat);
	window.setTextAtPoint(Vector2(8, 8), " ", Meat);

	window.setTextAtPoint(Vector2(9, 8), " ", Meat);
	window.setTextAtPoint(Vector2(10, 8), " ", Meat);

	window.setTextAtPoint(Vector2(11, 8), " ", Meat);
	window.setTextAtPoint(Vector2(12, 8), " ", Meat);

	window.setTextAtPoint(Vector2(13, 8), " ", Meat);
	window.setTextAtPoint(Vector2(14, 8), " ", Meat);

	window.setTextAtPoint(Vector2(15, 8), " ", Meat);
	window.setTextAtPoint(Vector2(16, 8), " ", Meat);

	window.setTextAtPoint(Vector2(17, 8), " ", Meat);
	window.setTextAtPoint(Vector2(18, 8), " ", Meat);

	window.setTextAtPoint(Vector2(19, 8), " ", Meat);
	window.setTextAtPoint(Vector2(20, 8), " ", Meat);

	window.setTextAtPoint(Vector2(9, 7), " ", Meat);
	window.setTextAtPoint(Vector2(10, 7), " ", Meat);

	window.setTextAtPoint(Vector2(11, 7), " ", Meat);
	window.setTextAtPoint(Vector2(12, 7), " ", Meat);

	window.setTextAtPoint(Vector2(13, 7), " ", Meat);
	window.setTextAtPoint(Vector2(14, 7), " ", Meat);

	window.setTextAtPoint(Vector2(15, 7), " ", Meat);
	window.setTextAtPoint(Vector2(16, 7), " ", Meat);

	window.setTextAtPoint(Vector2(17, 7), " ", Meat);
	window.setTextAtPoint(Vector2(18, 7), " ", Meat);

	window.setTextAtPoint(Vector2(19, 7), " ", Meat);
	window.setTextAtPoint(Vector2(20, 7), " ", Meat);

	window.setTextAtPoint(Vector2(11, 6), " ", Meat);
	window.setTextAtPoint(Vector2(12, 6), " ", Meat);
									  
	window.setTextAtPoint(Vector2(13, 6), " ", Meat);
	window.setTextAtPoint(Vector2(14, 6), " ", Meat);
									  
	window.setTextAtPoint(Vector2(15, 6), " ", Meat);
	window.setTextAtPoint(Vector2(16, 6), " ", Meat);
									  
	window.setTextAtPoint(Vector2(17, 6), " ", Meat);
	window.setTextAtPoint(Vector2(18, 6), " ", Meat);
									  
	window.setTextAtPoint(Vector2(19, 6), " ", Meat);
	window.setTextAtPoint(Vector2(20, 6), " ", Meat);

	window.setTextAtPoint(Vector2(13, 5), " ", Meat);
	window.setTextAtPoint(Vector2(14, 5), " ", Meat);
									  
	window.setTextAtPoint(Vector2(15, 5), " ", Meat);
	window.setTextAtPoint(Vector2(16, 5), " ", Meat);
									  
	window.setTextAtPoint(Vector2(17, 5), " ", Meat);
	window.setTextAtPoint(Vector2(18, 5), " ", Meat);
									  
	window.setTextAtPoint(Vector2(19, 5), " ", Meat);
	window.setTextAtPoint(Vector2(20, 5), " ", Meat);

	window.setTextAtPoint(Vector2(15, 4), " ", Meat);
	window.setTextAtPoint(Vector2(16, 4), " ", Meat);

	window.setTextAtPoint(Vector2(17, 4), " ", Meat);
	window.setTextAtPoint(Vector2(18, 4), " ", Meat);

	window.setTextAtPoint(Vector2(17, 3), " ", Meat);
	window.setTextAtPoint(Vector2(18, 3), " ", Meat);

	// SEEDS
	window.setTextAtPoint(Vector2(7, 10), " ", Seed);
	window.setTextAtPoint(Vector2(8, 10), " ", Seed);

	window.setTextAtPoint(Vector2(11, 9), " ", Seed);
	window.setTextAtPoint(Vector2(12, 9), " ", Seed);

	window.setTextAtPoint(Vector2(15, 7), " ", Seed);
	window.setTextAtPoint(Vector2(16, 7), " ", Seed);

	window.setTextAtPoint(Vector2(17, 5), " ", Seed);
	window.setTextAtPoint(Vector2(18, 5), " ", Seed);

	for (int i = 0; i < a_text.size(); i++)
	{
		window.setTextAtPoint(Vector2(i, 16), string(1, a_text[i]) , WHITE);
	}

	window.writeConsole();

}

void Options(vector<string> options)
{
	//window.ClearWindow(false);
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	for (int i = windowHeight; i > windowHeight - (options.size() + 3); i--)
	{
		for (int l = 0; l < windowWidth; l++)
		{
			window.setTextAtPoint(Vector2(l, i), " ", BLACK);
		}
	}
	for (int i = 0; i < options.size(); i++)
	{
		string optionBegin;
		if (i == 0) optionBegin = "A. ";
		else if (i == 1) optionBegin = "B. ";
		else if (i == 2) optionBegin = "C. ";
		else if (i == 3) optionBegin = "D. ";
		else if (i == 4) optionBegin = "E. ";
		for (int ii = 0; ii < optionBegin.size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii, windowHeight - (i + 2)), string(1, optionBegin[ii]), WHITE);
		}
		for (int ii = optionBegin.size(); ii < optionBegin.size() + options[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii, windowHeight - (i + 2)), string(1, options[i][ii - optionBegin.size()]), WHITE);
		}
	}
	SetConsoleCursorPosition(hOut, start);
	window.writeConsole();
	system("pause");
	if (GetKeyDown('A') && options.size() > 0)
	{
		command = options[0];
		return;
	}
	if (GetKeyDown('B') && options.size() > 1)
	{
		command = options[1];
		return;
	}
	if (GetKeyDown('C') && options.size() > 2)
	{
		command = options[2];
		return;
	}
	if (GetKeyDown('D') && options.size() > 3)
	{
		command = options[3];
		return;
	}
	if (GetKeyDown('E') && options.size() > 4)
	{
		command = options[4];
		return;
	}
}

void BackGroundParkCutScene()
{
	//CLOUDS
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", LIGHTBLUE_LIGHTBLUE_BG);
		}
	}
	window.setTextAtPoint(Vector2(0, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(1, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(2, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(3, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(0, 3), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(1, 3), " ", LIGHTBLUE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(19, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(20, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(21, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(22, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(35, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(36, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(37, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(38, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(37, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(38, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	//GRASS
	for (int i = 0; i < 40; i ++)
	{
		for (int ii = 16; ii < 18; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		}
	}
	//SIDEWALK
	for (int i = 0; i < 40; i++)
	{
		for (int ii = 18; ii < 21; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
		}
	}
	//TREE
	for (int i = 0; i < 22; i++)
	{
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 2; i < 20; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 2; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 13), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 12), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 4; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 11), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 10), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 6; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 9), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 8), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 8; i < 20; i++)
	{
		window.setTextAtPoint(Vector2(i, 7), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 8; i < 14; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 1), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 18; i < 24; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_YELLOW_BG);
	}
	//LEAVES
	for (int i = 4; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 1), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 4; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 2; i < 4; i++)
	{
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 6; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 12; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 14; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 16; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 22; i < 24; i++)
	{
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 7), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 24; i < 26; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	//FENCE
	for (int i = 0; i < 40; i+=4)
	{
		for (int ii = 12; ii < 17; ii ++ )
		{
			window.setTextAtPoint(Vector2(i + 0, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
			window.setTextAtPoint(Vector2(i + 1, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
		}
	}
	for (int i = 0; i < 40; i ++)
	{
		window.setTextAtPoint(Vector2(i, 13), " ", LIGHTBLUE_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_LIGHTGREY_BG);
	}
	//BENCH
	for (int i = 25; i < 38; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 16), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 27; i < 36; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", BLACK);
		window.setTextAtPoint(Vector2(i, 15), " ", BLACK);
	}
	for (int i = 25; i < 27; i++)
	{
		window.setTextAtPoint(Vector2(i, 17), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 36; i < 38; i++)
	{
		window.setTextAtPoint(Vector2(i, 17), " ", LIGHTBLUE_YELLOW_BG);
	}
}
void drawTruckCutScene(Vector2 point)
{
	//OUTLINE 1
	for (int i = -2; i < 29; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 1), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 12), " ", BLACK);
	}
	for (int i = 27; i < 29; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = -2; i < 0; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = -2; i < 0; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	//FILL 1
	for (int i = 0; i < 27; i++)
	{
		for (int ii = 2; ii < 12; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
	}
	//FILL 2
	for (int i = 1; i < 7; i++)
	{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", BLACK);
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 8), " ", BLACK);
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", BLACK);
	}
	for (int i = 1; i < 3; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", BLACK);
	}
	for (int i = 5; i < 7; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", BLACK);
	}
	for (int i = 7; i < 9; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 11; i < 13; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 7; i < 13; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 6; i < 9; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + 9, point.getY() - i), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + 10, point.getY() - i), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 13; i < 17; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", BLACK);
	}
	for (int i = 7; i < 10; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + 13, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 14, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 17, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 18, point.getY() - i), " ", BLACK);
	}
	for (int i = 19; i < 25; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 8), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 19; i < 21; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	//WHEELS 1
	for (int i = 0; i < 6; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 1, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	for (int i = 19; i < 25; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 19, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 20, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 23, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 24, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	//OUTLINE 2
	for (int i = 29; i < 31; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 31; i < 33; i++)
	{
		for (int ii = 1; ii < 12; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 33; i < 35; i++)
	{
		for (int ii = 1; ii < 11; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 35; i < 37; i++)
	{
		for (int ii = 1; ii < 10; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 37; i < 41; i++)
	{
		for (int ii = 1; ii < 7; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 41; i < 43; i++)
	{
		for (int ii = 2; ii < 6; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 4), "K", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 4), "d", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 6, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 7, point.getY() - 4), "a", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 8, point.getY() - 4), "p", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 9, point.getY() - 4), "p", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 10, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 11, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 12, point.getY() - 4), "g", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 13, point.getY() - 4), " ", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 14, point.getY() - 4), "S", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 15, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 16, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 17, point.getY() - 4), "c", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 18, point.getY() - 4), "e", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 19, point.getY() - 4), " ", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 20, point.getY() - 4), "1", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 21, point.getY() - 4), "9", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 22, point.getY() - 4), "8", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 23, point.getY() - 4), "3", BLACK_BRIGHTWHITE_BG);
	//FILL 1
	for (int i = 31; i < 35; i++)
	{
		for (int ii = 6; ii < 10; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", AQUA_LIGHTBLUE_BG);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 31, point.getY() - 10), " ", AQUA_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 32, point.getY() - 10), " ", AQUA_LIGHTBLUE_BG);

	window.setTextAtPoint(Vector2(point.getX() + 41, point.getY() - 2), " ", AQUA_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(point.getX() + 42, point.getY() - 2), " ", AQUA_BRIGHTYELLOW_BG);
	//WHEELS
	for (int i = 33; i < 39; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 33, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 34, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 37, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 38, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
}
void DrawParkGirlCutScene(Vector2 point)
{

	window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() + 0), " ", LIGHTBLUE_WHITE_BG);
	for (int i = 0; i < 4; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 1), " ", BLACK);
		for (int ii = 2; ii < 5; ii++) 
		{ 
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG); 
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", LIGHTBLUE_DARKBLUE_BG);
	}
	for (int i = -2; i < 0; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
		for (int ii = 3; ii < 5; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG);
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_DARKBLUE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_DARKBLUE_BG);
	}
	for (int i = 4; i < 6; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
		for (int ii = 3; ii < 5; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG);
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_DARKBLUE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_DARKBLUE_BG);
	}
}

void Cutscene()
{
	if (cutsceneStr == "NULL")
	{
		return;
	}
	if (cutsceneStr == "SYDE_Ep1_Intro")
	{
		CONSOLE_CURSOR_INFO cInfo;
		GetConsoleCursorInfo(hOut, &cInfo);
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
		cout.flush();
		//window.ClearWindow(true);
		//for (int l = 0; l < windowWidth; l++)
		//{
		//	for (int m = 0; m < windowHeight; m++)
		//	{
		//		window.addToLine(m, " ", WHITE);
		//	}
		//}
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE);
			}
		}

		//CUTSCENE
		SetConsoleCursorPosition(hOut, start);
		window.setTextAtPoint(Vector2(12, 10), "January 5th 2019", WHITE);
		window.setTextAtPoint(Vector2(10, 11), "4:00pm - Diptio Park", WHITE);
		window.writeConsole();
		Sleep(3500);
		SetConsoleCursorPosition(hOut, start);
		BackGroundParkCutScene();
		DrawParkGirlCutScene(Vector2(29, 17));
		window.writeConsole();
		Sleep(3500);
		SetConsoleCursorPosition(hOut, start);
		window.setTextAtPoint(Vector2(1, 19), "Girl : *Sigh* ", BLACK_LIGHTGREY_BG);
		window.writeConsole();
		Sleep(2000);
		window.setTextAtPoint(Vector2(1, 19), "              ", BLACK_LIGHTGREY_BG);
		bool drawGirl = true;
		for (int XVal = -60; XVal < 80; XVal++)
		{
			if (XVal >= 27 && drawGirl)
			{
				drawGirl = false;
			}
			SetConsoleCursorPosition(hOut, start);
			BackGroundParkCutScene();
			if (drawGirl)
			{
				DrawParkGirlCutScene(Vector2(29, 17));
			}
			drawTruckCutScene(Vector2(XVal, 17));
			window.writeConsole();
			Sleep(30);
		}
		SetConsoleCursorPosition(hOut, start);
		window.writeConsole();
		SetConsoleCursorPosition(hOut, start);
		window.setTextAtPoint(Vector2(11, 10),"SYDE : Episode One", WHITE);
		window.setTextAtPoint(Vector2(7, 11), "Something You Do Everytime", WHITE);
		window.writeConsole();
		Sleep(5000);
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l,m), " ", WHITE);
			}
		}
		window.setTextAtPoint(Vector2(12, 10), "January 6th 2019", WHITE);
		window.setTextAtPoint(Vector2(3, 11), "10:00am - South York Police Station", WHITE);
		window.writeConsole();
		Sleep(3500);
	}
	if (cutsceneStr == "Watermelon")
	{
		bool foundWatermelonInfo = false;
		vector<string> information = Split(info, ';');
		for (int i = 0; i < information.size(); i++)
		{
			if (information[i] == "atewatermelon")
			{
				PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BLACK, BLACK, WHITE, "MAN THAT WAS A TASTY WATERMELON");
				system("pause");
				foundWatermelonInfo = true;
			}
		}
		if (!foundWatermelonInfo)
		{
			PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, BLACK, WHITE, "OOOO THAT WATERMELON LOOKS TASTY!");
			system("pause");
			Options(vector<string> {"Eat Watermelon", "Leave Watermelon"});
			if (command == "Eat Watermelon")
			{
				info += "atewatermelon;";
			}
			command = "";
		}
	}
	else if (cutsceneStr == "Watermelon002")
	{
		bool foundWatermelonInfo = false;
		vector<string> information = Split(info, ';');
		for (int i = 0; i < information.size(); i++)
		{
			if (information[i] == "atewatermelon")
			{
				PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BLACK, BLACK, WHITE, "THE WATERMELON IS UPSET THAT YOU ATE IT");
				system("pause");
				foundWatermelonInfo = true;
			}
		}
		if (!foundWatermelonInfo)
		{
			PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, BLACK, WHITE, "THE WATERMELON IS HAPPY YOU LET IT LIVE");
			system("pause");
			command = "";
		}
	}
	cutsceneStr = "NULL";
}

// FOR GETTING ALL COMBOS
void outputVar()
{
	ifstream newFile("NoCombo.txt", ios::binary | ios::in);
	ofstream moveFile("NoCombo.txt");
	for (int a = 0; a < 3; a++)
	{
		string varA;
		switch (a)
		{
		case 0:
			varA = " ";
			break;
		case 1:
			varA = "X";
			break;
		default:
			varA = "O";
			break;
		}
		for (int b = 0; b < 3; b++)
		{
			string varB;
			switch (b)
			{
			case 0:
				varB = " ";
				break;
			case 1:
				varB = "X";
				break;
			default:
				varB = "O";
				break;
			}
			for (int c = 0; c < 3; c++)
			{
				string varC;
				switch (c)
				{
				case 0:
					varC = " ";
					break;
				case 1:
					varC = "X";
					break;
				default:
					varC = "O";
					break;
				}
				for (int d = 0; d < 3; d++)
				{
					string varD;
					switch (d)
					{
					case 0:
						varD = " ";
						break;
					case 1:
						varD = "X";
						break;
					default:
						varD = "O";
						break;
					}
					for (int e = 0; e < 3; e++)
					{
						string varE;
						switch (e)
						{
						case 0:
							varE = " ";
							break;
						case 1:
							varE = "X";
							break;
						default:
							varE = "O";
							break;
						}
						for (int f = 0; f < 3; f++)
						{
							string varF;
							switch (f)
							{
							case 0:
								varF = " ";
								break;
							case 1:
								varF = "X";
								break;
							default:
								varF = "O";
								break;
							}
							for (int g = 0; g < 3; g++)
							{
								string varG;
								switch (g)
								{
								case 0:
									varG = " ";
									break;
								case 1:
									varG = "X";
									break;
								default:
									varG = "O";
									break;
								}
								for (int h = 0; h < 3; h++)
								{
									string varH;
									switch (h)
									{
									case 0:
										varH = " ";
										break;
									case 1:
										varH = "X";
										break;
									default:
										varH = "O";
										break;
									}
									for (int i = 0; i < 3; i++)
									{
										string varI;
										switch (i)
										{
										case 0:
											varI = " ";
											break;
										case 1:
											varI = "X";
											break;
										default:
											varI = "O";
											break;
										}
										moveFile << varA << "," << varB << "," << varC << "," << varD << "," << varE << "," << varF << "," << varG << "," << varH << "," << varI << ";\n";
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void drawBrain(string AIBrain)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
		}
	}
	vector<BoardPiece> pieces = {
		BoardPiece(Vector2(0,0), 4), BoardPiece(Vector2(1,0), 3), BoardPiece(Vector2(2,0), 8),
		BoardPiece(Vector2(0,1), 9), BoardPiece(Vector2(1,1), 5), BoardPiece(Vector2(2,1), 1),
		BoardPiece(Vector2(0,2), 2), BoardPiece(Vector2(1,2), 7), BoardPiece(Vector2(2,2), 6),
	};
	AI brain(AIBrain);
	int ii = 0;
	int max = brain.getBrainSize();
	while (ii < max)
	{
		for (int y = 1; y < 10; y = y + 4)
		{
			for (int x = 1; x < 10; x = x + 4)
			{
				Board ticTacToeBoard(pieces, 15, 9);
				vector<string> board = brain.returnBoard(ii);
				int k = 0;
				for (int j = 0; j < 3; j++)
				{
					for (int jj = 0; jj < 3; jj++)
					{
						bool print = true;
						string occupier = board[k];
						if (occupier[0] == '\n' || occupier[0] == '\r')
						{
							if (occupier.size() > 0)
							{
								occupier = occupier[1];
							}
							else
							{
								jj--;
								print = false;
							}
						}
						if (occupier == " ")
						{
							occupier = "*";
						}
						if (print)
						{
							window.setTextAtPoint(Vector2(jj + x, j + y), occupier, WHITE);
							k++;
						}
					}
				}
				vector<string> winningMove = brain.returnWinningMove(ii);
				if (winningMove.size() > 1)
				{
					Vector2 move(stoi(winningMove[0]), stoi(winningMove[1]));
					window.setTextAtPoint(move + Vector2(x, y), "*", BRIGHTRED);
				}
				ii++;
				if (ii >= max)
				{
					window.ClearWindow(false);
					window.writeConsole();
					return;
				}
			}
		}
		window.ClearWindow(false);
		window.writeConsole();
		system("pause");
		window.ClearWindow(true);
		for (int l = 0; l < windowHeight; l++)
		{
			for (int m = 0; m < windowWidth; m++)
			{
				window.addToLine(m, " ", WHITE);
			}
		}
	}
}

void playTicTacToe()
{
	int gameNO = 0;
	int gamesMax = 5;
	while (gameNO < gamesMax || gamesMax <= 0)
	{
		TicTacToe(false, true, 1, dir + "AIBrainO.txt", dir + "AIBrainX.txt"); //AI Boolean, Offset On Board's Position
		gameNO++;
		system("pause");
	}
	window.ClearWindow(false);
	window.setLine(10, " X Wins : " + to_string(XWins) + ", O Wins : " + to_string(OWins) + ", Draws : " + to_string(Draws), BRIGHTWHITE);
	window.writeConsole();
}
// NODE PATH
void nodePath()
{
	// CREATE A BOARD
	// DECLARE THE BOARD WITH VECTORS & VALUES
	// 1 = Path
	// 2 = Finish Node
	// 0 = Wall

    // CREATING THE BOARDPIECES IN A FOR LOOP
	vector<BoardPiece> pieces;
	bool isWall = false;
	bool top = false;
	int heightVal = 5;
	int widthVal = 25;
	for (int xx = 0; xx < widthVal ; xx++)
	{
		for (int yy = 0; yy < heightVal; yy++)
		{
			int bValue = 1;
			if (isWall)
			{
				if (!top && yy != heightVal - 1)
				{
					bValue = 0;
				}
				if (top && yy != 0)
				{
					bValue = 0;
				}
			}
			pieces.push_back(BoardPiece(Vector2(xx, yy), bValue));
		}
		if (isWall)
		{
			top = !top;
		}
		isWall = !isWall;
	}
	pieces[pieces.size() - 1].setValue(2);
	// ADD PIECES TO A NEWLY DECLARED BOARD
	Board nodePathBoard(pieces,0,0);
	// INITIALIZE THE CONSOLE WINDOW 
	// SIZE WIDTH & HEIGHT DECLARED AT TOP OF FILE AS CONST
	window.ClearWindow(true);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
		}
	}

	// SET UP THE VIEW
	for (int l = 0; l < nodePathBoard.getBoard().size(); l++)
	{
		// ONLY NEED TO VISUALLY REPRESENT IT IF IT's A WALL
		if (nodePathBoard.getBoard()[l].getValue() == 0)
		{
			nodePathBoard.setOccupierAt(nodePathBoard.getBoard()[l].getPos(), "|");
		}
		else
		{
			nodePathBoard.setOccupierAt(nodePathBoard.getBoard()[l].getPos(), " ");
		}
		// SET THE WINDOW TEXT TO DISPLAY THE WALL
		window.setTextAtPoint(nodePathBoard.getBoard()[l].getPos(), nodePathBoard.getBoard()[l].getOccupier(), BRIGHTWHITE);
	}
	window.setLine(10, "Attempts : " + to_string(generations), WHITE);
	window.writeConsole();
	window.ClearWindow(false);
	// MARKER/POSITION FOR PLAYER
	Vector2 player(0,0);
	window.setTextAtPoint(player, "*", BRIGHTRED); // PLAYER MARKER
	// GAME LOOP
	int value = 1;
	int moveIndex = 0;
	// RUN INDEFINITELY UNTIL EITHER A. AN UNAVAILABLE NODE HAS BEEN HIT OR B. PLAYER MARKER HAS REACHED THE END NODE
	while (true)
	{
		nodePathBoard.setValueAt(player, 0);
		int lastVal = value;
		// SEARCH FOR PRE-EXISTING MOVES
		ifstream newFile(dir + "PathFile.zz", ios::binary | ios::in);
		string line;
		vector<string> lines(0);
		int lineNo = 0;
		if (newFile.is_open())
		{
			while (getline(newFile, line, '\r'))
			{
				lines.push_back(line);
			}
		}
		Vector2 moveVec;
		if (moveIndex < lines.size())
		{
			vector<string> vec = Split(lines[moveIndex], ',');
			if (vec.size() > 1)
			{
				moveVec = Vector2(stoi(vec[0]), stoi(vec[1]));
			}
			else
			{
				int x = (rand() % 3) - 1;
				int y = 0;
				if (x == 0)
				{
					y = (rand() % 3) - 1;
				}
				moveVec = Vector2(x,y);
			}
		}
		else
		{
			int x = (rand() % 3) - 1;
			int y = 0;
			if (x == 0)
			{
				y = (rand() % 3) - 1;
			}
			moveVec = Vector2(x, y);
		}
		if (!nodePathBoard.pieceExists(player + moveVec))
		{
			return;
		}
		else if (nodePathBoard.getPieceAt(player + moveVec).getValue() == 0)
		{
			return;
		}
		else if (nodePathBoard.pieceExists(player + moveVec) && nodePathBoard.getPieceAt(player + moveVec).getValue() != 0) //do > lastVal to allow skips
		{
			window.setTextAtPoint(player, "X", BLUE_BLUE_BG);
			player += moveVec;
			value = nodePathBoard.getPieceAt(player).getValue();
			window.setTextAtPoint(player, "*", BRIGHTRED);
			ofstream moveFile(dir + "PathFile.zz");
			if (lines.size() > 0)
			{
				if (lines[moveIndex] == "" || lines[moveIndex] == "\n")
				{
					lines.push_back(to_string(moveVec.getX()) + ',' + to_string(moveVec.getY()) + "\n");
				}
			}
			else
			{
				lines.push_back(to_string(moveVec.getX()) + ',' + to_string(moveVec.getY()) + "\n");
			}
			for (int i = 0; i < lines.size(); i++)
			{
				moveFile << lines[i];
			}
			window.ClearWindow(false);
			window.writeConsole();
			moveIndex++;
			if (value == 2)
			{
				foundPath = true;
				return;
			}
			Sleep(75);
		}
	}
	//window.writeConsole();
}

ColourClass determineColour(ColourClass main, ColourClass bg)
{
	if (bg >= BLACK_BLUE_BG && bg < BLACK_GREEN_BG)
	{
		return (ColourClass) (main + BLACK_BLUE_BG);
	}

	if (bg >= BLACK_GREEN_BG && bg < BLACK_AQUA_BG)
	{
		return (ColourClass)(main + BLACK_GREEN_BG);
	}

	if (bg >= BLACK_AQUA_BG && bg < BLACK_RED_BG)
	{
		return (ColourClass)(main + BLACK_AQUA_BG);
	}

	if (bg >= BLACK_RED_BG && bg < BLACK_PURPLE_BG)
	{
		return (ColourClass)(main + BLACK_RED_BG);
	}

	if (bg >= BLACK_PURPLE_BG && bg < BLACK_YELLOW_BG)
	{
		return (ColourClass)(main + BLACK_PURPLE_BG);
	}

	if (bg >= BLACK_YELLOW_BG && bg < BLACK_WHITE_BG)
	{
		return (ColourClass)(main + BLACK_YELLOW_BG);
	}

	if (bg >= BLACK_WHITE_BG && bg < BLACK_LIGHTGREY_BG)
	{
		return (ColourClass)(main + BLACK_WHITE_BG);
	}

	if (bg >= BLACK_LIGHTGREY_BG && bg < BLACK_DARKBLUE_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTGREY_BG);
	}

	if (bg >= BLACK_DARKBLUE_BG && bg < BLACK_BRIGHTGREEN_BG)
	{
		return (ColourClass)(main + BLACK_DARKBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTGREEN_BG && bg < BLACK_LIGHTBLUE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTGREEN_BG);
	}

	if (bg >= BLACK_LIGHTBLUE_BG && bg < BLACK_BRIGHTRED_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTRED_BG && bg < BLACK_LIGHTPURPLE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTRED_BG);
	}

	if (bg >= BLACK_LIGHTPURPLE_BG && bg < BLACK_BRIGHTYELLOW_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTPURPLE_BG);
	}

	if (bg >= BLACK_BRIGHTYELLOW_BG && bg < BLACK_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTYELLOW_BG);
	}

	if (bg >= BLACK_BRIGHTWHITE_BG && bg <= BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTWHITE_BG);
	}
	return main;
}
void PlayLevel(string level, bool jumpAllowed)
{
	//window.ClearWindow(true);
	//for (int l = 0; l < windowWidth; l++)
	//{
	//	for (int m = 0; m < windowHeight; m++)
	//	{
	//		window.addToLine(m, " ", WHITE);
	//	}
	//}
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE);
		}
	}
	vector<RigidBody> rbArr;
	vector<Background> bgArr;
	if (level == "Intro")
	{
		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);

		//HighGround
		for (int i = 0; i < windowWidth - 5; i++)
		{
			rbArr.push_back(PhysicsObject("HighGround" + to_string(i), Vector2(i, 9), true, 0));
		}
		//LowerGround
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("LowerGround" + to_string(i), Vector2(i, 14), true, 0));
		}
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 18), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}

		PhysicsObject door("Exit", Vector2(4, 3), true, 0);
		door.setTrigger(true, "Watermelon");
		rbArr.push_back(door);
	}

	else if (level == "BedroomTest")
	{
		// BUILD BACKGROUND
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				bgArr.push_back(Background(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
			}
		}

		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Floor" + to_string(i), Vector2(i, 19), true, 0));
		}
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Second Floor" + to_string(i), Vector2(i, 14), true, 0));
		}
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Third Floor" + to_string(i), Vector2(i, 9), true, 0));
		}

		//Interactables
		rbArr.push_back(PhysicsObject("Window", Vector2(7, 14), true, 0));
		rbArr[rbArr.size() - 1].setInteract(true);
		rbArr[rbArr.size() - 1].setInteractString("Watermelon");
		rbArr[rbArr.size() - 1].setTrigger(false, "Bedroom");
		rbArr[rbArr.size() - 1].setNewStartPos(rbArr[rbArr.size() - 1].getPos());
		rbArr[rbArr.size() - 1].setColour(DARKBLUE);
		rbArr.push_back(PhysicsObject("Door", Vector2(7, 19), true, 0));
		rbArr[rbArr.size() - 1].setInteract(true);
		rbArr[rbArr.size() - 1].setInteractString("Null");
		rbArr[rbArr.size() - 1].setTrigger(false, "ColourTest");
		rbArr[rbArr.size() - 1].setNewStartPos(Vector2(3, 14));
		rbArr[rbArr.size() - 1].setColour(BRIGHTGREEN);


	}
	else if (level == "Holding_Cell")
	{
		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);
		//BACKGROUND
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				bgArr.push_back(Background(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
			}
		}
		//GROUND
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Floor" + to_string(i), Vector2(i, 19), true, 0));
			rbArr[rbArr.size() - 1].setTag("Floor");
		}
		//CELL
		for (int l = 0; l < 10; l++)
		{
			for (int m = 13; m < 14; m++)
			{
				bgArr.push_back(Background(YELLOW_YELLOW_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 28; l < 38; l++)
		{
			for (int m = 13; m < 14; m++)
			{
				bgArr.push_back(Background(YELLOW_YELLOW_BG, Vector2(l, m), " "));
			}
		}
		//TODO, ADD PERSON ON THE BENCH
		//BARS
		for (int l = 0; l < 2; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 4; l < 6; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 8; l < 10; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 12; l < 14; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 16; l < 18; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 20; l < 22; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 24; l < 26; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 28; l < 30; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 32; l < 34; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int l = 36; l < 38; l++)
		{
			for (int m = 0; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		//Warp To Break_Room_002
		PhysicsObject door("Exit", Vector2(-1, 19), true, 0);
		door.setTrigger(true, "Break_Room_002");
		door.setNewStartPos(Vector2(33, 19));
		door.setTag("Floor");
		rbArr.push_back(door);
	}
	else if (level == "Break_Room")
	{
		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);

		//BACKGROUND
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				bgArr.push_back(Background(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
			}
		}
		//GROUND
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Floor" + to_string(i), Vector2(i, 19), true, 0));
			rbArr[rbArr.size() - 1].setTag("Floor");
		}

		//BENCH LOWER
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 16; m < windowHeight - 1; m++)
			{
				bgArr.push_back(Background(YELLOW_YELLOW_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 15; m < 16; m++)
			{
				bgArr.push_back(Background(BLACK, Vector2(l, m), " "));
			}
		}
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(0, m), " "));
		}
		bgArr.push_back(Background(BLACK, Vector2(8, 17), " "));
		bgArr.push_back(Background(BLACK, Vector2(7, 17), " "));
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(10, m), " "));
		}
		bgArr.push_back(Background(BLACK, Vector2(18, 17), " "));
		bgArr.push_back(Background(BLACK, Vector2(17, 17), " "));
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(20, m), " "));
		}
		bgArr.push_back(Background(BLACK, Vector2(28, 17), " "));
		bgArr.push_back(Background(BLACK, Vector2(27, 17), " "));
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(30, m), " "));
		}
		bgArr.push_back(Background(BLACK, Vector2(36, 17), " "));
		bgArr.push_back(Background(BLACK, Vector2(37, 17), " "));
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(39, m), " "));
		}

		//WINDOW
		for (int l = 10; l < 30; l++)
		{
			for (int m = 6; m < 13; m++)
			{
				bgArr.push_back(Background(YELLOW_LIGHTBLUE_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 10; l < 30; l++)
		{
			for (int m = 5; m < 6; m++)
			{
				bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 10; l < 30; l++)
		{
			for (int m = 9; m < 10; m++)
			{
				bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 10; l < 30; l++)
		{
			for (int m = 13; m < 14; m++)
			{
				bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 8; l < 10; l++)
		{
			for (int m = 5; m < 14; m++)
			{
				bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
			}
		}
		for (int l = 30; l < 32; l++)
		{
			for (int m = 5; m < 14; m++)
			{
				bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
			}
		}

		//TEST INTERACTABLE, DELETE LATER, BUILD ACTUAL ROOM
		rbArr.push_back(PhysicsObject("Window", Vector2(7, 15), true, 0));
		rbArr[rbArr.size() - 1].setInteract(true);
		rbArr[rbArr.size() - 1].setInteractString("Watermelon");
		rbArr[rbArr.size() - 1].setTrigger(false, "Break_Room");
		//rbArr[rbArr.size() - 1].setNewStartPos(rbArr[rbArr.size() - 1].getPos());
		rbArr[rbArr.size() - 1].setColour(RED);

		//Warp To Break_Room_002
		PhysicsObject door("Exit", Vector2(40, 19), true, 0);
		door.setTrigger(true, "Break_Room_002");
		door.setNewStartPos(Vector2(3,19));
		door.setTag("Floor");
		rbArr.push_back(door);

	}
	else if (level == "Break_Room_002")
	{
	PhysicsObject playerMk("player", startPosition, false, 0);
	rbArr.push_back(playerMk);

	//BACKGROUND
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			bgArr.push_back(Background(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
		}
	}
	//GROUND
	for (int i = 0; i < windowWidth; i++)
	{
		rbArr.push_back(PhysicsObject("Floor" + to_string(i), Vector2(i, 19), true, 0));
		rbArr[rbArr.size() - 1].setTag("Floor");
	}
	//WINDOW
	for (int l = 10; l < 30; l++)
	{
		for (int m = 6; m < 13; m++)
		{
			bgArr.push_back(Background(YELLOW_LIGHTBLUE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 5; m < 6; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 9; m < 10; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 13; m < 14; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 8; l < 10; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 30; l < 32; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	//COUCH
	for (int l = 6; l < 34; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(Background(YELLOW_BRIGHTRED_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 9; l < 10; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(l, m), "|"));
		}
	}
	for (int l = 30; l < 31; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(Background(BLACK, Vector2(l, m), "|"));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 17; m < 19; m++)
		{
			bgArr.push_back(Background(YELLOW_RED_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(Background(BLACK_BRIGHTRED_BG, Vector2(l, m), "_"));
		}
	}
	//PILLOWS
	for (int l = 13; l < 18; l++)
	{
		for (int m = 15; m < 16; m++)
		{
			bgArr.push_back(Background(YELLOW_AQUA_BG, Vector2(l, m), " "));
		}
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(Background(BLACK_AQUA_BG, Vector2(l, m), "_"));
		}
	}

	for (int l = 21; l < 26; l++)
	{
		for (int m = 15; m < 16; m++)
		{
			bgArr.push_back(Background(YELLOW_PURPLE_BG, Vector2(l, m), " "));
		}
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(Background(BLACK_PURPLE_BG, Vector2(l, m), "_"));
		}
	}

	//Warp To Break_Room
	PhysicsObject door("Exit", Vector2(-1, 19), true, 0);
	door.setTrigger(true, "Break_Room");
	door.setTag("Floor");
	door.setNewStartPos(Vector2(33, 19));
	rbArr.push_back(door);
	//Warp To Holding Cell
	PhysicsObject doorToCell("Exit", Vector2(40, 19), true, 0);
	doorToCell.setTrigger(true, "Holding_Cell");
	doorToCell.setNewStartPos(Vector2(3, 19));
	doorToCell.setTag("Floor");
	rbArr.push_back(doorToCell);
	}
	else if (level == "Watermelon")
	{
		//Vector2 startPosition(3, 14);
		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);

		//HighGround
		for (int i = 0; i < 6; i++)
		{
			rbArr.push_back(PhysicsObject("HighGround" + to_string(i), Vector2(i, 9), true, 0));
		}
		for (int i = 6; i < 9; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 9), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}
		for (int i = 3; i < 6; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 5), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}
		for (int i = 4; i < 8; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 13), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}
		for (int i = 0; i < 5; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 11), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}
		for (int i = 9; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("HighGround" + to_string(i), Vector2(i, 9), true, 0));
		}
		//LowerGround
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("LowerGround" + to_string(i), Vector2(i, 14), true, 0));
		}
		for (int i = 4; i < 15; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(15, i), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}
		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("Trap" + to_string(i), Vector2(i, 18), true, 0));
			rbArr[rbArr.size() - 1].setTrap(true);
		}

		PhysicsObject door("Exit", Vector2(4, 3), true, 0);
		door.setTrigger(true, "Banana");
		rbArr.push_back(door);

		PhysicsObject door2("Exit", Vector2(20, 13), true, 0);
		door2.setTrigger(true, "Bedroom");
		rbArr.push_back(door2);
	}

	else if (level == "ColourTest")
	{
		ColourClass colour = BLACK;
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				bgArr.push_back(Background(colour, Vector2(l,m), " "));
			}
			colour = (ColourClass)(colour + 3);
		}
		//Vector2 startPosition(3, 12);
		PhysicsObject playerMk("player", startPosition, false, 0);
		rbArr.push_back(playerMk);

		for (int i = 0; i < windowWidth; i++)
		{
			rbArr.push_back(PhysicsObject("LowerGround" + to_string(i), Vector2(i, 14), true, 0));
		}

		rbArr.push_back(PhysicsObject("Interactable", Vector2(7, 14), true, 0));
		rbArr[rbArr.size() - 1].setInteract(true);
		rbArr[rbArr.size() - 1].setInteractString("Watermelon002");
		rbArr[rbArr.size() - 1].setTrigger(false, "ColourTest");
		rbArr[rbArr.size() - 1].setNewStartPos(rbArr[rbArr.size() - 1].getPos());
		rbArr[rbArr.size() - 1].setColour(BRIGHTGREEN);
	}

	// Const Game Logic Variables
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	bool isJump = false;
	Vector2 startPos = rbArr[0].getPos();
	ColourClass playerColour = RED;
	// GAME LOGIC
	while (true)
	{
		// MAKE CONSOLE
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l,m), " ", WHITE);
			}			
		}
		for (int m = 0; m < bgArr.size(); m++)
		{
			window.setTextAtPoint(bgArr[m].pos, bgArr[m].mText, bgArr[m].colour);
		}
		// WRITE CONSOLE
		for (int i = 1; i < rbArr.size(); i++)
		{
			ColourClass colorUse;
			if (rbArr[i].getIsTrap())
			{
				colorUse = determineColour(LIGHTGREY, window.getTextColourAtPoint(rbArr[i].getPos()));
				window.setTextAtPoint(rbArr[i].getPos(), "M", colorUse);
			}
			else if (rbArr[i].getIsTrigger())
			{
				colorUse = determineColour(BRIGHTGREEN, window.getTextColourAtPoint(rbArr[i].getPos()));
				string ptext = "O";
				if (rbArr[i].getTag() == "Floor") ptext = " ";
				window.setTextAtPoint(rbArr[i].getPos(), ptext, colorUse);
			}
			else if (rbArr[i].getInteract())
			{
				colorUse = determineColour(rbArr[i].getColour(), window.getTextColourAtPoint(rbArr[i].getPos()));
				string ptext = "*";
				if (rbArr[i].getTag() == "Floor") ptext = " ";
				window.setTextAtPoint(rbArr[i].getPos(), ptext, colorUse);
			}
			else
			{
				colorUse = determineColour(BRIGHTWHITE, window.getTextColourAtPoint(rbArr[i].getPos()));
				string ptext = "_";
				if (rbArr[i].getTag() == "Floor") ptext = " ";
				window.setTextAtPoint(rbArr[i].getPos(), ptext, colorUse);
			}
		}
		if (rbArr[0].getPos().getY() >= 0)
		{
			playerColour = determineColour(BRIGHTRED, window.getTextColourAtPoint(rbArr[0].getPos()));
			//window.setTextAtPoint(rbArr[0].getPos(), "*",playerColour);
			drawCharacter(rbArr[0].getPos(), charSkins[skinNumber][0], charSkins[skinNumber][1], charSkins[skinNumber][2], charSkins[skinNumber][3], lookAngleStr);
		}
		if (level == "Intro") window.setLine(windowHeight - 1, "Level: Intro---Jump:W|Left:A|Right:D|Down:S", WHITE);
		else if (level == "Watermelon") window.setLine(windowHeight - 1, "Level: Watermelon---Beware The Spikes", WHITE);
		else if (level == "Bedroom_001") window.setLine(windowHeight - 1, "Your Bedroom: Population 1", WHITE);
		else if (level == "ColourTest") window.setLine(windowHeight - 1, "COLOURTEST -- TECH DEMO", WHITE);
		window.writeConsole();
		SetConsoleCursorPosition(hOut, start);
		for (int i = 1; i < rbArr.size(); i++)
		{
			if (rbArr[i].getIsTrigger() && charHitBoxCheck(rbArr[0].getPos(), rbArr[i].getPos(), -2, 6, 0, 10))
			{
				levelBonus = rbArr[i].getTriggerLevel();
				startPosition = rbArr[i].getNewStartPos();
				return;
			}
			if (rbArr[i].getIsTrap() && charHitBoxCheck(rbArr[0].getPos(), rbArr[i].getPos(), -2, 6, 0, 10))
			{
				rbArr[0].setPosition(startPos);
				rbArr[0].setSpeed(0);
				Sleep(2000);
			}
		}
		// GRAVITY
		for (int i = 0; i < rbArr.size(); i++)
		{
			rbArr[i].gravity(rbArr);
		}
		// MOVEMENT VARIABLES
		if (GetKeyDown('D') && rbArr[0].getPos().getX() < windowWidth - 1)
		{
			rbArr[0].setPosition(Vector2(rbArr[0].getPos().getX() + 1, rbArr[0].getPos().getY()));
			lookAngleStr = "Right";
		}
		if (GetKeyDown('A') && rbArr[0].getPos().getX() > 0)
		{
			rbArr[0].setPosition(Vector2(rbArr[0].getPos().getX() - 1, rbArr[0].getPos().getY()));
			lookAngleStr = "Left";
		}
		if (GetKeyDown('P'))
		{
			system("pause");
		}
		if (GetKeyDown('W') && !isJump && jumpAllowed)
		{
			isJump = true;
			if (rbArr[0].getSpeed() == 0)
			{
				rbArr[0].setSpeed(-3);
			}
		}
		else
		{
			isJump = false;
		}
		if (GetKeyDown('E'))
		{
			for (int i = 1; i < rbArr.size(); i++)
			{
				if (rbArr[i].getInteract() && charHitBoxCheck(rbArr[0].getPos(), rbArr[i].getPos(), -2, 6, 0, 10))
				{
					cutsceneStr = rbArr[i].getInteractString();
					levelBonus = rbArr[i].getTriggerLevel();
					startPosition = rbArr[0].getPos();
					return;
				}
			}
		}
		if (GetKeyDown('S') && jumpAllowed)
		{
			rbArr[0].setPosition(Vector2(rbArr[0].getPos().getX(), rbArr[0].getPos().getY() + 1));
		}
		//Sleep(150);
	}

}
string returnRandomNonsense()
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
void introductionScript()
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
			cout << returnRandomNonsense() << endl;
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
void drawTitle(int baseY, int baseX)
{
	//LINE 1
	window.setTextAtPoint(Vector2(baseX, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 13, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 17, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 18, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 19, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 24, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 25, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 26, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 27, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 28, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 29, baseY), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	//LINE 2
	window.setTextAtPoint(Vector2(baseX, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 10, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 12, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 20, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 21, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 24, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 25, baseY + 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	//LINE 3
	window.setTextAtPoint(Vector2(baseX, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 20, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 21, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 24, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 25, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 26, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 27, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 28, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 29, baseY + 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	//LINE 4
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 20, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 21, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 24, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 25, baseY + 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	//LINE 5
	window.setTextAtPoint(Vector2(baseX, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 18, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 19, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 24, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 25, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 26, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 27, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 28, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 29, baseY + 4), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
}												   
void introMenu()
{
	//Add Menu Music
	//window.ClearWindow(true);
	//for (int l = 0; l < windowWidth; l++)
	//{
	//	for (int m = 0; m < windowHeight; m++)
	//	{
	//		window.addToLine(m, " ", BLACK);
	//	}
	//}

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
			window.setTextAtPoint(Vector2(l, m), " ", WHITE);
		}
	}
	//window.writeConsole();
	while (true)
	{
		SetConsoleCursorPosition(hOut, start);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE);
			}
		}
		//DRAW TITLE 5 space on each side
		//window.setTextAtPoint(Vector2(10, 5), "SYDE: PRESS 'A' TO PLAY!", BRIGHTWHITE);
		drawTitle(3,5);

		//window.setTextAtPoint(Vector2(7, 8), "Something You Do Everytime", WHITE);
		string ptext = "Something You Do Everytime";
		for (int i = 7; i < (7 + ptext.size()); i++)
		{
			window.setTextAtPoint(Vector2(i, 8), string(1, ptext[i - 7]), BRIGHTWHITE);
		}
		//window.setTextAtPoint(Vector2(16, 10), "A. START", BRIGHTWHITE);
		string atext = "A. START";
		for (int i = 16; i < (16 + atext.size()); i++)
		{
			window.setTextAtPoint(Vector2(i, 10), string(1, atext[i - 16]), BRIGHTWHITE);
		}
		//window.setTextAtPoint(Vector2(16, 11), "B.  SKIN", BRIGHTWHITE);
		string btext = "B.  SKIN";
		for (int i = 16; i < (16 + btext.size()); i++)
		{
			window.setTextAtPoint(Vector2(i, 11), string(1, btext[i - 16]), BRIGHTWHITE);
		}
		//window.setTextAtPoint(Vector2(16, 12), "C.  QUIT", BRIGHTWHITE);
		string ctext = "C.  QUIT";
		for (int i = 16; i < (16 + ctext.size()); i++)
		{
			window.setTextAtPoint(Vector2(i, 12), string(1, ctext[i - 16]), BRIGHTWHITE);
		}
		//window.setTextAtPoint(Vector2(12, 14), "Char: " + charNames[skinNumber], BRIGHTWHITE);
		string dtext = "Char: " + charNames[skinNumber];
		for (int i = 12; i < (12 + dtext.size()); i++)
		{
			window.setTextAtPoint(Vector2(i, 14), string(1, dtext[i - 12]), BRIGHTWHITE);
		}
		window.setTextAtPoint(Vector2(16, 15), " ", charSkins[skinNumber][0]);
		window.setTextAtPoint(Vector2(17, 15), " ", charSkins[skinNumber][0]);
		window.setTextAtPoint(Vector2(18, 15), " ", charSkins[skinNumber][1]);
		window.setTextAtPoint(Vector2(19, 15), " ", charSkins[skinNumber][1]);
		window.setTextAtPoint(Vector2(20, 15), " ", charSkins[skinNumber][2]);
		window.setTextAtPoint(Vector2(21, 15), " ", charSkins[skinNumber][2]);
		window.setTextAtPoint(Vector2(22, 15), " ", charSkins[skinNumber][3]);
		window.setTextAtPoint(Vector2(23, 15), " ", charSkins[skinNumber][3]);
		window.writeConsole();
		SetConsoleCursorPosition(hOut, start);
		if (GetKeyDown('A'))
		{
			return;
		}
		if (GetKeyDown('B'))
		{
			skinNumber++;
			if (skinNumber >= charSkins.size())
			{
				skinNumber = 0;
			}
		}
		if (GetKeyDown('C'))
		{
			exit(NULL);
		}
	}
}
void drawBee(int baseY, int baseX, bool setUp)
{
	//window.ClearWindow(true);
	if (setUp)
	{
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
	//LINE 1
	window.setTextAtPoint(Vector2(baseX + 2, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 3, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 4, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 8, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 10, baseY), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 11, baseY), " ", BLACK);

	//LINE 2
	window.setTextAtPoint(Vector2(baseX , baseY + 1), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 1), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 2, baseY + 1), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 1), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 1), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 1), " ", LIGHTGREY_WHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 1), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 1), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 1), " ",  LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 1), " ",  LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 10, baseY + 1), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 1), " ", LIGHTGREY_WHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 1), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 1), " ", BLACK);

	//LINE 3
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 2), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 2), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 2), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 2), " ", LIGHTGREY_WHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 2), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 2), " ", LIGHTGREY_WHITE_BG);
																		
	window.setTextAtPoint(Vector2(baseX + 8, baseY + 2), " ", BLACK);	
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 2), " ", BLACK);	
	window.setTextAtPoint(Vector2(baseX + 10, baseY + 2), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 2), " ", LIGHTGREY_WHITE_BG);
													  
	window.setTextAtPoint(Vector2(baseX + 12, baseY + 2), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 2), " ", BLACK);

	//LINE 4
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 3), " ", BLACK);
													 		  
	window.setTextAtPoint(Vector2(baseX + 6, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 3), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 10, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 3), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 14, baseY + 3), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 3), " ", BLACK);

	//LINE 5
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 4), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 4), " ", LIGHTBLUE_DARKBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 4), " ", LIGHTBLUE_PURPLE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 4), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 4), " ", LIGHTBLUE_RED_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 4), " ", LIGHTBLUE_BRIGHTRED_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 4), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 14, baseY + 4), " ", LIGHTBLUE_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 18, baseY + 4), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 19, baseY + 4), " ", BLACK);

	//LINE 6
	window.setTextAtPoint(Vector2(baseX, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 5), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 2, baseY + 5), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 5), " ", LIGHTBLUE_AQUA_BG);

	window.setTextAtPoint(Vector2(baseX + 4, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 5), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 5), " ", LIGHTBLUE_DARKBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 5), " ", LIGHTBLUE_PURPLE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 5), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 5), " ", LIGHTBLUE_RED_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 5), " ", LIGHTBLUE_BRIGHTRED_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 5), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 14, baseY + 5), " ", LIGHTBLUE_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 5), " ", LIGHTBLUE_BRIGHTGREEN_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 5), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 18, baseY + 5), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 19, baseY + 5), " ", LIGHTGREY_WHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 20, baseY + 5), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 21, baseY + 5), " ", BLACK);

	//LINE 7
	window.setTextAtPoint(Vector2(baseX, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 6), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 2, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 6), " ", LIGHTBLUE_AQUA_BG);

	window.setTextAtPoint(Vector2(baseX + 4, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 6), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 6), " ", LIGHTBLUE_DARKBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 6), " ", LIGHTBLUE_PURPLE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 6), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 6), " ", LIGHTBLUE_RED_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 6), " ", LIGHTBLUE_BRIGHTRED_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 6), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 14, baseY + 6), " ", LIGHTBLUE_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 6), " ", LIGHTBLUE_BRIGHTGREEN_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 6), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 18, baseY + 6), " ", LIGHTGREY_WHITE_BG);
	window.setTextAtPoint(Vector2(baseX + 19, baseY + 6), " ", LIGHTGREY_WHITE_BG);

	window.setTextAtPoint(Vector2(baseX + 20, baseY + 6), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 21, baseY + 6), " ", BLACK);

	//LINE 8
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 7), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 7), " ", LIGHTBLUE_DARKBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 7), " ", LIGHTBLUE_PURPLE_BG);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 7), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 10, baseY + 7), " ", LIGHTBLUE_RED_BG);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 7), " ", LIGHTBLUE_BRIGHTRED_BG);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 7), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 14, baseY + 7), " ", LIGHTBLUE_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 7), " ", LIGHTBLUE_BRIGHTGREEN_BG);

	window.setTextAtPoint(Vector2(baseX + 16, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 17, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 18, baseY + 7), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 19, baseY + 7), " ", BLACK);

	//LINE 9
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 8), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 6, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 8), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 8, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 10, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 11, baseY + 8), " ", BLACK);

	window.setTextAtPoint(Vector2(baseX + 12, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 13, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 14, baseY + 8), " ", BLACK);
	window.setTextAtPoint(Vector2(baseX + 15, baseY + 8), " ", BLACK);

	string ptext = "Team Freebee Games";
	for (int i = baseX + 2; i < (baseX + 2 + ptext.size()); i++)
	{
		window.setTextAtPoint(Vector2(i, baseY + 10), string(1,ptext[i - (baseX + 2)]), BLACK_BRIGHTWHITE_BG);
	}
	//window.setTextAtPoint(Vector2(baseX + 2, baseY + 10), "Team Freebee Games", BLACK_BRIGHTWHITE_BG);
	window.writeConsole();
	//Sleep(5000);
}
void poweredBySYDEEngine(int baseY, int baseX)
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
	//LINE 1
	window.setTextAtPoint(Vector2(baseX + 0, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	//LINE 2
	window.setTextAtPoint(Vector2(baseX + 0, baseY + 1), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 1), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	//LINE 3
	window.setTextAtPoint(Vector2(baseX + 0, baseY + 2), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 2), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 2), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 2), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 2), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 2), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(baseX + 6, baseY + 2), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 2), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 8, baseY + 2), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 2), " ", LIGHTBLUE_LIGHTBLUE_BG);
	//LINE 4
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 3), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 3), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	//LINE 5
	window.setTextAtPoint(Vector2(baseX + 0, baseY + 4), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 1, baseY + 4), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 2, baseY + 4), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 3, baseY + 4), " ", BRIGHTYELLOW_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 4), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 4), " ", BRIGHTGREEN_BRIGHTGREEN_BG);
	window.setTextAtPoint(Vector2(baseX + 6, baseY + 4), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 4), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 8, baseY + 4), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 4), " ", LIGHTBLUE_LIGHTBLUE_BG);
	//LINE 6
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 5), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 5), " ", LIGHTBLUE_LIGHTBLUE_BG);
	//LINE 7															
	window.setTextAtPoint(Vector2(baseX + 4, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 5, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 6, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 7, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 8, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(baseX + 9, baseY + 6), " ", LIGHTBLUE_LIGHTBLUE_BG);

	//window.setTextAtPoint(Vector2(baseX - 6, baseY + 9), "Powered by SYDE Engine", BLACK_BRIGHTWHITE_BG);
	string ptext = "Powered by SYDE Engine";
	for (int i = baseX - 6; i < (baseX - 6 + ptext.size()); i++)
	{
		window.setTextAtPoint(Vector2(i, baseY + 9), string(1, ptext[i - (baseX - 6)]), BLACK_BRIGHTWHITE_BG);
	}
	window.writeConsole();
}
void introCreditsScript()
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
void opening()
{
	// OPENING
   introductionScript();
   introCreditsScript();
   bool setUp = true;
   for (int i = -10; i < 5; i++)
   {
   	drawBee(i, 9, setUp);
	setUp = false;
   	Sleep(50);
   }
   PlaySound(TEXT("EngineFiles\\electronicchime.wav"), NULL, SND_FILENAME | SND_ASYNC);
   Sleep(1250);
   for (int i = 5; i < 22; i++)
   {
   	drawBee(i, 9, setUp);
   	Sleep(50);
   }
   for (int i = -10; i < 5; i++)
   {
   	poweredBySYDEEngine(i, 15);
   	Sleep(50);
   }
   PlaySound(TEXT("EngineFiles\\electronicchime.wav"), NULL, SND_FILENAME | SND_ASYNC);
   Sleep(1250);
   for (int i = 5; i < 22; i++)
   {
   	poweredBySYDEEngine(i, 15);
   	Sleep(50);
   }
    introMenu();
}
// MAIN FUNCTION
int main()
{
	srand(time(NULL));
	//CENTER THE WINDOW
	window.setOffset(Vector2(2, 0));
	//generateart();
	
	//scenes();

	//generateTriangle();
	
	//Test();


	//PlayLevel(levelBonus);
	//// WATERMELON
	//PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, BLACK, WHITE);
	//system("pause");
	////Next Level, ETC
	//PlayLevel(levelBonus);

	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD NewSBSize;
	int Status;

	SMALL_RECT windowSize = { 0,0,windowWidth + 1,windowHeight};
	SetConsoleWindowInfo(hOut, TRUE, &windowSize);

	GetConsoleScreenBufferInfo(hOut, &SBInfo);
	COORD scrollbar = {
		SBInfo.srWindow.Right - SBInfo.srWindow.Left + 1,
		SBInfo.srWindow.Bottom - SBInfo.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(hOut, scrollbar);
	LPCWSTR title = L"Syde"; //GOOD TITLE, NO CHANGE NEEDED BOSS
	SetConsoleTitleW(title);

	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();

	if (true)
	{
		opening();
	}
	else
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
	while (true)
	{
		Cutscene();
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l,m), " ", BLACK);
			}
		}
		PlayLevel(levelBonus, false);
	}
	// select fruit based off level
	//BOW BASED OFF WATERMELON
	//PixelArt(BLACK, BLACK, YELLOW_YELLOW_BG, BLACK, BRIGHTWHITE_BRIGHTWHITE_BG, WHITE);
	//Jump Simulation
	//outputVar();
	
	//playTicTacToe();
	//window.ClearWindow(false);
	
	//drawBrain(dir + "AIBrainO.txt");
	
	//while (!foundPath)
	//{
	//	nodePath();
	//	generations++;
	//}
	//window.setLine(10, "Attempts Required For Path : " + to_string(generations), WHITE);
	//window.ClearWindow(false);
	//window.writeConsole();
	system("pause");
}
