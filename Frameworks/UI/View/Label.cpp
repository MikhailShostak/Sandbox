#include "Label.hpp"

namespace Experimental::UI
{

void Label::Draw()
{
    ImGui::PushItemWidth(Size.x);
    ImGui::LabelText(("##" + TextID).data(), Text.data());
    ImGui::PopItemWidth();
}

}
