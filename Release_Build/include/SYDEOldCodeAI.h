#pragma once
#include "Vector2.h"
#include <string>
#include "ConsoleWindow.h"
#include <vector>
using namespace std;
/// <summary>
/// The description of this github project at the time of writing (19/05/2021, i need to update it....) says this console uses simplified neural networking at points. That was when this project wasn't
/// even a library yet, and i was just displaying an ai learning winning moves in tic tac toe
/// - Callum/Rit@lin
/// </summary>
class SYDEOldCodeAI {
public:
	SYDEOldCodeAI(string filename) { m_filename = filename; }
	virtual ~SYDEOldCodeAI() {}

	Vector2 bestMove(string board);

	bool existingMove(string board, Vector2 move);

	void addWinMove(string board, Vector2 move);

	vector<string> returnBoard(int index);
	vector<string> returnWinningMove(int index);

	int getBrainSize();
private:
	string m_filename;
};