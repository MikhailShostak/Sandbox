#include "AAssets.h"

#include <unordered_map>

std::unordered_map<std::string, std::pair<const uint8_t *, std::size_t>> &AssetsRepository()
{
    static std::unordered_map<std::string, std::pair<const uint8_t *, std::size_t>> map;
    return map;
}

Array<uint8_t> AAsset(const String &identifier)
{
    auto it = AssetsRepository().find(identifier.data());

    if(it == AssetsRepository().end()) {
        return Array<uint8_t>();
    }

    return Array<uint8_t>(it->second.first, it->second.first + it->second.second);
}

