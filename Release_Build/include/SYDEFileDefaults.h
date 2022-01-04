#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>


using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

namespace fs = std::experimental::filesystem;
class SYDEBMPDimensions
{
public:
	int height;
	int width;
};

class SYDEFileDefaults {
public:

	/// <summary>
	/// Return all the file names in a folder as a vector of strings
	/// </summary>
	/// <param name="path">: folder path</param>
	/// <param name="format">: format filter, '*' will select all</param>
	/// <param name="trimPath"></param>
	/// <returns>filenames</returns>
	static std::vector<std::string> getAllFileNamesInFolder(std::string path, std::string format, bool trimPath, bool trimFormat);

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

	static void deleteAllFilesInFolder(const std::string& dir_path);

	static int getFileCount(std::string path, std::string format);

	static bool exists(const char* filename);
	static SYDEBMPDimensions getBMPDimensions(std::string bmpFile);
};