#pragma once

namespace Experimental::UI
{
struct Button
    : public UI::View
{
    using This = Button;
    using Super = UI::View;
    String Text;

    virtual ~Button() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Text"] & Text;
    }
    virtual void Draw();
};
}
