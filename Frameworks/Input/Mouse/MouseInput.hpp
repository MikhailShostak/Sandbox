#pragma once

struct MouseInput
{
    using This = MouseInput;
    Int2 Position = {};

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
