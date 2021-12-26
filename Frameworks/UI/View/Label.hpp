#pragma once

namespace Experimental::UI
{
struct Label
    : public UI::View
{
    using This = Label;
    using Super = UI::View;
    String Text;

    virtual ~Label() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Text"] & Text;
    }
    virtual void Draw();
};
}
