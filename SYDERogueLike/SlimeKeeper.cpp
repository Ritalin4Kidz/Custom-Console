#include "SlimeKeeper.h"

void SlimeKeeper::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new BulkUpMove()),
	std::shared_ptr<Move>(new HealSlimeMove()),
	std::shared_ptr<Move>(new LightningSlimeMove()),
	std::shared_ptr<Move>(new WaterSlimeMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new DefaultSlimeMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\SlimeKeeper.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(110); //70
	this->setMaxHealth(110); //70
	this->setAttack(10); //120
	this->setDefence(30); //220
	this->setMagicAttack(120); //290
	this->setMagicDefence(100); //300
	this->setSpeed(40);
	this->setName("Slime Keeper");
	this->setAbility(SYDEQuestAbilites::SQA_NaturalBoost);
	this->setType(Melee);
	addStats(lvl);
	m_EnemyTag = "Boss";
}

std::shared_ptr<Move> SlimeKeeper::determineMove(Character opponent)
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
