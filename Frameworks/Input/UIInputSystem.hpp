#pragma once

namespace ECS
{
struct UIInputSystem
    : public ECS::InputSystem
{
    using This = UIInputSystem;
    using Super = ECS::InputSystem;
    EScene* m_Scene = {};

    virtual ~UIInputSystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual bool/*Handled*/ OnTouchDown(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchMove(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchUp(const TouchInput & Input);
    virtual bool/*Handled*/ OnKeyDown(const KeyboardInput & Input);
    virtual bool/*Handled*/ OnKeyUp(const KeyboardInput & Input);
    virtual void OnUpdate(EScene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
