#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineUI.h"
#include "SYDEFileDefaults.h"
#include "Vector2.h"

#include "SYDESpecial.h"

#include "SYDEOptionCycler.h"

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

	SYDEOptionCycler cycler = SYDEOptionCycler(Vector2(0, 18), 20, BLACK_BRIGHTWHITE_BG, false, vector<SYDEOptionCyclerItem>({
		SYDEOptionCyclerItem(0,"TestItem"),
		SYDEOptionCyclerItem(1,"CheekyNandos"),
		SYDEOptionCyclerItem(2,"Hehehhehe"),
		SYDEOptionCyclerItem(3,"Lovers"),
		}));

	vector<Biome> _biomes;
};