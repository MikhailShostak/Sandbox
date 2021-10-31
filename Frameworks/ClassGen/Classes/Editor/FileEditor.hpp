#pragma once

namespace ClassGen
{
struct FileEditor
{
    using This = FileEditor;
    ClassGen::FileInfo Data;
    System::Path Path;
    Meta::Function<void, System::Path> MarkFileDirty;

    virtual ~FileEditor() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();
};
}
