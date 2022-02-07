#pragma once

namespace ECS
{
struct UITextComponent
{
    using This = UITextComponent;
    String Text;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Text"] & Text;
    }
};
}
