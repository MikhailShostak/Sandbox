#pragma once

#include <filesystem>

namespace OS
{

namespace FS
{
	using Path = std::filesystem::path;
	using Directory = std::filesystem::directory_entry;
	using Iterator = std::filesystem::recursive_directory_iterator;
	using RecursiveIterator = std::filesystem::recursive_directory_iterator;

	using namespace std::filesystem;
}

}
