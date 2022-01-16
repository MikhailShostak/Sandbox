#include "../Views.hpp"

#include "../../Data/Config.hpp"
#include "../../Data/Workspace.hpp"
#include "../Views.hpp"

namespace View
{

auto DefaultTreeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
auto DefaultTreeLeafFlags = DefaultTreeNodeFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

static std::filesystem::path PreviousFile;

void ShowContextMenu(const std::filesystem::path &path, bool root, bool is_directory)
{
    bool RenamePopup = false;
    bool RemovalConfirmPopup = false;
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("New...", nullptr, &File::DisplayNewDialog))
        {
            File::DialogWorkingDirectory = is_directory ? path : path.parent_path();
        }
        ImGui::Separator();
        ImGui::MenuItem("Rename", nullptr, &RenamePopup);
        ImGui::MenuItem("Remove", nullptr, &RemovalConfirmPopup);
        if(root)
        {
            ImGui::Separator();
            if (ImGui::MenuItem("Close"))
            {
                CloseFolder(path, true);
            }
        }
        ImGui::Separator();
        Utils::Menu::ShowDefaultFileOperations(path);
        ImGui::EndPopup();
    }

    auto RenamePopupID = "Rename##RenamePopup " + path.generic_string();
    static std::string newName;
    if(RenamePopup)
    {
        newName = path.filename().generic_string();
        ImGui::OpenPopup(RenamePopupID.data());
    }
    if(ImGui::BeginPopupModal(RenamePopupID.data()))
    {
        ImGui::Text(path.filename().generic_string().data());
        ImGui::InputText("New Name", &newName);
        if(ImGui::Button("Rename"))
        {
            CloseFile(path);
            auto newPath = path.parent_path() / newName;
            std::filesystem::rename(path, newPath);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    auto RemovalConfirmPopupID = "Remove?##RemovalConfirmPopup " + path.generic_string();
    if(RemovalConfirmPopup)
    {
        ImGui::OpenPopup(RemovalConfirmPopupID.data());
    }
    if(ImGui::BeginPopupModal(RemovalConfirmPopupID.data()))
    {
        ImGui::Text("Are you sure you want to delete?");
        ImGui::TextWrapped(path.generic_string().data());
        if(ImGui::Button("Yes"))
        {
            CloseFile(path);
            std::filesystem::remove(path);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if(ImGui::Button("No"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void ShowPath(const std::filesystem::path &path, bool root = false)
{
    bool is_directory = std::filesystem::is_directory(path);
    bool is_file = std::filesystem::is_regular_file(path);

    if (is_file)
    {
        bool needCombine = Config.FileBrowser.CombineFilesWithSameBasename && !PreviousFile.empty() && PreviousFile == path.stem();
        if (needCombine)
        {
            ImGui::SameLine();
            String title = fmt::format("{} {}", ICON_MD_DESCRIPTION, GetFileTitle(path, true));
            if (ImGui::Selectable(title.data(), false, ImGuiSelectableFlags_AllowItemOverlap))
            {
                OpenFile(path, false);
            }
        }
        else
        {
            ImGui::AlignTextToFramePadding();
            String title = fmt::format("{} {}", ICON_MD_DESCRIPTION, GetFileTitle(path, false));
            auto flags = DefaultTreeLeafFlags | (!Config.FileBrowser.CombineFilesWithSameBasename ? ImGuiTreeNodeFlags_SpanFullWidth : 0);
            ImGui::TreeNodeEx(title.data(), flags);
            if (ImGui::IsItemClicked())
            {
                OpenFile(path, false);
            }
        }

        ShowContextMenu(path, root, is_directory);

        PreviousFile = path.stem();
    }
    else if(is_directory)
    {
        auto pos = ImGui::GetCursorPos();
        String title = "       " + path.filename().generic_string();
        auto flags = DefaultTreeNodeFlags | (!Config.FileBrowser.CombineFilesWithSameBasename ? ImGuiTreeNodeFlags_SpanFullWidth : 0);
        auto opened = ImGui::TreeNodeEx(title.data(), flags);
        ShowContextMenu(path, root, is_directory);

        ImGui::SetCursorPos(pos);
        ImGui::TreeAdvanceToLabelPos();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(253, 212, 81)));
        ImGui::Text(ICON_MD_FOLDER);
        ImGui::PopStyleColor();

        if (!opened)
        {
            return;
        }

        PreviousFile.clear();

        Array<System::Path> paths;
        for (const auto &e : std::filesystem::directory_iterator(path))
        {
            paths.push_back(e.path());
        }
        ranges::sort(paths, [](const auto &l, const auto &r) { return std::filesystem::is_directory(l) && !std::filesystem::is_directory(r); });
        for (const auto &p : paths)
        {
            ShowPath(p);
        }

        ImGui::TreePop();
    }
}

void ShowFileBrowser()
{
    if (!DisplayFileBrowser)
    {
        return;
    }

    if (ImGui::Begin("File Browser"))
    {
        auto folders = Config.File.OpenedFolders;
        if (folders.size() == 0)
        {
            if (ImGui::Button("Open Folder"))
            {
                File::DisplayOpenFolderDialog = true;
            }
        }
        else
        {
            for(auto f : folders)
            {
                ShowPath(f, true);
            }
        }
    }
    ImGui::End();
}

}
