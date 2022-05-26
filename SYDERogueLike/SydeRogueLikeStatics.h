#pragma once
#include <string>
class SydeRogueLikeStatics
{
public:
	static void setSceneTag(std::string sceneTag) { m_SceneTag = sceneTag; }
	static std::string getSceneTag() { return m_SceneTag; }

private:
	static std::string m_SceneTag;
};