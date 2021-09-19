#pragma once

namespace ClassGen
{
struct FileInfo
{
    using This = FileInfo;
    std::string Type;
    std::shared_ptr<ClassGen::BaseInfo> Instance;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
    }
};
}
