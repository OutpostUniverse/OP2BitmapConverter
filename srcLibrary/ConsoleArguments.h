#pragma once

#include <string>

struct ConsoleArguments
{
	std::string sourcePath;
	std::string destinationPath;
};

ConsoleArguments ParseConsoleArguments(int argc, char** argv);
