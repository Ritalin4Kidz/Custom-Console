#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
#include <windows.h>
using namespace std;

struct SYDE_ColourValues {
	SYDE_ColourValues(int _r, int _g, int _b) { r = _r; dftr = _r; g = _g; dftg = _g; b = _b; dftb = _b; }
	int r;
	int g;
	int b;

	int dftr;
	int dftg;
	int dftb;

	void operator=(SYDE_ColourValues other) { r = other.r; g = other.g; b = other.b; }
	void set(int _r, int _g, int  _b) { r = _r; dftr = _r; g = _g; dftg = _g; b = _b; dftb = _b; }

	void toDefault() { r = dftr; g = dftg; b = dftb; }
	DWORD toRGB() { return RGB(r, g, b); }
	std::string toRGBStr() { return std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b); }
};

class Font_Settings_Func
{
public:
	/// <summary>
	/// Set up the font of the console with custom sizes/font Note: may cause uneven results
	/// </summary>
	/// <param name="sizeX"></param>
	/// <param name="sizeY"></param>
	/// <param name="font"></param>
	static void set_up_custom_font(int sizeX, int sizeY, const wchar_t* font);


	/// <summary>
	/// Set Up the Console in Arial Format
	/// </summary>
	/// <param name="size"></param>
	static void set_up_arial(int size);

	/// <summary>
	/// set up consola font
	/// </summary>
	/// <param name="size"></param>
	static void set_up_consola(int size);

	/// <summary>
	/// set up default font
	/// </summary>
	/// <param name="size"></param>
	static void set_up_consolas(int size);

	/// <summary>
	/// set up courier new font
	/// </summary>
	/// <param name="size"></param>
	static void set_up_courier(int size);

	/// <summary>
	/// Set up MS gothic font
	/// </summary>
	/// <param name="size"></param>
	static void set_up_gothic(int size);

	/// <summary>
	/// Set up lucida console font
	/// </summary>
	/// <param name="size"></param>
	static void set_up_lucida_console(int size);

private:
	static CONSOLE_FONT_INFOEX getCfi(int sizeX, int sizeY);
};


class Settings {
public:
	Settings() {}
	Settings(string settingsFile);

	Vector2 getOffset() { return Vector2(xOffset, yOffset); }

	vector<string> ReturnCheats();

	int getConsoleHeight() { return ConsoleSizeHeight; }
	int getConsoleWidth() { return ConsoleSizeWidth; }
	void ColourPalette(HANDLE hOut);
	void volumeControl(int volume);

	void setOffset(int x, int y) { xOffset = x; yOffset = y; }

protected:
	SYDE_ColourValues _BLACK = SYDE_ColourValues(12, 12, 12);
	SYDE_ColourValues _BLUE = SYDE_ColourValues(0, 55, 218);
	SYDE_ColourValues _GREEN = SYDE_ColourValues(19, 161, 14);
	SYDE_ColourValues _AQUA = SYDE_ColourValues(58, 150, 221);
	SYDE_ColourValues _RED = SYDE_ColourValues(197, 15, 31);
	SYDE_ColourValues _PURPLE = SYDE_ColourValues(136, 23, 152);
	SYDE_ColourValues _YELLOW = SYDE_ColourValues(193, 156, 0);
	SYDE_ColourValues _WHITE = SYDE_ColourValues(204, 204, 204);
	SYDE_ColourValues _LIGHTGREY = SYDE_ColourValues(118, 118, 118);
	SYDE_ColourValues _DARKBLUE = SYDE_ColourValues(59, 120, 255);
	SYDE_ColourValues _BRIGHTGREEN = SYDE_ColourValues(22, 198, 12);
	SYDE_ColourValues _LIGHTBLUE = SYDE_ColourValues(97, 214, 214);
	SYDE_ColourValues _BRIGHTRED = SYDE_ColourValues(231, 72, 86);
	SYDE_ColourValues _LIGHTPURPLE = SYDE_ColourValues(180, 0, 158);
	SYDE_ColourValues _BRIGHTYELLOW = SYDE_ColourValues(249, 241, 165);
	SYDE_ColourValues _BRIGHTWHITE = SYDE_ColourValues(242, 242, 242);

	int xOffset = 0;
	int yOffset = 0;
	int ConsoleSizeWidth = 40;
	int ConsoleSizeHeight = 20;
	string cheats;
private:

	DWORD VOLUME_LOW = DWORD(858993459);
	DWORD VOLUME_NML = DWORD(1717986918);
	DWORD VOLUME_MED = DWORD(-1717986918);
	DWORD VOLUME_HIG = DWORD(-858993459);
	DWORD VOLUME_OFF = DWORD(0);

};

class AdvancedSettings : public Settings {
public:
	AdvancedSettings() {}
	AdvancedSettings(string settingsFile);


	void addCheat(string c) { cheats += c + ";"; }

	void setBlack(SYDE_ColourValues c) { _BLACK = c; }
	void setBlue(SYDE_ColourValues c) { _BLUE = c; }
	void setGreen(SYDE_ColourValues c) { _GREEN = c; }
	void setAqua(SYDE_ColourValues c) { _AQUA = c; }
	void setRed(SYDE_ColourValues c) { _RED = c; }
	void setPurple(SYDE_ColourValues c) { _PURPLE = c; }
	void setYellow(SYDE_ColourValues c) { _YELLOW = c; }
	void setWhite(SYDE_ColourValues c) { _WHITE = c; }
	void setLightGrey(SYDE_ColourValues c) { _LIGHTGREY = c; }
	void setDarkBlue(SYDE_ColourValues c) { _DARKBLUE = c; }
	void setBrightGreen(SYDE_ColourValues c) { _BRIGHTGREEN = c; }
	void setLightBlue(SYDE_ColourValues c) { _LIGHTBLUE = c; }
	void setBrightRed(SYDE_ColourValues c) { _BRIGHTRED = c; }
	void setLightPurple(SYDE_ColourValues c) { _LIGHTPURPLE = c; }
	void setBrightYellow(SYDE_ColourValues c) { _BRIGHTYELLOW = c; }
	void setBrightWhite(SYDE_ColourValues c) { _BRIGHTWHITE = c; }

private:
};