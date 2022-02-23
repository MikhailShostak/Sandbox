#pragma once

struct KeyboardInput
{
    using This = KeyboardInput;
    int Key = {};
    int Char = {};

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
