#include "../Views.hpp"

#include "../../Data/Workspace.hpp"

namespace File
{

void ShowNewDialog()
{
    if (!File::DisplayNewDialog)
    {
        return;
    }

    File::DisplayNewDialog = false;
    
    auto path = System::Dialogs::SaveFile("New File", g_Config->Data.CreateFilters(), File::DialogWorkingDirectory);

    if (!path.empty())
    {
        std::fstream f;
        f.open(path, std::ios::binary | std::ios::out);
    }
}


void ShowOpenFileDialog()
{
    if (!File::DisplayOpenFileDialog)
    {
        return;
    }

    File::DisplayOpenFileDialog = false;

    auto path = System::Dialogs::OpenFile("Open File", g_Config->Data.CreateFilters(), File::DialogWorkingDirectory);

    if (!path.empty())
    {
        OpenFile(path);
    }
}

void ShowOpenFolderDialog()
{
    if (!File::DisplayOpenFolderDialog)
    {
        return;
    }

    File::DisplayOpenFolderDialog = false;

    auto path = System::Dialogs::SelectFolder("Open Folder", File::DialogWorkingDirectory);
    if (!path.empty())
    {
        OpenFolder(path);
    }
}

void ShowSaveAsDialog()
{
    if (!File::DisplaySaveAsDialog)
    {
        return;
    }

    File::DisplaySaveAsDialog = false;

    auto path = System::Dialogs::SaveFile("Save As", g_Config->Data.CreateFilters(), FileToSave);
    if (!path.empty())
    {
        SaveFile(FileToSave, path);
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
