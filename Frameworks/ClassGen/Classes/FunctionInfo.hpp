#pragma once

namespace ClassGen
{
struct FunctionInfo
{
    using This = FunctionInfo;
    String Name;
    Array<ClassGen::ParameterInfo> InputParameters;
    Array<ClassGen::ParameterInfo> OutputParameters;
    Array<String> ExecutionBranches;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["InputParameters"] & InputParameters;
        data["OutputParameters"] & OutputParameters;
        data["ExecutionBranches"] & ExecutionBranches;
    }
};
}
