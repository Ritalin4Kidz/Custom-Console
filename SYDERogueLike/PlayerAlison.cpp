#include "PlayerAlison.h"

void PlayerAlison::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new SingMove()),
		std::shared_ptr<Move>(new GustMove()),
		std::shared_ptr<Move>(new BalloonPopMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\AlisonBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(20); //70
	this->setMaxHealth(20); //70
	this->setAttack(120); //120
	this->setDefence(50); //220
	this->setMagicAttack(120); //290
	this->setMagicDefence(30); //300
	this->setName("Alison");
	this->setSpeed(50);
	this->setType(Air);
}
