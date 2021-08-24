#include "Editor.hpp"

#include "../Data/Workspace.hpp"

void Editor::MarkFileDirty(const std::filesystem::path &path)
{
    auto it = std::find_if(Editors.begin(), Editors.end(), [&](const auto &v){ return v.second.get() == this; });
    UnsavedFiles[path.generic_string()] = it->second.get();
}
