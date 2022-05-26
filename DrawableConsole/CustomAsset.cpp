#include "pch.h"
#include "CustomAsset.h"
std::string CustomAsset::filepath = "";
LPCWSTR CustomAsset::template_bmp = L"EngineFiles\\Bitmaps\\ExportTemplate.bmp";
void CustomAsset::operator=(CustomAsset other)
{
	this->AssetVector = other.AssetVector;
}

ConsoleWindow CustomAsset::draw_asset(ConsoleWindow window, Vector2 point)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii + point.getX(), i + point.getY()), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}
	return window;
}

ConsoleWindow CustomAsset::draw_asset(ConsoleWindow window, Vector2 point, int windowWidth, int windowHeight)
{
	int startPointY = point.getY();
	int startPointX = point.getX();
	int StartJ = 0;
	int StartJJ = 0;
	if (startPointY < 0)
	{
		StartJ = -startPointY;
		startPointY = 0;
	}
	if (startPointX < 0)
	{
		StartJJ = -startPointX;
		startPointX = 0;
	}
	for (int i = startPointY, j  = StartJ ; i < windowHeight + point.getY() && i < AssetVector.size(); i++, j++)
	{
		for (int ii = startPointX, jj = StartJJ; ii < windowWidth + point.getX() && ii < AssetVector[i].size(); ii++, jj++)
		{
			window.setTextAtPoint(Vector2(jj, j), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}
	return window;
}

void CustomAsset::setAsset(int width, int height, vector<ColourClass> colourClassArray)
{
	int j = 0;
	vector<vector<TextItem>> temp_temp;
	for (int i = 0; i < height; i++)
	{
		vector<TextItem> temp;
		for (int ii = 0; ii < width; ii++)
		{
			temp.push_back(TextItem(' ', colourClassArray[j]));
			j++;
		}
		temp_temp.push_back(temp);
	}
	AssetVector = temp_temp;
}

void CustomAsset::AddAssetOnto(CustomAsset other, Vector2 point)
{
	for (int i = 0; i < other.AssetVector.size(); i++)
	{
		for (int ii = 0; ii < other.AssetVector[i].size(); ii++)
		{
			setCharAtPoint(Vector2(point.getX() + ii, point.getY() + i), other.AssetVector[i][ii].getChar());
			setColourAtPoint(Vector2(point.getX() + ii, point.getY() + i), other.AssetVector[i][ii].getColour());
		}
	}
}

void CustomAsset::setCharAtPoint(Vector2 Point, char m_Text)
{
	AssetVector[Point.getY()][Point.getX()].setChar(m_Text);
}

void CustomAsset::setColourAtPoint(Vector2 Point, int m_Colour)
{
	AssetVector[Point.getY()][Point.getX()].setColour(m_Colour);
}

void CustomAsset::changeAllInstancesOfColour(ColourClass oldColour, ColourClass newColour)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			if (AssetVector[i][ii].getColour() == oldColour)
			{
				AssetVector[i][ii].setColour(newColour);
			}
		}
	}
}

int CustomAsset::changeAllInstancesOfColour(ColourClass oldColour, ColourClass newColour, char newChar)
{
	int instances = 0;
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			if (AssetVector[i][ii].getColour() == oldColour)
			{
				AssetVector[i][ii].setColour(newColour);
				AssetVector[i][ii].setChar(newChar);
				instances++;
			}
		}
	}
	return instances;
}

char CustomAsset::getCharAtPoint(Vector2 Point)
{
	return AssetVector[Point.getY()][Point.getX()].getChar();
}

int CustomAsset::getColourAtPoint(Vector2 Point)
{
	if (Point.getX() < 0 || Point.getY() < 0)
	{
		return NULLCOLOUR;
	}
	return AssetVector[Point.getY()][Point.getX()].getColour();
}

void CustomAsset::ExportAssetToFile()
{
	std::string file1 = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine");
	std::wstring stemp1 = s2ws(file1);
	LPCWSTR r1 = stemp1.c_str();
	if (CreateDirectory(r1, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}
	std::string file2 = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine\\Exports");
	std::wstring stemp2 = s2ws(file2);
	LPCWSTR r2 = stemp2.c_str();
	if (CreateDirectory(r2, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}
	filepath = std::string(getenv("APPDATA")) + std::string("\\SYDEEngine\\Exports");
	try {
		HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), template_bmp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		Bitmap* image = new Bitmap(hBitmap, NULL);

		for (int l = 0; l < AssetVector.size(); l++)
		{
			for (int m = 0; m < AssetVector[l].size(); m++)
			{
				Gdiplus::Color pixelColor;
				//ColourClass c = w.get_BG_Colour_At_Point_Only(Vector2(l, m));
				ColourClass c = static_cast<ColourClass>(AssetVector[l][m].getColour());
				std::vector<std::string> rgb_s_arr = AssetsClass::ColourToRGBStrArray(c);
				byte a{ 255 };
				byte r{ static_cast<byte>(std::stoi(rgb_s_arr[0])) };
				byte g{ static_cast<byte>(std::stoi(rgb_s_arr[1])) };
				byte b{ static_cast<byte>(std::stoi(rgb_s_arr[2])) };
				pixelColor.SetValue(pixelColor.MakeARGB(a, r, g, b));
				image->SetPixel(l, m, pixelColor);
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
		//e = SCREENSHOT_SUCCESS;
	}
	catch (std::exception ex)
	{
		//e = SCREENSHOT_ERROR;
	}
}

Vector2 CustomAsset::returnPointOfFirstInstance(ColourClass a_Colour)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			if (AssetVector[i][ii].getColour() == a_Colour)
			{
				return Vector2(ii, i);
			}
		}
	}
	return Vector2(0, 0);
}

int CustomAsset::GetCLSID(const WCHAR* format, CLSID* pClsid)
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

std::wstring CustomAsset::s2ws(const std::string& s)
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
