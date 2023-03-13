#include "OrcEnemy.h"

void OrcEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new SmokeBreakMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", 100, 30, 10, 10, 0, 27));
	setAnimationLoop(true);

    this->setLevel(lvl);
    this->setHealth(30); //70
	this->setMaxHealth(30); //70
    this->setAttack(50); //120
    this->setDefence(100); //220
    this->setMagicAttack(70); //290
    this->setMagicDefence(10); //300
	this->setSpeed(40);
    this->setName("Orc");
    this->setType(Grass);
	xpGainedFromFight = (200 * lvl) / 5;

	this->setMoney((rand() % (10 * lvl)) + (3 * lvl));
}

std::shared_ptr<Move> OrcEnemy::determineMove(Character opponent)
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
