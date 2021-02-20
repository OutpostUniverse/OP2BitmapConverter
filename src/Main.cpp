#include "ConsoleArguments.h"
#include "OP2Utility.h"
#include <iostream>
#include <stdexcept>

using namespace OP2Utility;

static const std::string version = "0.0.1";

void ConvertToBitmap(Stream::BidirectionalReader& reader, std::string destination);
void ConvertTilesetsInDirectory(ResourceManager& resourceManager, std::string destination);
void OutputHelp();

int main(int argc, char** argv)
{
	try {
		auto consoleArguments = ParseConsoleArguments(argc, argv);

		ResourceManager resourceManager(XFile::GetDirectory(consoleArguments.sourcePath));

		if (XFile::IsDirectory(consoleArguments.sourcePath)) {
			ConvertTilesetsInDirectory(resourceManager, consoleArguments.destinationPath);
		}
		else {
			auto stream = resourceManager.GetResourceStream(XFile::GetFilename(consoleArguments.sourcePath));
			ConvertTileset(*stream, consoleArguments.destinationPath);
		}
	}
	catch (std::exception& e) {
		std::cout << "An error was encountered. " << e.what() << std::endl << std::endl;

		OutputHelp();
	}

	return 0;
}

void ConvertToBitmap(Stream::BidirectionalReader& reader, std::string destinationPath)
{
	Tileset::ReadTileset(reader).WriteIndexed(destinationPath);
}

void ConvertTilesetsInDirectory(ResourceManager& resourceManager, std::string destinationDirectory)
{
	auto filenames = resourceManager.GetAllFilenamesOfType(".bmp");

	for (const auto& filename : filenames) {
		auto stream = resourceManager.GetResourceStream(filename);
		if (Tileset::PeekIsCustomTileset(*stream)) {
			ConvertToBitmap(*stream, XFile::Append(destinationDirectory, filename));
		}
	}
}

void OutputHelp()
{
	std::cout << std::endl;
	std::cout << "OP2BitmapConverter Ver " << version << std::endl;
	std::cout << "Developed by Hooman and Brett208 (Vagabond)" << std::endl;
	std::cout << std::endl;
	std::cout << "Convert bitmaps (bmps) from the Outpost 2 specific format into a standardized bitmap format." << std::endl;
	std::cout << "Typically used to convert the wells (tilesets). After conversion the bitmaps may be" << std::endl;
	std::cout << "rendered or edited by standard bitmap editing software such as Gimp or Microsoft Paint." << std::endl;
	std::cout << std::endl;
	std::cout << "+++ COMMAND SYNTAX +++" << std::endl;
	std::cout << "  * OP2BitmapConvert inputFile.bmp outputFile.bmp [-H] [-Q] [-O] [-A]" << std::endl;
	std::cout << std::endl;
	std::cout << "+++ EXAMPLE COMMANDS +++" << std::endl;
	std::cout << "  * OPBitmapConvert well0002.bmp converted/ReadeableWell0002.bmp" << std::endl;
	std::cout << "  * OPBitmapConvert -O --Quiet well0002.bmp converted/ReadeableWell0002.bmp" << std::endl;
	std::cout << std::endl;
	std::cout << "+++ OPTIONAL ARGUMENTS +++" << std::endl;
	std::cout << "  -H / --Help / -?: Displays help information." << std::endl;
	std::cout << "  -Q / --Quiet: [Default false] Add switch to run application without issuing console messages." << std::endl;
	std::cout << "  -O / --Overwrite: [Default false] Add switch to allow application to overwrite existing files." << std::endl;
	std::cout << "  -A / --AccessArchives [Default true]. Add switch to disable searching VOL archives for well files." << std::endl;
	std::cout << std::endl;
	std::cout << "For more information about Outpost 2 visit the Outpost Universe (http://outpost2.net/)." << std::endl;
	std::cout << std::endl;
}
