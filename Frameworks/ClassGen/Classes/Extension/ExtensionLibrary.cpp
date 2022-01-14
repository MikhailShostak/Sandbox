#include "ExtensionLibrary.hpp"

namespace ClassGen
{

//TODO: remove
void IndexFileData(const System::Path &path, const ClassGen::BaseInfo &baseInfo);

std::tuple<bool/*Success*/> ExtensionLibrary::LoadData(ClassGen::FileInfo& FileInfo, const Serialization::Data& Data, const System::Path& Path)
{
    if (FileInfo.Type.empty())
    {
        fmt::print("[Warning] {}: ClassGen type is undefined\n", Path);
        return false;
    }

    auto it = g_ExtensionLibrary.Types.find(FileInfo.Type);
    if (it == g_ExtensionLibrary.Types.end())
    {
        fmt::print("[Warning] {}: ClassGen type \"{}\" is not found\n", Path, FileInfo.Type);
        return false;
    }

    FileInfo.Instance = SharedReference<ClassGen::BaseInfo>{ it->second->Create().release() };
    Reflection::Deserialize(Data, *FileInfo.Instance);

    g_ClassGenCache[Path.generic_string()] = FileInfo;
    if (FileInfo.Type == "Class")
    {
        IndexFileData(Path, *DynamicCast<ClassGen::ClassInfo>(FileInfo.Instance));
    }
    return true;
}

std::tuple<ClassGen::FileInfo/*FileInfo*/> ExtensionLibrary::LoadFile(const System::Path &Path)
{
    Serialization::Data data;
    data.FromFile(Path);

    auto fileInfo = Serialization::Deserialize<ClassGen::FileInfo>(data);
    LoadData(fileInfo, data, Path);

    return { fileInfo };
}

}
