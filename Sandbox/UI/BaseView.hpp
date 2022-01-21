#pragma once

namespace UI
{
struct BaseView
{
    using This = BaseView;

    virtual ~BaseView() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();

    void Initialize()
    {
    }
};
}
