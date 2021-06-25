#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "SYDESound.h"
#include "Defaults.h"
#include "ConsoleWindow.h"

using namespace std;

struct SYDESoundtrackEntry
{
	SYDESoundtrackEntry(SYDESoundFile file, int time) { m_Sound = file, m_TimeOfSound = time; }
	SYDESoundFile m_Sound;
	int m_TimeOfSound = 0;
};

class SYDESoundtrack {
public:
	SYDESoundtrack() {}
	string getSongPlaying() { return m_Soundtrack[selectedSong].m_Sound.GetArtists() + "-" + m_Soundtrack[selectedSong].m_Sound.GetTitle(); }
	void addSong(SYDESoundFile file, int time) { m_Soundtrack.push_back(SYDESoundtrackEntry(file, time)); }
	void addSong(SYDESoundtrackEntry file) { m_Soundtrack.push_back(file); }
	void start();
	void editSongInfo(int index, string Title, string Artist) { m_Soundtrack[index].m_Sound.setSongArtist(Artist); m_Soundtrack[index].m_Sound.setSongTitle(Title); }
	void editSongInfo(int index, string Title, string Artist, string feat) { m_Soundtrack[index].m_Sound.setSongArtist(Artist); m_Soundtrack[index].m_Sound.setSongTitle(Title); m_Soundtrack[index].m_Sound.setFeatureArtist(feat);}
	ConsoleWindow displaySongInformation(ConsoleWindow window, int baseX);
	void play();
	void stop();

	void setYPos(int y) { baseY = y; }

	void next();
	void shuffleSongs(bool isOn, bool refresh) { shuffle = isOn; if (refresh) { selectedSong = -1; next(); } }

	ConsoleWindow playWindow(ConsoleWindow window);
private:
	vector<SYDESoundtrackEntry> m_Soundtrack;
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