#pragma once

namespace ECS
{
struct SceneSystem
    : public ECS::InputSystem
{
    using This = SceneSystem;
    using Super = ECS::InputSystem;
    Array<SharedReference<EScene>> Scenes = {};

    virtual ~SceneSystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Scenes"] & Scenes;
    }
    virtual void OnLoad(EScene & Scene);
    virtual void OnUnload(EScene & Scene);
    virtual void OnUpdate(EScene & Scene);
    virtual bool/*Handled*/ OnTouchDown(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchMove(const TouchInput & Input);
    virtual bool/*Handled*/ OnTouchUp(const TouchInput & Input);
    virtual bool/*Handled*/ OnWheelMove(const WheelInput & Input);
    virtual bool/*Handled*/ OnKeyDown(const KeyboardInput & Input);
    virtual bool/*Handled*/ OnKeyUp(const KeyboardInput & Input);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
