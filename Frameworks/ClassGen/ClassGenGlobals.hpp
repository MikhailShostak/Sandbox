#pragma once

#include "Classes/Extension/ExtensionLibrary.hpp"

inline ClassGen::ExtensionLibrary g_ExtensionLibrary;

inline Map<String, ClassGen::FunctionInfo> g_FunctionCache;
inline SortedMap<String, ClassGen::FileInfo> g_ClassGenCache;

inline Map<String, UniqueReference<ClassGen::FileEditor>> g_Editors;
