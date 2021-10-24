#include "Label.hpp"

namespace UI
{

void Label::Draw()
{
    ImGui::PushItemWidth(Size.x);
    ImGui::LabelText(("##" + TextID).data(), Text.data());
    ImGui::PopItemWidth();
}

}
