#include "SmokingCrab.h"

void SmokingCrab::init_Char(int lvl)
{
	SetMoves(vector<Move*>({
	new SmokeBreakMove(),
	new BoneClubMove(),
	new SmokeBreakMove(),
	new SmokeBreakMove(),
		}));
	m_LastEffortMove = new ScrapMove();
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimationSmoking.bmp", 40, 130, 10, 10, 0, 51));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(90); //120
	this->setDefence(40); //220
	this->setMagicAttack(90); //290
	this->setMagicDefence(40); //300
	this->setSpeed(40);
	this->setName("Smoking Crab");
	this->setType(Water);
	m_EnemyTag = "Boss";
}

Move* SmokingCrab::determineMove(Character opponent)
{
	vector<Move*> moves = getUsableMoves();
	if (moves.size() == 0)
	{
		return m_LastEffortMove;
	}
	else
	{
		int index = rand() % moves.size();
		return moves[index];
	}
}
