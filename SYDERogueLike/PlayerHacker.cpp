#include "PlayerHacker.h"

void PlayerHacker::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new HackMove()),
		std::shared_ptr<Move>(new SlashMove()),
		std::shared_ptr<Move>(new SmokeBreakMove())
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\HackerBehindAnim.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);

	int stats = 750;
	int health = rand() % 100 + 10;
	this->setHealth(health); //70
	this->setMaxHealth(health); //70
	stats -= (health-10);

	int maxStatSize = stats / 5;
	int statPoint = (rand() % maxStatSize);
	this->setAttack(statPoint + 15); //120
	stats -= statPoint;

	statPoint = (rand() % maxStatSize);
	this->setDefence(statPoint + 15); //220
	stats -= statPoint;

	statPoint = (rand() % maxStatSize);
	this->setMagicAttack(statPoint + 15); //290
	stats -= statPoint;

	statPoint = (rand() % maxStatSize);
	this->setMagicDefence(statPoint + 15); //300
	stats -= statPoint;
	this->setName("Hacker");

	statPoint = (rand() % maxStatSize);
	this->setSpeed(statPoint + 15);
	stats -= statPoint;

	this->setType(Telekinetic);
	this->setAbility(SYDEQuestAbilites::SQA_Immunity);
	this->setMoney(stats);

	addMovePool();
	addStats(lvl);
}

void PlayerHacker::levelUpStats()
{
}

void PlayerHacker::addMovePool()
{
}
