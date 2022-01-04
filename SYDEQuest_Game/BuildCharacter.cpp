#include "BuildCharacter.h"

BuildCharacter::BuildCharacter()
{
	_TypeOptions = SYDEAdaptiveMenu(vector<SYDEAdaptiveMenu_Item> {
		SYDEAdaptiveMenu_Item(new SYDEButton("Raine", Vector2(1, 2), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Water_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Daisy", Vector2(1, 3), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Grass_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Furi", Vector2(1, 4), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Fire_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Steve", Vector2(1, 5), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Metal_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Bruce", Vector2(1, 6), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Melee_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Wyatt", Vector2(1, 7), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Elect_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Dexter", Vector2(1, 8), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Tele_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Kris", Vector2(1, 9), Vector2(20, 1), BLACK, true),	new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Snow_Char.bmp", 10, 10)), Vector2(20, 10)),
		SYDEAdaptiveMenu_Item(new SYDEButton("Simone", Vector2(1, 10), Vector2(20, 1), BLACK, true),new	CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Air_Char.bmp", 10, 10)), Vector2(20, 10))
	});
	if (Bounties::CrabBounty_Unlocked)
	{
		_TypeOptions.AddOption(SYDEAdaptiveMenu_Item(new SYDEButton("Crab", Vector2(1, 11), Vector2(20, 1), BLACK, true), new CustomAsset(20, 10, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\CharacterBMPS\\Crab_Char.bmp", 10, 10)), Vector2(20, 10)));
	}
	for (int i = 0; i < _TypeOptions.getSize(); i++)
	{
		_TypeOptions[i].setLabel(std::to_string(i));
		_TypeOptions[i].setButtonHighlightColour(RED);
	}

	_TypeOptions.setActive(true);
	_TypeOptions.setPos(Vector2(1, 2));
}

BuildCharacter::~BuildCharacter()
{
	for (int i = _TypeOptions.getSize() - 1; i >= 0; i--)
	{
		delete &_TypeOptions[i];
	}
	delete& _TypeOptions;
}

ConsoleWindow BuildCharacter::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	window.setTextAtPoint(Vector2(12, 1), "SELECT CHARACTER", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 2), "CHARACTER STATS:", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 3), "Type: " + SQFunctions::TypeToString(Character_Stats[_TypeOptions.getSelectedNumber()].m_Type), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 4), "Health: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_hp), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 5), "Attack: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_atk), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 6), "Defence: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_def), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 7), "Magic Attack: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_matk), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 8), "Magic Defence: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_mdef), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(21, 9), "Speed: " + to_string(Character_Stats[_TypeOptions.getSelectedNumber()].m_speed), BLACK_WHITE_BG);
	window = _TypeOptions.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_TypeOptions.nextSelect();
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		SetPlayer();
	}
	return window;
}

