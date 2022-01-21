#pragma once

namespace ClassGen
{
struct FileEditor
{
    using This = FileEditor;
    ClassGen::FileInfo Data = {};
    System::Path Path = {};
    Map<String, UniqueReference<ClassGen::PropertyEditor>> PropertyEditors = {};

    virtual ~FileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    Meta::Function<void, const System::Path & /*FilePath*/> MarkFileDirty;
    virtual void RenderFile();

    void Initialize()
    {
    }
};
}
