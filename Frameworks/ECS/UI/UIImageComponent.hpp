#pragma once

namespace ECS
{
struct UIImageComponent
    : public ECS::EntityComponent
{
    using This = UIImageComponent;
    using Super = ECS::EntityComponent;
    SharedReference<Graphics::Texture> Texture = {};

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
