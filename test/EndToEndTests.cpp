#include "../OP2Utility/include/OP2Utility.h"
#include <gtest/gtest.h>
#include <string>

using namespace OP2Utility;

std::string getMsvcExeDirectory();

TEST(EndToEnd, ImageConversion)
{

#ifdef _WIN32
	const std::string applicationName = getMsvcExeDirectory() + "OP2BitmapConverter.exe";
#else // Linux makefile
	const std::string applicationName = "";
#endif

	const std::string startingTilesetFilename("TilesetTest.bmp");
	const std::string customTilesetFilename("CustomTilesetTest.bmp");
	const std::string standardTilesetFilename("StandardTilesetTest.bmp");

	// Convert standard 8-bit bitmap into custom tileset format
	std::system((applicationName + " " + startingTilesetFilename + " " + customTilesetFilename).c_str());
	
	// Convert custom tileset format back into custom 8-bit bitmap
	std::system((applicationName + " " + customTilesetFilename + " " + standardTilesetFilename).c_str());


	auto bitmap1 = Tileset::ReadTileset(Stream::FileReader(startingTilesetFilename));
	auto bitmap2 = Tileset::ReadTileset(Stream::FileReader(standardTilesetFilename));

	ASSERT_EQ(bitmap1, bitmap2);
}

// Return the relative directory where OP2BitmapConverter is compiled
std::string getMsvcExeDirectory()
{
#ifdef _WIN64 && _DEBUG
	return "..\\x64\\debug\\";
#elif _WIN64
	return "..\\x64\\release\\"
#elif _DEBUG
	return "..\\debug\\";
#else
	return "..\\release\\";
#endif
}
