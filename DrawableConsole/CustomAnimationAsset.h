#pragma once
#include <vector>
#include "ConsoleWindow.h"
#include "CustomAsset.h"
#include "AssetsClass.h"
#include "Defaults.h"
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
	static vector<CustomAsset> load_from_animation_sheet(const WCHAR* bmpFile, int file_totalWidth, int file_totalHeight, int sprite_width, int sprite_height, int startingSprite, int noSprites);
};

class CustomAnimationAsset {
public:
	CustomAnimationAsset() { max_frame_time = _standardMaxFrameTime; }
	CustomAnimationAsset(vector<CustomAsset> frames) { setAsset(frames); max_frame_time = _standardMaxFrameTime;}

	/// <summary>
	/// Set if animation should go to next frame based off deltaTime
	/// </summary>
	/// <param name="deltaTimeAnimation"></param>
	static void SetDeltatimeBasedAnimation(bool deltaTimeAnimation) { _DeltatimeFrame = deltaTimeAnimation; }
	/// <summary>
	/// get if the animation is moving to next frame based off deltaTime
	/// </summary>
	/// <returns></returns>
	static bool getDeltatimeBasedAnimation() { return _DeltatimeFrame; }

	/// <summary>
	/// set the standard time needed to move to the next frame
	/// </summary>
	/// <param name="frameTime"></param>
	static void setStandardMaxFrameTime(float frameTime) { _standardMaxFrameTime = frameTime; }
	/// <summary>
	/// get the standard time needed to move to the next frame
	/// </summary>
	/// <returns></returns>
	static float getStandardMaxFrameTime() { return _standardMaxFrameTime; }

	/// <summary>
	/// get the max frame time
	/// </summary>
	/// <returns></returns>
	float getMaxDeltatime() { return max_frame_time; }

	/// <summary>
	/// set the max frame time
	/// </summary>
	/// <param name="maxFrameTime"></param>
	void setMaxDeltatime(float maxFrameTime) { max_frame_time = maxFrameTime; }

	/// <summary>
	/// get how long the animation has been on this frame
	/// </summary>
	/// <returns></returns>
	float getCurrentFrameTime() { return frame_time; }

	void operator=(CustomAnimationAsset other);
	/// <summary>
	/// Set the frame back to the starting point of the animation
	/// </summary>
	void resetAnimation() { frame_number = 0; }

	/// <summary>
	/// set the frame the animation is on
	/// </summary>
	/// <param name="aFrameNo"></param>
	void setFrame(int aFrameNo);
	/// <summary>
	/// get the frame the animation is on
	/// </summary>
	/// <returns></returns>
	int getFrame() { return frame_number; }
	/// <summary>
	/// get the amount of frames in the animation
	/// </summary>
	/// <returns></returns>
	int getFrameSize() { return m_Frames.size(); }

	/// <summary>
	/// set if the animation loops or not
	/// </summary>
	/// <param name="aLoop"></param>
	void setLooping(bool aLoop) { m_looping = aLoop; }
	/// <summary>
	/// toggle loop status
	/// </summary>
	void toggleLooping() { m_looping = !m_looping; }

	/// <summary>
	/// get if the animation is looping
	/// </summary>
	/// <returns></returns>
	bool getLooping() { return m_looping; }

	/// <summary>
	/// pause/unpause the animation
	/// </summary>
	/// <param name="aPause"></param>
	void setPaused(bool aPause) { m_paused = aPause; }
	/// <summary>
	/// toggle play/pause
	/// </summary>
	void togglePaused() { m_paused = !m_paused; }

	/// <summary>
	/// get if the animation is paused
	/// </summary>
	/// <returns></returns>
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

	/// <summary>
	/// clear the animation asset
	/// </summary>
	void ClearAsset() { for (int i = 0; i < m_Frames.size(); i++) m_Frames[i].ClearAsset(); m_Frames.clear(); }

private:
	void nextFrame();

	vector<CustomAsset> m_Frames;
	int frame_number = 0;
	bool m_looping = false;
	bool m_paused = false;

	float frame_time = 0;
	float max_frame_time;

	static bool _DeltatimeFrame;
	static float _standardMaxFrameTime;
};