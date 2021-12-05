#include "AssetsRepository.h"

Map<String, Array<uint8_t>> &getAssets() {
    static Map<String, Array<uint8_t>> data;
    return data;
}

void RegisterStaticAsset(const char *identifier, const std::uint8_t *data, size_t size)
{
    getAssets().insert({ identifier, Array<uint8_t>(data, data + size) });
}

const Array<uint8_t> &getAsset(const String &identifier)
{
    static Array<uint8_t> empty;
    auto it = getAssets().find(identifier);
    return it != getAssets().end() ? it->second : empty;
}
