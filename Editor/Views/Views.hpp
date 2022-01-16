#pragma once

void ShowRootView(const std::function<void()> &callback);
void ShowMainMenu();
void ShowWelcomePage();

namespace File
{
inline bool DisplayNewDialog = false;
inline bool DisplayOpenFileDialog = false;
inline bool DisplayOpenFolderDialog = false;
inline bool DisplaySaveAsDialog = false;
inline std::filesystem::path DialogWorkingDirectory = ".";
inline std::filesystem::path FileToSave;
void ShowNewDialog();
void ShowOpenFileDialog();
void ShowOpenFolderDialog();
void ShowSaveAsDialog();
void ProcessDialogs();
}

struct SettingsEntry
{
    std::string title;
    std::function<void()> handle;
};

namespace Settings
{

inline bool DisplaySettings = false;
void ShowSettings();
void ShowGeneralSettings();
void ShowFileBrowserSettings();
void ShowEnvironment();
void ShowFileTypes();
void ShowExtensions();

inline std::vector<SettingsEntry> ExtensionSettings;

}

namespace View
{

inline bool DisplayConsole = false;
void ShowConsole();

inline bool DisplayFileBrowser = true;
void ShowFileBrowser();


}

namespace Utils
{

namespace Menu
{
void CopyFullPath(const std::filesystem::path &path);
void ShowInExplorer(const std::filesystem::path &path);
void ShowInExternalTextEditor(const std::filesystem::path &path);
void OpenTerminalHere(const std::filesystem::path &path);
void ShowDefaultFileOperations(const std::filesystem::path &path);
}

}

namespace Debug
{

inline bool DisplayImGuiDemo = false;
inline bool DisplayDebugWindow = false;

void ShowDebugWindow();

}

inline static ImGuiTableFlags DefaultTableFlags =
    ImGuiTableFlags_SizingFixedFit |
    ImGuiTableFlags_RowBg |
    ImGuiTableFlags_Borders |
    ImGuiTableFlags_Resizable |
    ImGuiTableFlags_Hideable;
