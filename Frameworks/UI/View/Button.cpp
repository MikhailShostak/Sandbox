#include "Button.hpp"

namespace UI
{

void Button::Draw()
{
    ImGui::Button(Text.data(), Size);
}

}
