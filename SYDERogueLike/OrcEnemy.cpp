#include "OrcEnemy.h"

void OrcEnemy::init_Char(int lvl)
{
	SetMoves(vector<Move*>({
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		}));
}

Move* OrcEnemy::determineMove(Character opponent)
{
	return nullptr;
}
