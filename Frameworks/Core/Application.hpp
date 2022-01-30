#pragma once

namespace Core
{
struct Application
{
    using This = Application;
    Array<UniqueReference<Core::ApplicationComponent>> Components = {};
    bool Running = {};
    int ErrorCode = {};

    virtual ~Application() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Components"] & Components;
    }
    virtual int/*Result*/ Run();

    void Initialize()
    {
    }
};
}
