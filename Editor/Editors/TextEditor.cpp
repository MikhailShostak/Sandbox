#include "TextEditor.hpp"

#include <TextEditor.h>
#include "../Data/Workspace.hpp"

namespace DefaultExtensions
{

::TextEditor InternalEditor;

void TextEditor::RenderFile(const std::filesystem::path &path)
{
    static std::filesystem::path current_file;
    if(current_file != path)
    {
        InternalEditor.SetText(FileCache[path.generic_string()]);
        current_file = path;
    }
    auto cpos = InternalEditor.GetCursorPosition();
    /*ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                editor.IsOverwrite() ? "Ovr" : "Ins",
                editor.CanUndo() ? "*" : " ",
                editor.GetLanguageDefinition().mName.c_str(), f.string());*/
    InternalEditor.Render("TextEditor");

    if (InternalEditor.IsTextChanged())
    {
        FileCache[path.generic_string()] = InternalEditor.GetText();
        MarkFileDirty(path);
    }
}

}
