#pragma once
#include <vector>
#include "ConsoleWindow.h"
#include "CustomAsset.h"
#include "AssetsClass.h"
#include <windows.h>

using namespace std;

class AnimationSpriteSheets {
public:
	/// <summary>
	/// load in an animation from a sprite sheet
	/// </summary>
	/// <param name="bmpFile"></param>
	/// <param name="astVars"></param>
	/// <param name="file_totalWidth"></param>
	/// <param name="file_totalHeight"></param>
	/// <param name="sprite_width"></param>
	/// <param name="sprite_height"></param>
	/// <param name="startingSprite"></param>
	/// <param name="noSprites"></param>
	/// <returns></returns>
	static vector<CustomAsset> load_from_animation_sheet(const WCHAR* bmpFile, AssetsClass astVars, int file_totalWidth, int file_totalHeight, int sprite_width, int sprite_height, int startingSprite, int noSprites);
};

class CustomAnimationAsset {
public:
	CustomAnimationAsset() {}
	CustomAnimationAsset(vector<CustomAsset> frames) { setAsset(frames); }

	virtual ~CustomAnimationAsset() {}

	void operator=(CustomAnimationAsset other);
	/// <summary>
	/// Set the frame back to the starting point of the animation
	/// </summary>
	void resetAnimation() { frame_number = 0; }

	void setFrame(int aFrameNo);
	int getFrame() { return frame_number; }
	int getFrameSize() { return m_Frames.size(); }

	void setLooping(bool aLoop) { m_looping = aLoop; }
	void toggleLooping() { m_looping = !m_looping; }

	bool getLooping() { return m_looping; }

	void setPaused(bool aPause) { m_paused = aPause; }
	void togglePaused() { m_paused = !m_paused; }

	bool getPaused() { return m_paused; }

	/// <summary>
	/// Draw the asset to the window, +1 to the frame number (if not paused)
	/// </summary>
	/// <param name="window"></param>
	/// <param name="point"></param>
	/// <returns></returns>
	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point);
	/// <summary>
	/// set the animation to a new asset array
	/// </summary>
	/// <param name="frames"></param>
	void setAsset(vector<CustomAsset> frames);

	void ClearAsset() { for (int i = 0; i < m_Frames.size(); i++) m_Frames[i].ClearAsset(); m_Frames.clear(); }

private:
	vector<CustomAsset> m_Frames;
	int frame_number = 0;
	bool m_looping = false;
	bool m_paused = false;
};