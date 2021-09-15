#include "../Views.hpp"

#include "../../Data/Config.hpp"

namespace Settings
{

void ShowGeneralSettings()
{
    std::string externalTextEditor = Config.General.ExternalTextEditor;    
    if (ImGui::InputText("External Text Editor", &externalTextEditor, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        Config.General.ExternalTextEditor = externalTextEditor;
    }
}

}
