#pragma once

#include <filesystem>

namespace System
{

using Path = std::filesystem::path;
using Directory = std::filesystem::directory_entry;
using DirectoryIterator = std::filesystem::recursive_directory_iterator;
using RecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;

}