void BuildCharacter::SetPlayer()
{
	//400-500 STAT TOTAL TO ALL
	Player* p = new Player();
	int SelectedCharacter = _TypeOptions.getSelectedNumber();
	p->setMaxHealth(Character_Stats[SelectedCharacter].m_hp);
	p->setHealth(Character_Stats[SelectedCharacter].m_hp);
	p->setAttack(Character_Stats[SelectedCharacter].m_atk);
	p->setMagicAttack(Character_Stats[SelectedCharacter].m_matk);
	p->setDefence(Character_Stats[SelectedCharacter].m_def);
	p->setMagicDefence(Character_Stats[SelectedCharacter].m_mdef);
	p->setSpeed(Character_Stats[SelectedCharacter].m_speed);
	p->setType(Character_Stats[SelectedCharacter].m_Type);
	//WATER
	if (_TypeOptions.getSelected().compareLabel("0"))
	{
		p->setName("Raine");
		p->setAbility(Ability_NaturalBoost);
		p->SetMoves(std::vector<Move*>{ new Water_Blast(), new Wave_Splash(), new Lightning_Punch(), new Swarm(), new Water_Slime() });
		//THIS CHARACTER IS PART OF THE FAST LEVELLING GROUP
		p->setXP_To_Next_Level(LevelUPRates::FAST_LEVEL_UP_GROUP_START, LevelUPRates::FAST_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//GRASS
	else if (_TypeOptions.getSelected().compareLabel("1"))
	{
		p->setName("Daisy");
		p->SetMoves(std::vector<Move*>{ new Growth(), new Garden(), new Poison_Flower(), new Entangle(), new Knights_Sword() });
		p->setXP_To_Next_Level(LevelUPRates::FAST_LEVEL_UP_GROUP_START, LevelUPRates::FAST_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//FIRE
	else if (_TypeOptions.getSelected().compareLabel("2"))
	{
		p->setName("Furi");
		p->SetMoves(std::vector<Move*>{ new Fireball(), new Smoke_Break(), new Ember(), new Slash(), new Knights_Sword() });
		p->setXP_To_Next_Level(LevelUPRates::NORMAL_LEVEL_UP_GROUP_START, LevelUPRates::NORMAL_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//METAL
	else if (_TypeOptions.getSelected().compareLabel("3"))
	{
		p->setName("Steve");
		p->SetMoves(std::vector<Move*>{ new Flashbang(), new Bell_Ring(), new Sabotage(), new Skull_Pierce(), new Knights_Sword() });
		p->setXP_To_Next_Level(LevelUPRates::SLOW_LEVEL_UP_GROUP_START, LevelUPRates::SLOW_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//MELEE
	else if (_TypeOptions.getSelected().compareLabel("4"))
	{
		p->setName("Bruce");
		p->SetMoves(std::vector<Move*>{ new Bell_Ring(), new Slash(), new Scary_Face(), new Bone_Club(), new Marked() });
		p->setXP_To_Next_Level(LevelUPRates::NORMAL_LEVEL_UP_GROUP_START, LevelUPRates::NORMAL_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//ELECTRIC
	else if (_TypeOptions.getSelected().compareLabel("5"))
	{
		p->setName("Wyatt");
		p->SetMoves(std::vector<Move*>{ new Flashbang(), new Bright_Idea(), new Lightning_Punch(), new Lightning_Bolt(), new Lightning_Slime() });
		p->setXP_To_Next_Level(LevelUPRates::NORMAL_LEVEL_UP_GROUP_START, LevelUPRates::NORMAL_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//TELEKINETIC
	else if (_TypeOptions.getSelected().compareLabel("6"))
	{
		p->setName("Dexter");
		p->setAbility(Ability_Insomnia);
		p->SetMoves(std::vector<Move*>{ new Pitch_Black(), new Rainbow(), new Self_Change(), new Type_Swap(), new Psybeam() });
		p->setXP_To_Next_Level(LevelUPRates::SLOW_LEVEL_UP_GROUP_START, LevelUPRates::SLOW_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//SNOW
	else if (_TypeOptions.getSelected().compareLabel("7"))
	{
		p->setName("Kris");
		p->SetMoves(std::vector<Move*>{ new Sudden_Cold(), new Water_Blast(), new Snowball(), new Icicle_Beam(), new Snowman() });
		p->setXP_To_Next_Level(LevelUPRates::SLOW_LEVEL_UP_GROUP_START, LevelUPRates::SLOW_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	//AIR
	else if (_TypeOptions.getSelected().compareLabel("8"))
	{
		p->setName("Simone");
		p->SetMoves(std::vector<Move*>{ new Sour_Note(), new Smoke_Break(), new Smoke_Cloud(), new Slash(), new Sing() });
		p->setXP_To_Next_Level(LevelUPRates::FAST_LEVEL_UP_GROUP_START, LevelUPRates::FAST_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	else if (_TypeOptions.getSelected().compareLabel("9") && Bounties::CrabBounty_Unlocked)
	{
		p->setName("Crab");
		p->setAbility(Ability_ChainSmoker);
		p->SetMoves(std::vector<Move*>{ new Bubble(), new Smoke_Break(), new Smoke_Cloud(), new Water_Blast(), new Ciggie_Rain() });
		p->setXP_To_Next_Level(LevelUPRates::FAST_LEVEL_UP_GROUP_START, LevelUPRates::FAST_LEVEL_UP_GROUP_RATE);
		p->setLevel(1);
	}
	else
	{
		//UNABLE TO MAKE CHARACTER
		return;
	}
	for (int i = 0; i < p->getMoves().size(); i++)
	{
		p->addUnlockedMove(p->getMoveAtIndex(i)->getMoveInt());
	}
	//TEST THINGY
	p->addUnlockedMove(_SQ_Self_Destruct);

	SYDEMapGame::m_Player = *p;
	SYDEMapGame::camera_Pos = Vector2(74, 45);
	GameScene::SetScene(LoadingScene);
	delete p;
}
