#include "main.hpp"

Sandbox::Sandbox()
{

}

Sandbox::~Sandbox()
{

}

bool Sandbox::PreInit()
{
    MainWindowTitle = "Sandbox";
    return true;
}

bool Sandbox::Init()
{
    return true;
}

void Sandbox::Update(float dt)
{

}

void Sandbox::UpdateUI(float dt)
{
    ImGui::ShowDemoWindow();
}

void Sandbox::Draw()
{

}

DEFINE_MAIN_APPLICATION(Sandbox)
