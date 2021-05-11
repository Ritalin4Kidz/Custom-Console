#include "pch.h"
#include "SYDEFileDefaults.h"

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format)
{
	std::vector<std::string> StringVector = std::vector<std::string>();
	for (const auto& entry : fs::directory_iterator(path))
	{
		StringVector.push_back(std::string(entry.path().generic_string()));
	}
	if (format == "*")
	{
		return StringVector;
	}
	int formatSize = format.length();
	for (int i = 0; i < StringVector.size(); i++)
	{
		std::string temp = StringVector[i].substr(StringVector[i].length() - formatSize);
		if (temp != format)
		{
			StringVector.erase(StringVector.begin() + i);
			i--;
		}
	}
	return StringVector;
}
