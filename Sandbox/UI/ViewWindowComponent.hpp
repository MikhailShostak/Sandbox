#pragma once

namespace UI
{
struct ViewWindowComponent
    : public WindowComponent
{
    using This = ViewWindowComponent;
    using Super = WindowComponent;
    Array<SharedReference<UI::BaseView>> Views = {};

    virtual ~ViewWindowComponent() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Views"] & Views;
    }
    virtual void Draw();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
