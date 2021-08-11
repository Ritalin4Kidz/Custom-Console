#pragma once
#pragma once
//https://github.com/sol-prog/roguelike/blob/master/part_4/PerlinNoise.h
#include <vector>

#include "CustomAsset.h"

// THIS CLASS IS A TRANSLATION TO C++11 FROM THE REFERENCE
// JAVA IMPLEMENTATION OF THE IMPROVED PERLIN FUNCTION (see http://mrl.nyu.edu/~perlin/noise/)
// THE ORIGINAL JAVA IMPLEMENTATION IS COPYRIGHT 2002 KEN PERLIN

// I ADDED AN EXTRA METHOD THAT GENERATES A NEW PERMUTATION VECTOR (THIS IS NOT PRESENT IN THE ORIGINAL IMPLEMENTATION)

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

class SYDENoise {
	// The permutation vector
	std::vector<int> p;
public:
	// Initialize with the reference values for the permutation vector
	SYDENoise();
	// Generate a new permutation vector based on the value of seed
	SYDENoise(unsigned int seed);
	// Get a noise value, for 2D images z can have any value
	double noise(double x, double y, double z);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};

class SYDENoiseMapRule
{
public:
	SYDENoiseMapRule() {}
	SYDENoiseMapRule(double f, double c, ColourClass clr, char chr) { m_PrimaryChar = chr, m_SecondaryChar = chr; m_Colour = clr, ceiling = c; floor = f; }
	SYDENoiseMapRule(double f, double c, ColourClass clr, char chr1, char chr2) { m_PrimaryChar = chr1, m_SecondaryChar = chr2; m_Colour = clr, ceiling = c; floor = f; }

	bool isInRange(double v) {
		if (floor == 0 && v < 0)
		{
			return true;
		}
		return v >= floor && v < ceiling;
	}

	ColourClass getColour() { return m_Colour; }
	char getPrimaryChar() { return m_PrimaryChar; }
	char getSecondaryChar() { return m_SecondaryChar; }

private:
	double floor;
	double ceiling;
	ColourClass m_Colour = BLACK;
	char m_PrimaryChar = ' ';
	char m_SecondaryChar = ' ';
};

class SYDENoiseMap
{
public:
	SYDENoiseMap() {}

	SYDENoiseMap(std::vector<SYDENoiseMapRule> NoiseMapRules,ColourClass defaultClr, double seed, int _width, int _height, double gradientLength = 0, double gradientStrength = 0);
	
	SYDENoise getNoiseMap() { return m_NoiseMap; }

	CustomAsset getAsset() { return m_Asset; }

private:

	SYDENoise m_NoiseMap;
	CustomAsset m_Asset;
};

#endif