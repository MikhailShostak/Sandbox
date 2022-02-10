#pragma once

namespace Graphics
{
struct Scene
{
    using This = Scene;

    virtual ~Scene() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
}
