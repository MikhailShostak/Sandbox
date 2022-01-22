#pragma once

namespace ClassGen
{
struct FileInfo
{
    using This = FileInfo;
    String Type = {};
    System::Path Path = {};
    std::shared_ptr<ClassGen::BaseInfo> Instance = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
    }

    void Initialize()
    {
    }
};
}
