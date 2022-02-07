#pragma once

namespace ECS
{
struct RootComponent
{
    using This = RootComponent;
    bool unused = false;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
