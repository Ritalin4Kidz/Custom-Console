#pragma once
#include "Vector2.h"
#include <string>
#include <vector>
class SYDEMathUtils
{
public:
	static std::string VectorToString(Vector2 vec);

	static Vector2 VectorFromString(std::string vec);
private:
	static std::vector<std::string> Split(std::string str, char split);
};