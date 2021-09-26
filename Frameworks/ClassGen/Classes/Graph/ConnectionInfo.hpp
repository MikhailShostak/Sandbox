#pragma once

namespace ClassGen
{
struct ConnectionInfo
{
    using This = ConnectionInfo;
    std::filesystem::path Source;
    std::filesystem::path Destination;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Source"] & Source;
        data["Destination"] & Destination;
    }
};
}
