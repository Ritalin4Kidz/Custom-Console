#include "WolfEnemy.h"

void WolfEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new BiteMove()),
		std::shared_ptr<Move>(new ScaryFaceMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\Wolf.bmp", 120, 30, 10, 10, 0, 36));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(90); //120
	this->setDefence(10); //220
	this->setMagicAttack(10); //290
	this->setMagicDefence(10); //300
	this->setSpeed(120);
	this->setName("Wolf");
	this->setType(Melee);
	xpGainedFromFight = (100 * lvl) / 5;

	this->setMoney((rand() % (10 * lvl)) + (3 * lvl));
}

std::shared_ptr<Move> WolfEnemy::determineMove(Character opponent)
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
