#include "pch.h"
#include "SYDEFileDefaults.h"

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format, bool trimPath, bool trimFormat)
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
	if (trimFormat)
	{
		for (int i = 0; i < StringVector.size(); i++)
		{
			StringVector[i].erase(StringVector[i].end() - format.length(), StringVector[i].end());
		}
	}
	return StringVector;
}

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format, bool trimPath)
{
	return getAllFileNamesInFolder(path, format, trimPath, false);
}

std::vector<std::string> SYDEFileDefaults::getAllFileNamesInFolder(std::string path, std::string format)
{
	return getAllFileNamesInFolder(path, format, false);
}

int SYDEFileDefaults::getFileCount(std::string path, std::string format)
{
	return getAllFileNamesInFolder(path,format).size();
}

bool SYDEFileDefaults::exists(const char* filename)
{
	return fs::exists(filename);
}

SYDEBMPDimensions SYDEFileDefaults::getBMPDimensions(std::string bmpFile)
{
	FILE* f = fopen(bmpFile.c_str(), "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	fclose(f);
	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	SYDEBMPDimensions dimensions;
	dimensions.width = width;
	dimensions.height = height;
	return dimensions;
}
