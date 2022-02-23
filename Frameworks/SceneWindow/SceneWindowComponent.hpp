#pragma once

struct SceneWindowComponent
    : public WindowComponent
{
    using This = SceneWindowComponent;
    using Super = WindowComponent;
    ECS::SceneSystem Scene = {};

    virtual ~SceneWindowComponent() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Scene"] & Scene;
    }
    virtual void Load(Core::Application & Application);
    virtual void Unload(Core::Application & Application);
    virtual void Update(Core::Application & Application);
    virtual void PreDraw();

    void Initialize()
    {
        Super::Initialize();
    }
};
