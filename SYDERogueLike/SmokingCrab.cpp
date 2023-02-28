#include "SmokingCrab.h"

void SmokingCrab::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new SmokeBreakMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
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

std::shared_ptr<Move> SmokingCrab::determineMove(Character opponent)
{
	vector<std::shared_ptr<Move>> moves = getUsableMoves();
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
