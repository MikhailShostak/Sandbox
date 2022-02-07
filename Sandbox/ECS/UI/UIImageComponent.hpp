#pragma once

namespace ECS
{
struct UIImageComponent
{
    using This = UIImageComponent;
    SharedReference<Graphics::Texture> Texture;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
