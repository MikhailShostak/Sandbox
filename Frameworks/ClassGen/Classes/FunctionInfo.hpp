#pragma once

namespace ClassGen
{
struct FunctionInfo
{
    using This = FunctionInfo;
    std::string Name;
    std::vector<ClassGen::ParameterInfo> InputParameters;
    std::vector<ClassGen::ParameterInfo> OutputParameters;
    std::vector<std::string> ExecutionBranches;

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
