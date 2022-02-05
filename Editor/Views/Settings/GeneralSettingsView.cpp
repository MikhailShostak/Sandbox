#include "../Views.hpp"

namespace Settings
{

void ShowGeneralSettings()
{
    std::string externalTextEditor = g_Config->Data.General.ExternalTextEditor;
    if (ImGui::InputText("External Text Editor", &externalTextEditor, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        g_Config->Data.General.ExternalTextEditor = externalTextEditor;
    }
}

}
