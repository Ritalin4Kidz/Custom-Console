#pragma once
#include "Vector2.h"
#include <string>


using namespace std;
/// <summary>
/// A piece of the tic tac toe board, $5
/// </summary>
class SYDEOldCodeBoardPiece {
public:
	SYDEOldCodeBoardPiece(Vector2 a_pos, int a_val) { m_pos = a_pos; m_value = a_val; }
	virtual ~SYDEOldCodeBoardPiece() {}

	void setOccupier(string a_val) { occupier = a_val; }
	string getOccupier() { return occupier; }

	int getValue() { return m_value; }
	void setValue(int a_val) { m_value = a_val; }

	Vector2 getPos() { return m_pos; }
private:
	Vector2 m_pos;
	int m_value;
	string occupier = " ";
};