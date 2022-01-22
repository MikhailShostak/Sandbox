#include "ExtensionLibrary.hpp"

namespace ClassGen
{

//TODO: remove
void IndexFileData(const System::Path &path, const ClassGen::BaseInfo &baseInfo);

std::tuple<bool/*Success*/> ExtensionLibrary::LoadData(ClassGen::FileInfo& FileInfo, const Serialization::Data& Data)
{
    if (FileInfo.Path.empty())
    {
        fmt::print("[Warning] Path is undefined for data:\n{}\n", Data.ToString());
        return false;
    }

    if (FileInfo.Type.empty())
    {
        fmt::print("[Warning] {}: ClassGen type is undefined\n", FileInfo.Path);
        return false;
    }

    auto it = g_ExtensionLibrary.Types.find(FileInfo.Type);
    if (it == g_ExtensionLibrary.Types.end())
    {
        fmt::print("[Warning] {}: ClassGen type \"{}\" is not found\n", FileInfo.Path, FileInfo.Type);
        return false;
    }

    FileInfo.Instance = SharedReference<ClassGen::BaseInfo>{ it->second->Create().release() };
    Reflection::Deserialize(Data, *FileInfo.Instance);

    g_ClassGenCache[FileInfo.Path.generic_string()] = FileInfo;
    if (FileInfo.Type == "Class")
    {
        IndexFileData(FileInfo.Path, *DynamicCast<ClassGen::ClassInfo>(FileInfo.Instance));
    }
    return true;
}

std::tuple<ClassGen::FileInfo/*FileInfo*/> ExtensionLibrary::LoadFile(const System::Path &Path)
{
    Serialization::Data data;
    data.FromFile(Path);

    auto fileInfo = Serialization::Deserialize<ClassGen::FileInfo>(data);
    fileInfo.Path = Path;
    LoadData(fileInfo, data);

    return { fileInfo };
}

std::tuple<UniqueReference<ClassGen::PropertyEditor>/*Editor*/> ExtensionLibrary::FindEditor(const ClassGen::TypeInfo& Type)
{
    if (auto it = PropertyInstanceEditors.find(writeRecursively(Type));  it != PropertyInstanceEditors.end())
    {
        return { UniqueReference<ClassGen::PropertyEditor>(it->second->Create()) };
    }

    if (!Type.Parameters.empty())
    {
        if (auto it = PropertyInstanceEditors.find(Type.Name);  it != PropertyInstanceEditors.end())
        {
            return { UniqueReference<ClassGen::PropertyEditor>(it->second->Create()) };
        }
    }

    ClassGen::FileInfo propertyFileInfo = FindClassByName(Type.Name);
    if (auto it = PropertyTypeEditors.find(propertyFileInfo.Type); it != PropertyTypeEditors.end())
    {
        return { UniqueReference<ClassGen::PropertyEditor>(it->second->Create()) };
    }

    return { UniqueReference<ClassGen::PropertyEditor>() };
}

}
