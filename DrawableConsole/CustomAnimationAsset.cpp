#include "pch.h"
#include "CustomAnimationAsset.h"

void CustomAnimationAsset::operator=(CustomAnimationAsset other)
{
	this->m_Frames = other.m_Frames;
	this->frame_number = 0;
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
			frame_number++;
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
