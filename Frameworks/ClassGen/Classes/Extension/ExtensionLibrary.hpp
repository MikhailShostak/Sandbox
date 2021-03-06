#pragma once

namespace ClassGen
{
struct ExtensionLibrary
{
    using This = ExtensionLibrary;
    Map<String, ClassReference<ClassGen::PropertyEditor>> PropertyTypeEditors = {};
    Map<String, ClassReference<ClassGen::PropertyEditor>> PropertyInstanceEditors = {};
    Map<String, ClassReference<ClassGen::FileEditor>> FileEditors = {};
    Map<String, ClassReference<ClassGen::BaseInfo>> Types = {};
    Map<String, ClassReference<ClassGen::Compiler>> Compilers = {};

    virtual ~ExtensionLibrary() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    Meta::Function<void, const ClassGen::FileInfo & /*TypeName*/> Navigate;
    virtual std::tuple<ClassGen::FileInfo/*FileInfo*/> LoadFile(const System::Path & Path);
    virtual std::tuple<bool/*Success*/> LoadData(ClassGen::FileInfo & FileInfo, const Serialization::Data & Data);
    virtual std::tuple<UniqueReference<ClassGen::PropertyEditor>/*Editor*/> FindEditor(const ClassGen::TypeInfo & Type);

    void Initialize()
    {
    }
};
}
