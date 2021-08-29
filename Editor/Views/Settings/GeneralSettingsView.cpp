#include "../Views.hpp"

#include "../../Data/Config.hpp"

namespace Settings
{

void ShowGeneralSettings()
{
    std::string externalTextEditor;
    auto config = GeneralConfig();
    if(config["ExternalTextEditor"].IsDefined())
    {
        externalTextEditor = config["ExternalTextEditor"].as<std::string>();
    }
    if (ImGui::InputText("External Text Editor", &externalTextEditor, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        config["ExternalTextEditor"] = externalTextEditor;
    }
}

}
