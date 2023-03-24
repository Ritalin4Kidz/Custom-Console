#include "SharkBoss.h"

void SharkBoss::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new IceBeamMove()),
		std::shared_ptr<Move>(new WaveMove()),
		std::shared_ptr<Move>(new SlashMove()),
		std::shared_ptr<Move>(new BiteMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\SharkBoss.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(60); //70
	this->setMaxHealth(60); //70
	this->setAttack(60); //120
	this->setDefence(60); //220
	this->setMagicAttack(60); //290
	this->setMagicDefence(60); //300
	this->setSpeed(60);
	this->setName("Shark");
	this->setType(Water);
	this->setAbility(SYDEQuestAbilites::SQA_Hasten);
	addStats(lvl);
	m_EnemyTag = "Boss";
}

std::shared_ptr<Move> SharkBoss::determineMove(Character opponent)
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
