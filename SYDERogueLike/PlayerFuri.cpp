#include "PlayerFuri.h"

void PlayerFuri::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		std::shared_ptr<Move>(new EmberMove()),
		std::shared_ptr<Move>(new FireballMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\FuriBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(30); //70
	this->setMaxHealth(30); //70
	this->setAttack(50); //120
	this->setDefence(100); //220
	this->setMagicAttack(70); //290
	this->setMagicDefence(10); //300
	this->setName("Furi");
	this->setSpeed(20);
	this->setType(Fire);
}
