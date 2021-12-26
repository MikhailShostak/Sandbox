#pragma once

namespace Experimental::UI
{
struct TextField
    : public UI::View
{
    using This = TextField;
    using Super = UI::View;
    String Text;

    virtual ~TextField() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Text"] & Text;
    }
    virtual void Draw();
};
}
