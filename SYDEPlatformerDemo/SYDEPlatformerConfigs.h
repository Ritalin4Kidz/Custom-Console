#pragma once
#include <string>

using namespace std;
class SYDEPlatformerControls
{
public:
	static void setJumpButton(string newConfig) { m_JumpButton = newConfig; }
	static string getJumpButton() { return m_JumpButton; }

	static void setLeftButton(string newConfig) { m_LeftButton = newConfig; }
	static string getLeftButton() { return m_LeftButton; }

	static void setRightButton(string newConfig) { m_RightButton = newConfig; }
	static string getRightButton() { return m_RightButton; }

	static void setDownButton(string newConfig) { m_DownButton = newConfig; }
	static string getDownButton() { return m_DownButton; }

private:
	static string m_JumpButton;
	static string m_LeftButton;
	static string m_RightButton;
	static string m_DownButton;
};