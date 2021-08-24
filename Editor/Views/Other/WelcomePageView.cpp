#include "../Views.hpp"

void ShowWelcomePage()
{
    if(ImGui::Begin("Welcome Page", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoMove))
    {
    }
    ImGui::End();
}
