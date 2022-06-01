#include "pch.h"
#include "SYDEMathUtils.h"

std::string SYDEMathUtils::VectorToString(Vector2 vec)
{
	return std::string(std::to_string(vec.getX()) + "," + std::to_string(vec.getY()));
}

Vector2 SYDEMathUtils::VectorFromString(std::string vec)
{
	std::vector<std::string> values = Split(vec, ',');
	return Vector2(std::stoi(values[0]), std::stoi(values[1]));
}

std::vector<std::string> SYDEMathUtils::Split(std::string str, char split)
{
	int arraySize = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == split)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == split)
			{
				splitString[arrayNo] = str.substr(0, i);
				str = str.substr(i + 1, str.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = str;
	return splitString;
}
