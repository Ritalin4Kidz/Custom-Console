#include "RabbitEnemy.h"

void RabbitEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new RabbitFoodMove()),
	std::shared_ptr<Move>(new BiteMove()),
	std::shared_ptr<Move>(new SingMove()),
	std::shared_ptr<Move>(new EntangleMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BunnyAnimation.bmp", 40, 180, 10, 10, 0, 72));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(60); //70
	this->setMaxHealth(60); //70
	this->setAttack(5); //120
	this->setDefence(100); //220
	this->setMagicAttack(5); //290
	this->setMagicDefence(10); //300
	this->setSpeed(95);
	this->setName("Bunny");
	this->setType(Grass);
	addStats(lvl);
	xpGainedFromFight = (250 * lvl) / 5;
	this->setAbility(SYDEQuestAbilites::SQA_NaturalBoost);
	this->setMoney((rand() % (10 * lvl)) + (3 * lvl));
}

std::shared_ptr<Move> RabbitEnemy::determineMove(Character opponent)
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
