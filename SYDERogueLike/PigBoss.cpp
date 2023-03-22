#include "PigBoss.h"

void PigBoss::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new RabbitFoodMove()),
	std::shared_ptr<Move>(new PigRollMove()),
	std::shared_ptr<Move>(new MudThrowMove()),
	std::shared_ptr<Move>(new BulkUpMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\pig.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(180); //70
	this->setMaxHealth(180); //70
	this->setAttack(5); //120
	this->setDefence(70); //220
	this->setMagicAttack(5); //290
	this->setMagicDefence(70); //300
	this->setSpeed(5);
	this->setName("Piggy");
	this->setType(Melee);
	this->setAbility(SYDEQuestAbilites::SQA_NaturalBoost);
	m_EnemyTag = "Boss";
}

std::shared_ptr<Move> PigBoss::determineMove(Character opponent)
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
