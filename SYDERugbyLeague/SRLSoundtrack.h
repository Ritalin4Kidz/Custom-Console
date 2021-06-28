#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "SYDESound.h"
#include "Defaults.h"
#include "ConsoleWindow.h"

#include "SYDESounds.h"

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_codec.h>
#include <fmod_dsp.h>
#include <fmod_dsp_effects.h>
#include <fmod_errors.h>
#include <fmod_output.h>

using namespace std;

struct SRLSoundtrackEntry
{
	SRLSoundtrackEntry(string file, string title, string artist, string feat, int time) { m_SoundFile = file, m_FeatArtist = feat; m_SongTitle = title; m_SongArtist = artist; timeOfSong = time; }
	string m_SoundFile;
	string getLongerString();
	string m_FeatArtist = "";
	string m_SongTitle = "";
	string m_SongArtist = "";
	int timeOfSong;
};

class SRLSoundtrack {
public:
	SRLSoundtrack() {}
	string getSongPlaying() { return m_Soundtrack[selectedSong].m_SongArtist + "-" + m_Soundtrack[selectedSong].m_SongTitle; }
	void addSong(string file, string title, string artist, string feat, int time) { m_Soundtrack.push_back(SRLSoundtrackEntry(file,title, artist, feat, time)); }
	void addSong(SRLSoundtrackEntry file) { m_Soundtrack.push_back(file); }
	void start();
	ConsoleWindow displaySongInformation(ConsoleWindow window, int baseX);
	void play();
	void stop();

	void setOn(bool isOn) { playing = isOn; }

	void setYPos(int y) { baseY = y; }

	void next();
	void shuffleSongs(bool isOn, bool refresh) { shuffle = isOn; if (refresh) { selectedSong = -1; next(); } }

	float getDefaultSoundAsFloat();

	ConsoleWindow playWindow(ConsoleWindow window);
protected:
	FMOD::System* m_pFmodSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
private:
	vector<SRLSoundtrackEntry> m_Soundtrack;
	int selectedSong = 0;
	float timeSongPassed = 0;

	int baseY = 2;

	bool playing = false;
	bool shuffle = false;

	float infoTimePassed = 0;
	bool displaySongInfo = false;
	int songInfoPosition = -20;
	int direction = 1;
};