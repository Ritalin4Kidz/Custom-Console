#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"

#include "SYDESpecial.h"

#include "SYDEOptionCycler.h"
#include "SYDEScrollViewer.h"

enum BiomeType
{
	Grassland =0,
	Desert,
	Ocean,
	Mountain
};

struct Biome
{
	Biome(Vector2 s, Vector2 p) { size = s; pos = p; _biome = static_cast<BiomeType>(rand() % 4); }
	Vector2 size;
	Vector2 pos;
	BiomeType _biome;
	
};

class SYDESurvival : public SYDEWindowGame {
public:
	SYDESurvival() { init(); }
	virtual ~SYDESurvival() {}
	void init();

	void test();

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static AssetsClass astVars;
private:
	CustomAsset m_Island;
	Vector2 m_CameraPos = Vector2(0,0);

	//LOWER THE NUMBER, THE STRONGER THE GRADIENT
	double gradientStrength = 0.999;

	double gradientLength = 85;

	int _height = 2000;
	int _width = 1000;

	BiomeType getBiomeFromPoint(Vector2 point)
	{
		for (int i = 0; i < _biomes.size(); i++)
		{
			bool withinLengthBoundaries = (point.getX() >= _biomes[i].pos.getX() && (point.getX() < _biomes[i].pos.getX() + _biomes[i].size.getX()));
			bool withinHeightBoundaries = (point.getY() >= _biomes[i].pos.getY() && (point.getY() < _biomes[i].pos.getY() + _biomes[i].size.getY()));
			if (withinHeightBoundaries && withinLengthBoundaries)
			{
				return _biomes[i]._biome;
			}
		}
		return Ocean;
	}

	//SYDECheckbox testBox = SYDECheckbox(string("This Is A Test"), Vector2(0,18), BLACK, BLACK_BRIGHTWHITE_BG, false);
	//SYDEVerticalSlider testSlider = SYDEVerticalSlider(Vector2(57, 1), 19, WHITE, BRIGHTWHITE_BRIGHTWHITE_BG);
	Vector2 biomeSize = Vector2(250, 500);

	//SYDEOptionCycler cycler = SYDEOptionCycler(Vector2(0, 18), 20, BLACK_BRIGHTWHITE_BG, false, vector<SYDEOptionCyclerItem>({
	//	SYDEOptionCyclerItem(0,"TestItem"),
	//	SYDEOptionCyclerItem(1,"CheekyNandos"),
	//	SYDEOptionCyclerItem(2,"Hehehhehe"),
	//	SYDEOptionCyclerItem(3,"Lovers"),
	//	}));

	SYDEScrollViewer m_Viewer = SYDEScrollViewer(Vector2(6,2), Vector2(48,10), vector<SYDEScrollViewerElement>(
		{
			SYDEScrollViewerElement(new SYDECheckbox(string("This Is 1 Test"), Vector2(0,1), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG, false)),
			SYDEScrollViewerElement(new SYDECheckbox(string("This Is 2 Test"), Vector2(0,3), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG, false)),
			SYDEScrollViewerElement(new SYDECheckbox(string("This Is 3 Test"), Vector2(0,7), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG, false)),
		}),
		BLACK);

	SYDERadioButtonMenu m_ButtonMenu = SYDERadioButtonMenu(Vector2(0, 1), vector<SYDERadioOption>({
		SYDERadioOption(string("This Is 1 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG),
		SYDERadioOption(string("This Is 2 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG),
		SYDERadioOption(string("This Is 3 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG)
		}));

	vector<Biome> _biomes;
};