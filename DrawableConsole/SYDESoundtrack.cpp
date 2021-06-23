#include "pch.h"
#include "SYDESoundtrack.h"

void SYDESoundtrack::start()
{
	m_Soundtrack[selectedSong].m_Sound.playSound();
	displaySongInfo = true;
	songInfoPosition = (m_Soundtrack[selectedSong].m_Sound.getLongerString().size() + 4);
	songInfoPosition = -songInfoPosition;
	songInfoPosition++;
	timeSongPassed = 0;
	direction = 1;
	playing = true;
}

ConsoleWindow SYDESoundtrack::displaySongInformation(ConsoleWindow window, int baseX)
{
	int length = m_Soundtrack[selectedSong].m_Sound.getLongerString().length() + 4;
	for (int i = baseX; i < baseX + length; i++)
	{
		for (int ii = baseY; ii < baseY + 3; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTWHITE_BRIGHTRED_BG);
		}
	}
	for (int i = baseX + 2, j= 0; i < m_Soundtrack[selectedSong].m_Sound.GetArtists().length(); i++, j++)
	{
		window.setTextAtPoint(Vector2(i, baseY), m_Soundtrack[selectedSong].m_Sound.GetArtists().substr(j, j+1), BRIGHTWHITE_BRIGHTRED_BG);
	}
	for (int i = baseX + 2, j = 0; i < m_Soundtrack[selectedSong].m_Sound.GetTitle().length(); i++, j++)
	{
		window.setTextAtPoint(Vector2(i, baseY + 1), m_Soundtrack[selectedSong].m_Sound.GetTitle().substr(j, j + 1), BRIGHTWHITE_BRIGHTRED_BG);
	}
	return window;
}

void SYDESoundtrack::play()
{
	if (playing)
	{
		timeSongPassed += SYDEDefaults::getDeltaTime();
		if (timeSongPassed > m_Soundtrack[selectedSong].m_TimeOfSound)
		{
			next();
		}
	}
}

void SYDESoundtrack::stop()
{
	m_Soundtrack[selectedSong].m_Sound.stopSound();
	playing = false;
}

void SYDESoundtrack::next()
{
	timeSongPassed = 0;
	if (!shuffle)
	{
		selectedSong++;
		if (selectedSong >= m_Soundtrack.size())
		{
			selectedSong = 0;
		}
	}
	else
	{
		int selectedSong2 = selectedSong;
		while (selectedSong2 == selectedSong)
		{
			selectedSong2 = rand() % m_Soundtrack.size();
		}
		selectedSong = selectedSong2;
	}
	m_Soundtrack[selectedSong].m_Sound.playSound();
	displaySongInfo = true;
	songInfoPosition = (m_Soundtrack[selectedSong].m_Sound.getLongerString().size() + 4);
	songInfoPosition = -songInfoPosition;
	songInfoPosition++;
	direction = 1;
}

ConsoleWindow SYDESoundtrack::playWindow(ConsoleWindow window)
{
	if (playing)
	{
		timeSongPassed += SYDEDefaults::getDeltaTime();
		if (timeSongPassed > m_Soundtrack[selectedSong].m_TimeOfSound)
		{
			next();
		}
	}
	if (displaySongInfo)
	{
		int endPosition = m_Soundtrack[selectedSong].m_Sound.getLongerString().size() + 4;
		if (songInfoPosition == -endPosition)
		{
			displaySongInfo = false;
			return window;
		}
		infoTimePassed += SYDEDefaults::getDeltaTime();
		if (infoTimePassed > 0.025f && songInfoPosition != 0)
		{
			songInfoPosition += direction;
			infoTimePassed = 0;
		}
		else if (infoTimePassed > 3 && songInfoPosition == 0)
		{
			direction = -1;
			songInfoPosition += direction;
			infoTimePassed = 0;
		}
		window = displaySongInformation(window, songInfoPosition);
	}
	return window;
}
