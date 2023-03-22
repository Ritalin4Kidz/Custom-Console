#include "AliBoss.h"

void AliBoss::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new FireballMove()),
	std::shared_ptr<Move>(new EmberMove()),
	std::shared_ptr<Move>(new SmokeBreakMove()),
	std::shared_ptr<Move>(new LooseMatchMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\AliBoss.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(30); //120
	this->setDefence(60); //220
	this->setMagicAttack(90); //290
	this->setMagicDefence(50); //300
	this->setSpeed(20);
	this->setName("Ali");
	this->setType(Fire);
	this->setAbility(SYDEQuestAbilites::SQA_ChainSmoker);
	m_EnemyTag = "Boss";
}

std::shared_ptr<Move> AliBoss::determineMove(Character opponent)
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
