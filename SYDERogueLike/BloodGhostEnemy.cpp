#include "BloodGhostEnemy.h"

void BloodGhostEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new SingMove()),
	std::shared_ptr<Move>(new SabotageMove()),
	std::shared_ptr<Move>(new EmberMove()),
	std::shared_ptr<Move>(new SmokeBreakMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BloodGhost.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(30); //70
	this->setMaxHealth(30); //70
	this->setAttack(90); //120
	this->setDefence(10); //220
	this->setMagicAttack(90); //290
	this->setMagicDefence(10); //300
	this->setSpeed(80);
	this->setName("Blood Ghost");
	this->setType(Telekinetic);
	this->setAbility(Ability_Insomnia);
	xpGainedFromFight = (275 * lvl) / 5;
}

std::shared_ptr<Move> BloodGhostEnemy::determineMove(Character opponent)
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
