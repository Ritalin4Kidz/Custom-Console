#include "pch.h"
#include "SYDEScreenshot.h"
std::string SYDEScreenshot::filepath = "";
LPCWSTR SYDEScreenshot::template_bmp = L"EngineFiles\\Bitmaps\\SSTemplate.bmp";
void SYDEScreenshot::init()
{
	std::string file1 = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine");
	std::wstring stemp1 = s2ws(file1);
	LPCWSTR r1 = stemp1.c_str();
	if (CreateDirectory(r1, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}
	std::string file2 = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine\\Screenshots");
	std::wstring stemp2 = s2ws(file2);
	LPCWSTR r2 = stemp2.c_str();
	if (CreateDirectory(r2, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}
	filepath = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine\\Screenshots");
}

int SYDEScreenshot::GetCLSID(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}

void SYDEScreenshot::Take_Screenshot(ConsoleWindow w, int width, int height, SYDEScreenshotError& e)
{
	try {
		HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), template_bmp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		Bitmap* image = new Bitmap(hBitmap, NULL);

		for (int l = 0, i = 0; l < width; l += 2, i++)
		{
			for (int m = 0; m < height; m++)
			{
				Gdiplus::Color pixelColor;
				//ColourClass c = w.get_BG_Colour_At_Point_Only(Vector2(l, m));
				ColourClass c = w.determineColourAtPoint(Vector2(l, m), BLACK, true);
				std::vector<std::string> rgb_s_arr = AssetsClass::ColourToRGBStrArray(c);
				byte a{ 255 };
				byte r{ static_cast<byte>(std::stoi(rgb_s_arr[0])) };
				byte g{ static_cast<byte>(std::stoi(rgb_s_arr[1])) };
				byte b{ static_cast<byte>(std::stoi(rgb_s_arr[2])) };
				pixelColor.SetValue(pixelColor.MakeARGB(a, r, g, b));
				image->SetPixel(i, m, pixelColor);
			}
		}
		CLSID clsID;
		time_t now = time(0);
		char* dt = ctime(&now);
		std::string temp = "\\" + std::string(dt);
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
		temp.erase(remove(temp.begin(), temp.end(), ':'), temp.end());
		temp = temp.substr(0, temp.length() - 1);
		temp += ".png";
		std::wstring stemp = s2ws(filepath + temp);
		LPCWSTR result = stemp.c_str();
		int retVal = GetCLSID(L"image/png", &clsID);
		image->Save(result, &clsID, NULL);
		delete image;
		e = SCREENSHOT_SUCCESS;
	}
	catch (std::exception ex)
	{
		e = SCREENSHOT_ERROR;
	}
}

std::wstring SYDEScreenshot::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
