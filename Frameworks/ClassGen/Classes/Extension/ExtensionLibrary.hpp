#pragma once

namespace ClassGen
{
struct ExtensionLibrary
{
    using This = ExtensionLibrary;
    Map<String, ClassReference<ClassGen::FileEditor>> FileEditors;
    Map<String, ClassReference<ClassGen::BaseInfo>> Types;

    virtual ~ExtensionLibrary() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<ClassGen::FileInfo/*FileInfo*/> Load(const System::Path & Path);
};
}
