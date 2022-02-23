#pragma once

namespace ECS
{
struct InputComponent
    : public ECS::EntityComponent
{
    using This = InputComponent;
    using Super = ECS::EntityComponent;
    Array<UniqueReference<InputHandler>> Handlers = {};
    InputComponent() = default;
    InputComponent(const InputComponent &other) = delete;
    InputComponent &operator =(const InputComponent &other) = delete;
    InputComponent(InputComponent &&other) = default;
    InputComponent &operator =(InputComponent &&other) = default;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Handlers"] & Handlers;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
