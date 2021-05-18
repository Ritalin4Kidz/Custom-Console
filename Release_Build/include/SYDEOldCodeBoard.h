#pragma once
#include "SYDEOldCodeBoardPiece.h"
#include <vector>

using namespace std;
/// <summary>
/// Just a simple tictactoe board, gimme money now
/// </summary>
class SYDEOldCodeBoard {
public:
	SYDEOldCodeBoard(vector<SYDEOldCodeBoardPiece> boardpieces, int targetValue, int a_maxTurns) { m_board = boardpieces; m_targetValue = targetValue; maxTurns = a_maxTurns; }
	virtual ~SYDEOldCodeBoard() {}

	bool checkWinner(string user);
	void setOccupier(int index, string occupier) { m_board[index].setOccupier(occupier); }
	string getOccupier(int index) { m_board[index].getOccupier(); }

	vector<SYDEOldCodeBoardPiece> getBoard() { return m_board; }
	bool pieceExists(Vector2 pos);
	SYDEOldCodeBoardPiece getPieceAt(Vector2 pos);
	void setOccupierAt(Vector2 pos, string occupier);

	void setValueAt(Vector2 pos, int value);
	int getMaxTurns() { return maxTurns; }
private:
	int m_targetValue;
	int maxTurns;
	vector<SYDEOldCodeBoardPiece> m_board;
};