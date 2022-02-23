#pragma once

struct TouchInput
    : public MouseInput
{
    using This = TouchInput;
    using Super = MouseInput;
    int Button = {};

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
