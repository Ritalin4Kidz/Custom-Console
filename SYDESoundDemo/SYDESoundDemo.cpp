#include "SYDESoundDemo.h"
AssetsClass SYDESoundDemo::astVars = AssetsClass();
SYDESoundDemo::SYDESoundDemo()
{
	BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_NML);


	SYDEBMPDimensions fileSize = SYDEFileDefaults::getBMPDimensions("EngineFiles\\Bitmaps\\Synth.bmp");
	m_Synth = CustomAsset(fileSize.width * 2, fileSize.height, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\Synth.bmp", fileSize.width, fileSize.height));
	m_Drums = CustomAsset(fileSize.width * 2, fileSize.height, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\Drum.bmp", fileSize.width, fileSize.height));
}

ConsoleWindow SYDESoundDemo::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}

	switch (static_cast<DemoScenes>(m_Scene))
	{
		case SynthScene:
			window = synth(window, windowWidth, windowHeight);
			break;
		case DrumScene:
			window = drum(window, windowWidth, windowHeight);
			break;
	}
	window.setTextAtPoint(Vector2(0, 19), "Ctrl:ASDFG-Play Note,Space-Change Inst. ", BLACK_BRIGHTWHITE_BG);
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_Scene++;
		if (m_Scene > DrumScene)
		{
			m_Scene = 0;
		}
	}
	return window;
}

ConsoleWindow SYDESoundDemo::synth(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_Synth.draw_asset(window,Vector2(0, 0));
	if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		SynthSoundEffect001.playSound();
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEYDOWN))
	{
		SynthSoundEffect002.playSound();
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		SynthSoundEffect003.playSound();
	}
	if (SYDEKeyCode::get_key('F')._CompareState(KEYDOWN))
	{
		SynthSoundEffect004.playSound();
	}
	if (SYDEKeyCode::get_key('G')._CompareState(KEYDOWN))
	{
		SynthSoundEffect005.playSound();
	}

	return window;
}

ConsoleWindow SYDESoundDemo::drum(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_Drums.draw_asset(window, Vector2(0, 0));
	if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		DrumSoundEffect001.playSound();
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEYDOWN))
	{
		DrumSoundEffect002.playSound();
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		DrumSoundEffect003.playSound();
	}
	if (SYDEKeyCode::get_key('F')._CompareState(KEYDOWN))
	{
		DrumSoundEffect004.playSound();
	}
	if (SYDEKeyCode::get_key('G')._CompareState(KEYDOWN))
	{
		DrumSoundEffect005.playSound();
	}

	return window;
}
