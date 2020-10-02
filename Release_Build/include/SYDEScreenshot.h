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
	static void init();
	static void Take_Screenshot(ConsoleWindow w, int width, int height, SYDEScreenshotError& e);
protected:
	static int GetCLSID(const WCHAR* format, CLSID* pClsid);
	static std::wstring s2ws(const std::string& s);
private:
	static std::string filepath;
	static LPCWSTR template_bmp;
};