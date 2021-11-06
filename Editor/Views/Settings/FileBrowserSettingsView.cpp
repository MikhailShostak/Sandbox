#include "../Views.hpp"

#include "../../Data/Config.hpp"

namespace Settings
{

void ShowFileBrowserSettings()
{
    ImGui::Checkbox("Combine files with the same basename", &Config.FileBrowser.CombineFilesWithSameBasename);
}

}
