#include "ClassGenEditor.hpp"

#include "../Views/Views.hpp"
#include "../Data/Workspace.hpp"

namespace DefaultExtensions
{

void ClassGenEditor::ResetIndex()
{
    g_Editors.clear();
    g_ClassGenCache.clear();
    g_FunctionCache.clear();
}

void ClassGenEditor::IndexFile(const System::Path &path)
{
    if (path.extension() != ".cg")
    {
        return;
    }

    String pathString = path.generic_string();
    auto it = g_ClassGenCache.find(pathString);
    if(it != g_ClassGenCache.end())
    {
        fmt::print("Class {} already exists\n", pathString);
        return;
    }

    auto [fileInfo] = g_ExtensionLibrary.LoadFile(path);
}

void ClassGenEditor::RenderFile(const System::Path &path)
{
    auto& fileInfo = g_ClassGenCache[path.generic_string()];
    if (fileInfo.Path.empty())
    {
        fileInfo.Path = path;
    }
    auto& editor = g_Editors[path.generic_string()];
    
    if (ImGui::InputText("Type", &fileInfo.Type))
    {
        editor.reset();
        MarkFileDirty(path);
    }

    //TODO: move this to generic file context menu
    ImGui::SameLine();
    if (ImGui::Button("Reload"))
    {
        auto [f] = g_ExtensionLibrary.LoadFile(path);
        fileInfo = std::move(f);
        editor.reset();
        UnsavedFiles.erase(path.generic_string());
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset"))
    {
        g_ExtensionLibrary.LoadData(fileInfo, {});
        if (editor)
        {
            editor->Data = fileInfo;
        }
        MarkFileDirty(path);
    }

    ImGui::SameLine();
    if (ImGui::Button("Compile"))
    {
        ClassGen::Compile(fileInfo);
    }

    if (!editor)
    {
        auto it = g_ExtensionLibrary.FileEditors.find(fileInfo.Type);
        if (it == g_ExtensionLibrary.FileEditors.end())
        {
            return;
        }

        Serialization::Data data;
        data.FromFile(path);
        g_ExtensionLibrary.LoadData(fileInfo, data);

        editor = it->second->Create();
        editor->Data = fileInfo;
        editor->Path = path;
        editor->MarkFileDirty = std::bind(&Editor::MarkFileDirty, this, std::placeholders::_1);
    }

    editor->RenderFile();
}

bool ClassGenEditor::SaveFile(const System::Path &source, const System::Path &destination)
{
    auto fileInfo = g_ClassGenCache.at(source.generic_string());
    Serialization::Data data;
    Serialization::Serialize(fileInfo, data);
    Reflection::Serialize(*fileInfo.Instance, data);
    data.ToFile(destination);

    if (source != destination)
    {
        //TODO: rework
        auto [newFileInfo] = g_ExtensionLibrary.LoadFile(destination);
        ClassGen::Compile(newFileInfo);
        g_ExtensionLibrary.Navigate(newFileInfo);
    }
    else
    {
        ClassGen::Compile(fileInfo);
    }

    return true;
}

}
