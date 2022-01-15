#pragma once

namespace ClassGen
{
struct ExtensionLibrary
{
    using This = ExtensionLibrary;
    Map<String, ClassReference<ClassGen::FileEditor>> FileEditors;
    Map<String, ClassReference<ClassGen::BaseInfo>> Types;
    Map<String, ClassReference<ClassGen::Compiler>> Compilers;

    virtual ~ExtensionLibrary() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<ClassGen::FileInfo/*FileInfo*/> LoadFile(const System::Path & Path);
    virtual std::tuple<bool/*Success*/> LoadData(ClassGen::FileInfo & FileInfo, const Serialization::Data & Data, const System::Path& Path);
};
}
