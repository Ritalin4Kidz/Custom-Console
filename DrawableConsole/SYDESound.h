#pragma once
#include <Windows.h>
#include <string>
/*
DWORD VOLUME_LOW = DWORD(858993459);
DWORD VOLUME_NML = DWORD(1717986918);
DWORD VOLUME_MED = DWORD(-1717986918);
DWORD VOLUME_HIG = DWORD(-858993459);
DWORD VOLUME_OFF = DWORD(0);
*/
enum SYDESoundVolume
{
	SYDE_VOLUME_LOW,
	SYDE_VOLUME_NML,
	SYDE_VOLUME_MED,
	SYDE_VOLUME_HIG,
	SYDE_VOLUME_OFF
};

class BaseSYDESoundSettings
{
public:
	static void changeDefaultVolume(SYDESoundVolume m_Volume);
	static DWORD getDefaultVolume() { return m_SoundVolume; }
	static SYDESoundVolume getDefaultVolumeState();
	static DWORD getVolume(SYDESoundVolume m_Volume);

private:
	static DWORD m_SoundVolume;

};

/// <summary>
/// Class for creating basic sound files (Note: does not support overlapping audio)
/// </summary>
class SYDESoundFile {
public:
	SYDESoundFile() {}
	SYDESoundFile(std::string FileName) { m_FileName = std::wstring(FileName.begin(), FileName.end()); m_SoundVolume = BaseSYDESoundSettings::getDefaultVolume(); }
	SYDESoundFile(std::string FileName, SYDESoundVolume m_Volume) { m_FileName = std::wstring(FileName.begin(), FileName.end()); m_SoundVolume = BaseSYDESoundSettings::getVolume(m_Volume); }
	virtual ~SYDESoundFile() {}

	void setSongTitle(std::string Title) { m_SongTitle = Title; }
	void setSongArtist(std::string Artist) { m_SongArtist = Artist; }
	void setFeatureArtist(std::string Artist) { m_FeatArtist = Artist; }


	std::string getLongerString();

	std::string GetTitle() { return m_SongTitle; }
	std::string GetArtists() { return m_SongArtist; }
	std::string GetFeatureArtists() { return m_FeatArtist; }
	/// <summary>
	/// play the sound
	/// </summary>
	void playSound();
	/// <summary>
	/// play the sound (looped)
	/// </summary>
	void playSoundLooped();

	/// <summary>
	/// Stop sounds
	/// </summary>
	void stopSound();

	void setVolume(DWORD volume) { m_SoundVolume = volume; }

private:
	DWORD m_SoundVolume;
	std::wstring m_FileName;

	std::string m_SongTitle;
	std::string m_SongArtist;
	std::string m_FeatArtist = "";
};