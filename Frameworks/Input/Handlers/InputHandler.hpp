#pragma once

struct InputHandler
{
    using This = InputHandler;

    virtual ~InputHandler() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual bool/*Handled*/ OnTouchDown(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnTouchMove(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnTouchUp(EScene & Scene, const TouchInput & Input, bool Intersected);
    virtual bool/*Handled*/ OnKeyDown(EScene & Scene, const KeyboardInput & Input);
    virtual bool/*Handled*/ OnKeyUp(EScene & Scene, const KeyboardInput & Input);

    void Initialize()
    {
    }
};
