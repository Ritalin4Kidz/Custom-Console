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

	std::string getTag() { return m_Tag; }

private:
	std::string m_Tag;
	CustomAsset m_CharacterSelectImg;
	int m_Rating;
};

class TagToPlayer
{
public:
	static Player* getNewFromString(int level, std::string tag)
	{
		if (tag == "Furi")
		{
			return new PlayerFuri(level);
		}
		else if (tag == "Alison")
		{
			return new PlayerAlison(level);
		}
		else if (tag == "Bruce")
		{
			return new PlayerBruce(level);
		}
		else if (tag == "Jordan")
		{
			return new PlayerJordan(level);
		}
		return new Player();
	}
private:
};