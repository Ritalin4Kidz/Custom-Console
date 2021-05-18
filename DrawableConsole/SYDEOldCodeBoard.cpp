#include "pch.h"
#include "SYDEOldCodeBoard.h"



bool SYDEOldCodeBoard::checkWinner(string user)
{
	// CHECK HOW MANY SPACES ARE OCCUPIED
	int occupied = 0;
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getOccupier() == user)
		{
			occupied++;
		}
	}
	// CREATE A VECTOR OF VALUES (DECLARED IN THE BOARDPIECE) THE SIZE OF THE USER'S OCCUPIED SPACES
	vector<int> occupiedValues(occupied);
	occupied = 0;
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getOccupier() == user)
		{
			occupiedValues[occupied] = m_board[i].getValue();
			occupied++;
		}
	}
	/*
		CHECK THAT AT LEAST THREE SPACES HAVE BEEN OCCUPIED BY THE USER
		THEN CHECK IF ANY OF THOSE THREE VALUES' SUM == TARGETVALUE
	*/
	if (occupiedValues.size() >= 3)
	{
		for (int i = 0; i < occupiedValues.size(); i++)
		{
			for (int j = 0; j < occupiedValues.size(); j++)
			{
				for (int k = 0; k < occupiedValues.size(); k++)
				{
					// ALL THREE VALUES HAVE TO BE DIFFERENT (STOPS FOR EXAMPLE 5 + 5 + 5)
					if (i != k && k != j && i != j)
					{
						if (occupiedValues[i] + occupiedValues[j] + occupiedValues[k] == m_targetValue)
						{
							// IF VALUE IS EQUAL TO TARGETVALUE, THE USER HAS WON
							return true;
						}
					}
				}
			}
		}
	}
	// USER HAS NOT REACHED A WINNING STATE, RETURN FALSE
	return false;
}

bool SYDEOldCodeBoard::pieceExists(Vector2 pos)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getPos() == pos)
		{
			return true;
		}
	}
	return false;
}

SYDEOldCodeBoardPiece SYDEOldCodeBoard::getPieceAt(Vector2 pos)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getPos() == pos)
		{
			return m_board[i];
		}
	}
	return m_board[0];
}

void SYDEOldCodeBoard::setOccupierAt(Vector2 pos, string occupier)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getPos() == pos)
		{
			m_board[i].setOccupier(occupier);
			return;
		}
	}
}

void SYDEOldCodeBoard::setValueAt(Vector2 pos, int value)
{
	for (int i = 0; i < m_board.size(); i++)
	{
		if (m_board[i].getPos() == pos)
		{
			m_board[i].setValue(value);
			return;
		}
	}
}
