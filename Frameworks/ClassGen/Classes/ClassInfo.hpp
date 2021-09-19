#pragma once

namespace ClassGen
{
struct ClassInfo
    : public ClassGen::BaseInfo
{
    using This = ClassInfo;
    using Super = ClassGen::BaseInfo;
    ClassGen::TypeInfo BaseType;
    std::vector<ClassGen::TypeInfo> Interfaces;
    std::vector<std::string> Attributes;
    std::vector<ClassGen::PropertyInfo> Properties;

    virtual ~ClassInfo() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["BaseType"] & BaseType;
        data["Interfaces"] & Interfaces;
        data["Attributes"] & Attributes;
        data["Properties"] & Properties;
    }
};
}
