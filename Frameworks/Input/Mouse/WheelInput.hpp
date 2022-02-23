#pragma once

struct WheelInput
    : public MouseInput
{
    using This = WheelInput;
    using Super = MouseInput;
    int Delta = {};

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
