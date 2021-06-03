#include "pch.h"
#include "SYDESound.h"

DWORD BaseSYDESoundSettings::m_SoundVolume = DWORD(-1717986918);

void BaseSYDESoundSettings::changeDefaultVolume(SYDESoundVolume m_Volume)
{
	switch (m_Volume)
	{
	case SYDE_VOLUME_LOW:
		m_SoundVolume = DWORD(858993459);
		break;
	case SYDE_VOLUME_NML:
		m_SoundVolume = DWORD(1717986918);
		break;
	case SYDE_VOLUME_MED:
		m_SoundVolume = DWORD(-1717986918);
		break;
	case SYDE_VOLUME_HIG:
		m_SoundVolume = DWORD(-858993459);
		break;
	case SYDE_VOLUME_OFF:
		m_SoundVolume = DWORD(0);
		break;
	default:
		m_SoundVolume = DWORD(1717986918);
		break;
	}
}

DWORD BaseSYDESoundSettings::getVolume(SYDESoundVolume m_Volume)
{
	switch (m_Volume)
	{
	case SYDE_VOLUME_LOW:
		return DWORD(858993459);
	case SYDE_VOLUME_NML:
		return DWORD(1717986918);
	case SYDE_VOLUME_MED:
		return DWORD(-1717986918);
	case SYDE_VOLUME_HIG:
		return DWORD(-858993459);
	case SYDE_VOLUME_OFF:
		return DWORD(0);
	default:
		return DWORD(1717986918);
	}
}

void SYDESoundFile::playSound()
{
	waveOutSetVolume(0, m_SoundVolume);
	PlaySound((WCHAR*)m_FileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void SYDESoundFile::playSoundLooped()
{
	waveOutSetVolume(0, m_SoundVolume);
	PlaySound((WCHAR*)m_FileName.c_str(), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void SYDESoundFile::stopSound()
{
	PlaySound(NULL, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}