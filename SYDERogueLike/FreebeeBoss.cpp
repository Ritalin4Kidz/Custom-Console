#include "FreebeeBoss.h"

void FreebeeBoss::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new GustMove()),
		std::shared_ptr<Move>(new BeeStingMove()),
		std::shared_ptr<Move>(new BulkUpMove()),
		std::shared_ptr<Move>(new SlashMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\FreebeeEnem.bmp", 36, 48, 12, 12, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(90); //120
	this->setDefence(40); //220
	this->setMagicAttack(90); //290
	this->setMagicDefence(40); //300
	this->setSpeed(40);
	this->setName("Freebee");
	this->setType(Air);
	this->requireBG = true;
	this->setAbility(SYDEQuestAbilites::SQA_Hasten);
	m_EnemyTag = "Boss";
	addStats(lvl);
	this->xDrawPos = 36;
}

std::shared_ptr<Move> FreebeeBoss::determineMove(Character opponent)
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
