#pragma once

namespace Core
{
struct ApplicationComponent
{
    using This = ApplicationComponent;
    bool Enabled = {};

    virtual ~ApplicationComponent() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Enabled"] & Enabled;
    }
    virtual void Load(Core::Application & Application);
    virtual void Unload(Core::Application & Application);
    virtual void Update(Core::Application & Application);

    void Initialize()
    {
    }
};
}
