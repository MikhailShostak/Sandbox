#include "Button.hpp"

namespace Experimental::UI
{

void Button::Draw()
{
    ImGui::Button(Text.data(), Size);
}

}
