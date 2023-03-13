#include "PlayerFuego.h"

void PlayerFuego::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SlashMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		std::shared_ptr<Move>(new SabotageMove()),
		std::shared_ptr<Move>(new TypeSwapMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new FuegoSwordMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\FuegoBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(25); //70
	this->setMaxHealth(25); //70
	this->setAttack(80); //120
	this->setDefence(75); //220
	this->setMagicAttack(5); //290
	this->setMagicDefence(75); //300
	this->setName("Fuego");
	this->setSpeed(60);
	this->setType(Metal);
	this->setAbility(Ability_Constant_Struggle);
}
