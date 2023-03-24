#include "FireSkeletonBoss.h"

void FireSkeletonBoss::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new FireballMove()),
		std::shared_ptr<Move>(new EmberMove()),
		std::shared_ptr<Move>(new BloodPactMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\AliBoss.bmp", 60, 20, 10, 10, 0, 12));
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(100); //70
	this->setMaxHealth(100); //70
	this->setAttack(60); //120
	this->setDefence(20); //220
	this->setMagicAttack(80); //290
	this->setMagicDefence(30); //300
	this->setSpeed(20);
	this->setName("Skelly");
	this->setType(Fire);
	this->setAbility(SYDEQuestAbilites::SQA_Hasten);
	addStats(lvl);
	m_EnemyTag = "Boss";
}

std::shared_ptr<Move> FireSkeletonBoss::determineMove(Character opponent)
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
