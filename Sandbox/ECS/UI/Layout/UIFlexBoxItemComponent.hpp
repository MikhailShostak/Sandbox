#pragma once

namespace ECS
{
struct UIFlexBoxItemComponent
{
    using This = UIFlexBoxItemComponent;
    size_t Alignment;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
