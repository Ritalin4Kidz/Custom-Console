#pragma once
#include "PlayerIncludeHeader.h"
#include <string>
#include "SYDEEngineAssets.h"
class PlayerSelectObject
{
public:

	PlayerSelectObject(int rat, std::string tag, const WCHAR* bmpPath) 
	{
		m_Rating = rat;
		m_CharacterSelectImg.setAsset(20, 10, AssetsClass::get_bmp_as_direct_colour_class_array(bmpPath, 10, 10));
		m_Tag = tag;
	}

	CustomAsset getImg() { return m_CharacterSelectImg; }
	int getRating() { return m_Rating; }
private:
	std::string m_Tag;
	CustomAsset m_CharacterSelectImg;
	int m_Rating;
};

//class TagToHeader
//{
//public:
//	static Player* getNewFromString(int level, std::string tag);
//};
//
//Player* TagToHeader::getNewFromString(int level, std::string tag)
//{
//	return new Player();
//}