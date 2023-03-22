#include "CrabEnemy.h"

void CrabEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new CrabClawMove()),
	std::shared_ptr<Move>(new SmokeBreakMove()),
	std::shared_ptr<Move>(new WaterPinchMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimation.bmp", 40, 30, 10, 10, 0, 11));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(42); //70
	this->setMaxHealth(42); //70
	this->setAttack(70); //120
	this->setDefence(60); //220
	this->setMagicAttack(70); //290
	this->setMagicDefence(10); //300
	this->setSpeed(45);
	this->setName("Crab");
	this->setType(Water);
	xpGainedFromFight = (200 * lvl) / 5;

	this->setMoney((rand() % (10 * lvl)) + (3 * lvl));
}

std::shared_ptr<Move> CrabEnemy::determineMove(Character opponent)
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
