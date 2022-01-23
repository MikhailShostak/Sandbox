#pragma once

namespace ClassGen
{
struct ClassInfo
    : public ClassGen::BaseInfo
{
    using This = ClassInfo;
    using Super = ClassGen::BaseInfo;
    ClassGen::TypeInfo BaseType = {};
    Array<ClassGen::TypeInfo> Interfaces = {};
    Array<String> Attributes = {};
    Array<String> TemplateTypes = {};
    ClassGen::TypeInfo IndirectType = {};
    Array<ClassGen::PropertyInfo> Properties = {};
    Array<ClassGen::FunctionInfo> Functions = {};
    Array<ClassGen::EventInfo> Events = {};
    SortedMap<String, ClassGen::GraphInfo> Graphs = {};
    SortedMap<String, Serialization::Data> Values = {};

    virtual ~ClassInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["BaseType"] & BaseType;
        data["Interfaces"] & Interfaces;
        data["Attributes"] & Attributes;
        data["TemplateTypes"] & TemplateTypes;
        data["IndirectType"] & IndirectType;
        data["Properties"] & Properties;
        data["Functions"] & Functions;
        data["Events"] & Events;
        data["Graphs"] & Graphs;
        data["Values"] & Values;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
