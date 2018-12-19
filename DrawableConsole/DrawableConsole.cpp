// DrawableConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include <conio.h>
#include <fstream>
#include "AI.h"

#include "PhysicsObject.h"
#include "RigidBody.h"
int windowWidth = 40;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
ConsoleWindow window(windowHeight);
string levelBonus = "ColourTest";
bool isScene = true;
int XWins = 0;
int OWins = 0;
int Draws = 0;

int generations = 0;
bool foundPath = false;

//GAME VALUES
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Vector2 startPosition(3, 14);
string cutsceneStr = "NULL";

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

void PixelArt(ColourClass skinOuter, ColourClass skinMiddle, ColourClass skinInner, ColourClass Meat, ColourClass Seed, ColourClass BG)
{
	window.ClearWindow(true);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
			window.setTextAtPoint(Vector2(l, m), " ", BG);
		}
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

	window.setLine(16, "OOOO THAT WATERMELON LOOKS TASTY", WHITE);

	window.writeConsole();

}

void Cutscene()
{
	if (cutsceneStr == "NULL")
	{
		return;
	}
	if (cutsceneStr == "Watermelon")
	{
		PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, BLACK, WHITE);
	}
	system("pause");
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
void PlayLevel(string level)
{
	window.ClearWindow(true);
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.addToLine(m, " ", WHITE);
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
		rbArr[rbArr.size() - 1].setInteractString("Watermelon");
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
				window.setTextAtPoint(rbArr[i].getPos(), "O", colorUse);
			}
			else if (rbArr[i].getInteract())
			{
				colorUse = determineColour(rbArr[i].getColour(), window.getTextColourAtPoint(rbArr[i].getPos()));
				window.setTextAtPoint(rbArr[i].getPos(), "*", colorUse);
			}
			else
			{
				colorUse = determineColour(BRIGHTWHITE, window.getTextColourAtPoint(rbArr[i].getPos()));
				window.setTextAtPoint(rbArr[i].getPos(), "_", colorUse);
			}
		}
		if (rbArr[0].getPos().getY() >= 0)
		{
			playerColour = determineColour(BRIGHTRED, window.getTextColourAtPoint(rbArr[0].getPos()));
			window.setTextAtPoint(rbArr[0].getPos(), "*",playerColour);
		}
		if (level == "Intro") window.setLine(windowHeight - 1, "Level: Intro---Jump:W|Left:A|Right:D|Down:S", WHITE);
		else if (level == "Watermelon") window.setLine(windowHeight - 1, "Level: Watermelon---Beware The Spikes", WHITE);
		else if (level == "Bedroom_001") window.setLine(windowHeight - 1, "Your Bedroom: Population 1", WHITE);
		else if (level == "ColourTest") window.setLine(windowHeight - 1, "COLOURTEST -- TECH DEMO", WHITE);
		window.writeConsole();
		SetConsoleCursorPosition(hOut, start);
		for (int i = 1; i < rbArr.size(); i++)
		{
			if (rbArr[i].getIsTrigger() && rbArr[0].getPos() == rbArr[i].getPos())
			{
				levelBonus = rbArr[i].getTriggerLevel();
				return;
			}
			if (rbArr[i].getIsTrap() && rbArr[0].getPos() == rbArr[i].getPos())
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
		}
		if (GetKeyDown('A') && rbArr[0].getPos().getX() > 0)
		{
			rbArr[0].setPosition(Vector2(rbArr[0].getPos().getX() - 1, rbArr[0].getPos().getY()));
		}
		if (GetKeyDown('P'))
		{
			system("pause");
		}
		if (GetKeyDown('W') && !isJump)
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
				if (rbArr[i].getInteract() && rbArr[0].getPos() == rbArr[i].getPos())
				{
					cutsceneStr = rbArr[i].getInteractString();
					levelBonus = rbArr[i].getTriggerLevel();
					startPosition = rbArr[i].getNewStartPos();
					return;
				}
			}
		}
		if (GetKeyDown('S'))
		{
			rbArr[0].setPosition(Vector2(rbArr[0].getPos().getX(), rbArr[0].getPos().getY() + 1));
		}
		//Sleep(150);
	}

}
// MAIN FUNCTION
int main()
{
	srand(time(NULL));

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
	LPCWSTR title = L"Syde"; //Think of title later
	SetConsoleTitleW(title);
	while (true)
	{
		Cutscene();
		PlayLevel(levelBonus);
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
