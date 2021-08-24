#include "../Views.hpp"

#include <ImGuiFileDialog.h>

#include "../../Data/Workspace.hpp"

namespace File
{

void ShowNewDialog()
{
    if(File::DisplayNewDialog)
    {
        ImGuiFileDialog::Instance()->OpenModal("NewDialog", "Choose File", ".txt", ".");
        File::DisplayNewDialog = false;
    }

    ImGui::SetNextWindowSize({800, 480});
    if (ImGuiFileDialog::Instance()->Display("NewDialog"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}


void ShowOpenFileDialog()
{
    if(File::DisplayOpenFileDialog)
    {
        ImGuiFileDialog::Instance()->OpenModal("OpenFileDialog", "Open File", ".*,.txt", ".");
        File::DisplayOpenFileDialog = false;
    }

    ImGui::SetNextWindowSize({800, 480});
    if (ImGuiFileDialog::Instance()->Display("OpenFileDialog"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path path = ImGuiFileDialog::Instance()->GetFilePathName();
            OpenFile(path);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void ShowOpenFolderDialog()
{
    if(File::DisplayOpenFolderDialog)
    {
        ImGuiFileDialog::Instance()->OpenModal("OpenFolderDialog", "Open Folder", "", ".");
        File::DisplayOpenFolderDialog = false;
    }

    ImGui::SetNextWindowSize({800, 480});
    if (ImGuiFileDialog::Instance()->Display("OpenFolderDialog"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path path = ImGuiFileDialog::Instance()->GetFilePathName();
            OpenFolder(path);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void ShowSaveAsDialog()
{
    if(File::DisplaySaveAsDialog)
    {
        ImGuiFileDialog::Instance()->OpenModal("SaveAsDialog", "Save File", (FileToSave.extension().generic_string() + ",.*").data(), FileToSave.generic_string());
        File::DisplaySaveAsDialog = false;
    }

    ImGui::SetNextWindowSize({800, 480});
    if (ImGuiFileDialog::Instance()->Display("SaveAsDialog"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path path = ImGuiFileDialog::Instance()->GetFilePathName();
            SaveFile(FileToSave, path);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void ProcessDialogs()
{
    ShowNewDialog();
    ShowOpenFileDialog();
    ShowOpenFolderDialog();
    ShowSaveAsDialog();
}

}
