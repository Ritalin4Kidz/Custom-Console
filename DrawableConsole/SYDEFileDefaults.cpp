#include "pch.h"
#include "SYDEFileDefaults.h"

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format, bool trimPath)
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
	if (trimPath)
	{
		for (int i = 0; i < StringVector.size(); i++)
		{
			StringVector[i].erase(StringVector[i].begin(), StringVector[i].end() - ((StringVector[i].length() - path.length())- 1));
		}
	}
	return StringVector;
}

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format)
{
	return getAllFileNamesInFolder(path, format, false);
}
