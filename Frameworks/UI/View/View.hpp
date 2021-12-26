#pragma once

namespace Experimental::UI
{
struct View
{
    using This = View;
    String TextID = fmt::format("{}", fmt::ptr(this));;
    ImVec2 Position = { 0, 0 };
    ImVec2 Size = { 0, 0 };
    Array<SharedReference<UI::View>> Views;

    virtual ~View() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Position"] & Position;
        data["Size"] & Size;
    }
    virtual void Layout();
    virtual void PreDraw();
    virtual void Draw();
    virtual void PostDraw();
    virtual void Update();
};
}
