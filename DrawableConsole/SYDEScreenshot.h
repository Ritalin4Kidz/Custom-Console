#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#include "AssetsClass.h"
#include <ctime>
#include<iostream>
#include<algorithm>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
enum SYDEScreenshotError
{
	SCREENSHOT_SUCCESS,
	SCREENSHOT_ERROR
};

class SYDEScreenshot {
public:
	/// <summary>
	/// Initialize settings for screenshots, creates directory in appdata if non-existant
	/// </summary>
	static void init();
	/// <summary>
	/// Take a screenshot of the game and store it in AppData (does not include text)
	/// </summary>
	/// <param name="w"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="e"></param>
	static void Take_Screenshot(ConsoleWindow w, int width, int height, SYDEScreenshotError& e);
protected:
	static int GetCLSID(const WCHAR* format, CLSID* pClsid);
	static std::wstring s2ws(const std::string& s);
	static std::string getFilePath() { return filepath; }
	static LPCWSTR getTemplatePath() { return template_bmp; }
	static void setFilePath(std::string s) { filepath = s; }
	static void setTemplatePath(LPCWSTR l) { template_bmp = l; }
private:
	static std::string filepath;
	static LPCWSTR template_bmp;
};