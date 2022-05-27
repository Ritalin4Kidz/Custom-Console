#include "OrcEnemy.h"

void OrcEnemy::init_Char(int lvl)
{
	SetMoves(vector<Move*>({
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		new SmokeBreakMove(),
		}));

	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", 100, 30, 10, 10, 0, 27));
	setAnimationLoop(true);
}

Move* OrcEnemy::determineMove(Character opponent)
{
	return nullptr;
}
