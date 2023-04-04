#pragma once
#include "PlayerIncludeHeader.h"
#include <string>
#include "SYDEEngineAssets.h"
#include <vector>
class PlayerSelectObject
{
public:

	PlayerSelectObject(int rat, std::string tag, const WCHAR* bmpPath, std::vector<std::string> desc) 
	{
		m_Rating = rat;
		m_CharacterSelectImg.setAsset(20, 10, AssetsClass::get_bmp_as_direct_colour_class_array(bmpPath, 10, 10));
		m_Tag = tag;
		m_Desc = desc;
	}

	CustomAsset getImg() { return m_CharacterSelectImg; }
	int getRating() { return m_Rating; }

	std::string getTag() { return m_Tag; }
	std::vector<std::string> getDesc() { return m_Desc; }
private:
	std::string m_Tag;
	CustomAsset m_CharacterSelectImg;
	int m_Rating;
	std::vector<std::string> m_Desc;
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
		else if (tag == "Fuego")
		{
			return new PlayerFuego(level);
		}
		else if (tag == "Hacker")
		{
			return new PlayerHacker(level);
		}
		return new Player();
	}
private:
};