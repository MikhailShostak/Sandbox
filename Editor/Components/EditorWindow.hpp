#pragma once

struct EditorWindow
    : public WindowComponent
{
    using This = EditorWindow;
    using Super = WindowComponent;
    SharedReference<System::ConfigFile<EditorConfig>> Config = {};

    virtual ~EditorWindow() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Config"] & Config;
    }
    virtual void Load(Core::Application & Application);
    virtual void Unload(Core::Application & Application);
    virtual void CreateUI();
    virtual void Draw();

    void Initialize()
    {
        Super::Initialize();
    }
};
