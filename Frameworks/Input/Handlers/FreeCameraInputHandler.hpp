#pragma once

struct FreeCameraInputHandler
    : public InputHandler
{
    using This = FreeCameraInputHandler;
    using Super = InputHandler;
    float Speed = {};
    Float2 Sensetivity = {};
    float SprintFactor = {};
    ECS::Entity CurrentCamera = {};
    Int2 LastPosition = {};
    Float2 Velocity = {};
    Float3 Rotation = {};
    bool Captured = {};

    virtual ~FreeCameraInputHandler() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Speed"] & Speed;
        data["Sensetivity"] & Sensetivity;
        data["SprintFactor"] & SprintFactor;
        data["CurrentCamera"] & CurrentCamera;
    }
    virtual bool/*Handled*/ OnTouchDown(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnTouchMove(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnTouchUp(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnKeyDown(EScene & Scene, const KeyboardInput & Input);
    virtual bool/*Handled*/ OnKeyUp(EScene & Scene, const KeyboardInput & Input);

    void Initialize()
    {
        Super::Initialize();
    }
};
