#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
class SYDEFileDefaults {
public:

	/// <summary>
	/// Return all the file names in a folder as a vector of strings
	/// </summary>
	/// <param name="path">: folder path</param>
	/// <param name="format">: format filter, '*' will select all</param>
	/// <param name="trimPath"></param>
	/// <returns>filenames</returns>
	static std::vector<std::string> getAllFileNamesInFolder(std::string path, std::string format, bool trimPath);

	/// <summary>
	/// Return all the file names in a folder as a vector of strings
	/// </summary>
	/// <param name="path">: folder path</param>
	/// <param name="format">: format filter, '*' will select all</param>
	/// <returns>filenames</returns>
	static std::vector<std::string> getAllFileNamesInFolder(std::string path, std::string format);
};