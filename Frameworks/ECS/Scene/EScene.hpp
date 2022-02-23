#pragma once

struct EScene
{
    using This = EScene;
    ECS::Registry Registry = {};
    Array<UniqueReference<ECS::System>> Systems = {};
    DateTime::SecondRatio DeltaTime;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Systems"] & Systems;
    }

    void Initialize()
    {
    }
};
