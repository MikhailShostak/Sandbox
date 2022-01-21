#pragma once

namespace UI
{
struct DemoView
    : public UI::BaseView
{
    using This = DemoView;
    using Super = UI::BaseView;

    virtual ~DemoView() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
