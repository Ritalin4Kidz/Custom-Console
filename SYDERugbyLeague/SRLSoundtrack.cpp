#include "pch.h"
#include "SRLSoundtrack.h"

void SRLSoundtrack::start()
{
	play();
}

ConsoleWindow SRLSoundtrack::displaySongInformation(ConsoleWindow window, int baseX)
{
	int length = m_Soundtrack[selectedSong].getLongerString().length() + 4;
	for (int i = baseX; i < baseX + length; i++)
	{
		for (int ii = baseY; ii < baseY + 3; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BRIGHTWHITE_BRIGHTRED_BG);
		}
	}
	string Artists = m_Soundtrack[selectedSong].m_SongArtist;
	if (m_Soundtrack[selectedSong].m_FeatArtist != "")
	{
		Artists += " " + m_Soundtrack[selectedSong].m_FeatArtist;
	}
	for (int i = baseX + 2, j = 0; i < Artists.length(); i++, j++)
	{
		window.setTextAtPoint(Vector2(i, baseY), Artists.substr(j, j + 1), BRIGHTWHITE_BRIGHTRED_BG);
	}

	for (int i = baseX + 2, j = 0; i < m_Soundtrack[selectedSong].m_SongTitle.length(); i++, j++)
	{
		window.setTextAtPoint(Vector2(i, baseY + 1), m_Soundtrack[selectedSong].m_SongTitle.substr(j, j + 1), BRIGHTWHITE_BRIGHTRED_BG);
	}
	return window;
}

void SRLSoundtrack::play()
{
	if (playing)
	{
		m_pSound->release();
		m_pFmodSystem->close();
		m_pFmodSystem->release();


		FMOD_RESULT result;
		m_pFmodSystem = NULL;
		//result = m_pChannel->setFrequency(musicSpeed);
		// Create the main system object. 
		result = FMOD::System_Create(&m_pFmodSystem);
		if (result != FMOD_OK)
		{
			//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return;
		} // Initialize FMOD with 512 channels 
		result = m_pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
		if (result != FMOD_OK)
		{
			//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return;
		}

		//FMOD::Sound* m_pSound;
		result = m_pFmodSystem->createSound(m_Soundtrack[selectedSong].m_SoundFile.c_str(), FMOD_DEFAULT, 0, &m_pSound);
		result = m_pFmodSystem->playSound(m_pSound, 0, true, &m_pChannel);
		result = m_pChannel->setVolume(getDefaultSoundAsFloat());
		//result - m_pChannel->setFrequency(musicSpeed * m_speed);
		result = m_pChannel->setPaused(false);

		FMOD::ChannelGroup* pChannelGroup;
		result = m_pFmodSystem->createChannelGroup("MyChannelGroup", &pChannelGroup);
		result = m_pFmodSystem->playSound(m_pSound, pChannelGroup, false, &m_pChannel);

		displaySongInfo = true;
		songInfoPosition = (m_Soundtrack[selectedSong].getLongerString().size() + 4);
		songInfoPosition = -songInfoPosition;
		songInfoPosition++;
		direction = 1;
	}
}

void SRLSoundtrack::stop()
{
	m_pSound->release();
	m_pFmodSystem->close();
	m_pFmodSystem->release();
}


void SRLSoundtrack::next()
{

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
}


float SRLSoundtrack::getDefaultSoundAsFloat()
{
	switch (BaseSYDESoundSettings::getDefaultVolumeState())
	{
	case SYDE_VOLUME_OFF:
		return 0.0f;
	case SYDE_VOLUME_LOW:
		return 0.1f;
	case SYDE_VOLUME_NML:
		return 0.3f;
	case SYDE_VOLUME_MED:
		return 0.5f;
	case SYDE_VOLUME_HIG:
		return 0.8f;
	}
	return 0.0f;
}

ConsoleWindow SRLSoundtrack::playWindow(ConsoleWindow window)
{
	FMOD_RESULT result;
	result = m_pChannel->setVolume(getDefaultSoundAsFloat());
	m_pFmodSystem->update();
	if (playing)
	{
		timeSongPassed += SYDEDefaults::getDeltaTime();
		if (timeSongPassed > m_Soundtrack[selectedSong].timeOfSong)
		{
			next();
			play();
		}
	}
	if (displaySongInfo)
	{
		int endPosition = m_Soundtrack[selectedSong].getLongerString().size() + 4;
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

string SRLSoundtrackEntry::getLongerString()
{
		if (m_FeatArtist != "")
		{
			if (m_SongTitle.length() > m_SongArtist.length() + m_FeatArtist.length() + 1)
			{
				return m_SongTitle;
			}
			return m_SongArtist + " " + m_FeatArtist;
		}
		if (m_SongTitle.length() > m_SongArtist.length())
		{
			return m_SongTitle;
		}
		return m_SongArtist;
}
