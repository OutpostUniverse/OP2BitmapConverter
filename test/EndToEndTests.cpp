#include "../OP2Utility/include/OP2Utility.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

using namespace OP2Utility;

// Filename of a .txt file containing the fully qualified path of the application under test (as it was just compiled)
const std::string documentFilenameContainingApplicationUnderTestFilename("ApplicationPath.txt");
std::string getApplicationName();

TEST(EndToEnd, ImageConversion)
{
	const auto applicationName = getApplicationName();

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

std::string getApplicationName()
{
	std::ifstream file(documentFilenameContainingApplicationUnderTestFilename);
	std::string applicationName;
	std::getline(file, applicationName);

	return applicationName;
}
