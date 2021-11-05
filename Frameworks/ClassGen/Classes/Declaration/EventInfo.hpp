#pragma once

namespace ClassGen
{
struct EventInfo
{
    using This = EventInfo;
    String Name;
    Array<ClassGen::ParameterInfo> InputParameters;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["InputParameters"] & InputParameters;
    }
};
}
