#include "pch.h"
#include "CustomAnimationAsset.h"
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

bool CustomAnimationAsset::_DeltatimeFrame = false;
//30FPS
float CustomAnimationAsset::_standardMaxFrameTime = 0.03f;

void CustomAnimationAsset::operator=(CustomAnimationAsset other)
{
	this->m_Frames = other.m_Frames;
	this->frame_number = 0;
	this->max_frame_time = other.max_frame_time;
}


void CustomAnimationAsset::setFrame(int aFrameNo)
{
	if (aFrameNo >= m_Frames.size() || aFrameNo < 0 )
	{
		frame_number = m_Frames.size() - 1;
	}
	else
	{
		frame_number = aFrameNo;
	}
}

ConsoleWindow CustomAnimationAsset::draw_asset(ConsoleWindow window, Vector2 point)
{
	if (m_Frames.size() > 0)
	{
		window = m_Frames[frame_number].draw_asset(window, point);
		if (!m_paused)
		{
			nextFrame();
		}
		if (frame_number >= m_Frames.size())
		{
			if (m_looping) frame_number = 0;
			else frame_number = m_Frames.size() - 1;
		}
	}
	return window;
}

void CustomAnimationAsset::setAsset(vector<CustomAsset> frames)
{
	m_Frames = frames;
}

void CustomAnimationAsset::nextFrame()
{
	if (_DeltatimeFrame)
	{
		frame_time += SYDEDefaults::getDeltaTime();
		while (frame_time >= max_frame_time)
		{
			frame_time -= max_frame_time;
			frame_number++;
		}
	}
	else
	{
		frame_number++;
	}
}

vector<CustomAsset> AnimationSpriteSheets::load_from_animation_sheet(const WCHAR * bmpFile, int file_totalWidth, int file_totalHeight, int sprite_width, int sprite_height, int startingSprite, int noSprites)
{
	Bitmap temp(bmpFile, FALSE);
	vector<CustomAsset> tempAssetVec;
	vector<ColourClass> tempVec;
	int yPos = 0;
	int xPos = 0;
	xPos += (sprite_width * startingSprite);

	while (xPos >= file_totalWidth)
	{
		yPos += sprite_height;
		xPos -= file_totalWidth;
	}
	for (int ih = 0; ih < noSprites; ih++)
	{
		for (int i = 0; i < sprite_height; i++)
		{
			for (int ii = 0; ii < sprite_width; ii++)
			{
				Gdiplus::Color pixelColor;
				temp.GetPixel(ii + xPos, i + yPos, &pixelColor);
				ColourClass colour_use = AssetsClass::return_colour_from_RGB(to_string(pixelColor.GetR()), to_string(pixelColor.GetG()), to_string(pixelColor.GetB()));
				tempVec.push_back(colour_use); //twice for one pixel
				tempVec.push_back(colour_use);
			}
		}
		tempAssetVec.push_back(CustomAsset(sprite_width * 2, sprite_height, tempVec));
		tempVec.clear();
		xPos += sprite_width;
		if (xPos >= file_totalWidth)
		{
			yPos += sprite_height;
			xPos = 0;
		}
	}
	return tempAssetVec;
}
