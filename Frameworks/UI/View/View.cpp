#include "View.hpp"

namespace UI
{

void View::Layout()
{

}

void View::PreDraw()
{
    ImGui::SetCursorPos(Position);
}

void View::Draw()
{
    ImGui::BeginChild(TextID.data());
    for (auto &v : Views)
    {
        v->Update();
    }
    ImGui::EndChild();
}

void View::PostDraw()
{
    /*if (g_Debug)
    {
        ImGui::Line(m_TextID, {});
    }*/
}

void View::Update()
{
    Layout();
    PreDraw();
    Draw();
    PostDraw();
}


}
