#pragma once

#include "Classes/Extension/ExtensionLibrary.hpp"

inline ClassGen::ExtensionLibrary g_ExtensionLibrary;

inline Map<String, ClassGen::FunctionInfo> g_FunctionCache;
inline SortedMap<String, ClassGen::FileInfo> g_ClassGenCache;

inline Map<String, UniqueReference<ClassGen::FileEditor>> g_Editors;

inline Array<UniqueReference<ClassGen::ExtensionInterface>> g_Extensions;

namespace ClassGen
{

inline void LoadExtensions()
{
    auto extensions = Reflection::FindAll<ClassGen::ExtensionInterface>();
    for (auto& e : extensions)
    {
        auto i = e->Create();
        i->Load(g_ExtensionLibrary);
        g_Extensions.push_back(std::move(i));
    }
}

}
