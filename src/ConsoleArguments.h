#pragma once

#include <string>
#include <stdexcept>
#include <cstddef>

struct ConsoleArguments
{
	std::string sourcePath;
	std::string destinationPath;
};

inline ConsoleArguments ParseConsoleArguments(std::size_t argc, char** argv)
{
	if (argc > 3)
	{
		throw std::runtime_error("Too many command line arguments provided.");
	}
	if (argc < 3)
	{
		throw std::runtime_error("Too few command line arguments provided.");
	}

	return ConsoleArguments{ argv[1], argv[2] };
}
