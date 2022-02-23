#pragma once

namespace ECS
{
struct PersistentComponent
    : public ECS::EntityComponent
{
    using This = PersistentComponent;
    using Super = ECS::EntityComponent;
    String Name = {};
    Array<ECS::EntityComponent*> Components = {};

    virtual ~PersistentComponent() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
