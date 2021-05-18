#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"
#include "SYDESounds.h"

enum DemoScenes
{
	SynthScene = 0,
	DrumScene
};

class SYDESoundDemo : public SYDEWindowGame {
public:
	SYDESoundDemo();
	virtual ~SYDESoundDemo() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;

	ConsoleWindow synth(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drum(ConsoleWindow window, int windowWidth, int windowHeight);

private:

	int m_Scene = SynthScene;
	CustomAsset m_Synth;
	SYDESoundFile SynthSoundEffect001 = SYDESoundFile("EngineFiles\\Sounds\\Synth001.wav");
	SYDESoundFile SynthSoundEffect002 = SYDESoundFile("EngineFiles\\Sounds\\Synth002.wav");
	SYDESoundFile SynthSoundEffect003 = SYDESoundFile("EngineFiles\\Sounds\\Synth003.wav");
	SYDESoundFile SynthSoundEffect004 = SYDESoundFile("EngineFiles\\Sounds\\Synth004.wav");
	SYDESoundFile SynthSoundEffect005 = SYDESoundFile("EngineFiles\\Sounds\\Synth005.wav");

	CustomAsset m_Drums;
	SYDESoundFile DrumSoundEffect001 = SYDESoundFile("EngineFiles\\Sounds\\Drum001.wav");
	SYDESoundFile DrumSoundEffect002 = SYDESoundFile("EngineFiles\\Sounds\\Drum002.wav");
	SYDESoundFile DrumSoundEffect003 = SYDESoundFile("EngineFiles\\Sounds\\Drum003.wav");
	SYDESoundFile DrumSoundEffect004 = SYDESoundFile("EngineFiles\\Sounds\\Drum004.wav");
	SYDESoundFile DrumSoundEffect005 = SYDESoundFile("EngineFiles\\Sounds\\Drum005.wav");



};