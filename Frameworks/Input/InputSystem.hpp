#pragma once

namespace ECS
{
struct InputSystem
    : public ECS::System
{
    using This = InputSystem;
    using Super = ECS::System;

    virtual ~InputSystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual bool/*Handled*/ OnTouchDown(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchMove(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchUp(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouch(const TouchInput & Input);
    virtual bool/*Handled*/ OnWheelMove(const WheelInput & Input);
    virtual bool/*Handled*/ OnKeyDown(const KeyboardInput & Input);
    virtual bool/*Handled*/ OnKeyUp(const KeyboardInput & Input);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
