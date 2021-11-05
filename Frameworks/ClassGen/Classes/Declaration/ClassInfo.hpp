#pragma once

namespace ClassGen
{
struct ClassInfo
    : public ClassGen::BaseInfo
{
    using This = ClassInfo;
    using Super = ClassGen::BaseInfo;
    ClassGen::TypeInfo BaseType;
    Array<ClassGen::TypeInfo> Interfaces;
    Array<String> Attributes;
    Array<ClassGen::PropertyInfo> Properties;
    Array<ClassGen::FunctionInfo> Functions;
    Array<ClassGen::EventInfo> Events;
    SortedMap<String, ClassGen::GraphInfo> Graphs;

    virtual ~ClassInfo() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["BaseType"] & BaseType;
        data["Interfaces"] & Interfaces;
        data["Attributes"] & Attributes;
        data["Properties"] & Properties;
        data["Functions"] & Functions;
        data["Events"] & Events;
        data["Graphs"] & Graphs;
    }
};
}
