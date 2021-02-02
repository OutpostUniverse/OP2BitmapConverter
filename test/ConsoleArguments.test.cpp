#include "../src/ConsoleArguments.h"
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <array>

char* SampleApplicationPath("C:/SampleFolder/SampleApplication.exe");

TEST(ConsoleArguments, ArgumentCount)
{
	{ // Proper argument count
		std::array<char*, 3> consoleInput{ SampleApplicationPath, "First Argument", "Second Argument"};
		auto arguments = ParseConsoleArguments(consoleInput.size(), consoleInput.data());
		EXPECT_EQ(consoleInput[1], arguments.sourcePath);
		EXPECT_EQ(consoleInput[2], arguments.destinationPath);
	}
	{ // Too few arguments
		std::array<char*, 2> consoleInput{ SampleApplicationPath, "First Argument" };
		EXPECT_THROW(ParseConsoleArguments(consoleInput.size(), consoleInput.data()), std::runtime_error);
	}
	{ // Too many arguments
		std::array<char*, 4> consoleInput{ SampleApplicationPath, "First Argument", "Second Argument", "Third Argument" };
		EXPECT_THROW(ParseConsoleArguments(consoleInput.size(), consoleInput.data()), std::runtime_error);
	}
}
