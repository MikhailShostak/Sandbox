#include "ExtensionLibrary.hpp"

namespace ClassGen
{

std::tuple<ClassGen::FileInfo/*FileInfo*/> ExtensionLibrary::Load(const System::Path &Path)
{
    Serialization::Data data;
    data.FromFile(Path);

    auto fileInfo = Serialization::Deserialize<ClassGen::FileInfo>(data);

    if (fileInfo.Type.empty())
    {
        fmt::print("[Warning] {}: ClassGen type is undefined\n", Path);
        return { fileInfo };
    }

    auto it = g_ExtensionLibrary.Types.find(fileInfo.Type);
    if (it == g_ExtensionLibrary.Types.end())
    {
        fmt::print("[Warning] {}: ClassGen type \"{}\" is not found\n", Path, fileInfo.Type);
        return { fileInfo };
    }

    fileInfo.Instance = SharedReference<ClassGen::BaseInfo>{ it->second->Create().release() };
    Reflection::Deserialize(data, *fileInfo.Instance);

    g_ClassGenCache.insert({ Path.generic_string(), fileInfo });

    return { fileInfo };
}

}
