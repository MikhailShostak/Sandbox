#include "Textures.h"

AStaticRun(Textures)
{
    AssetManager::getInstance().assets.insert({ "Lava_005_MASK", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_MASK)); } });
    AssetManager::getInstance().assets.insert({ "Lava_005_DISP", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_DISP)); } });
    AssetManager::getInstance().assets.insert({ "Lava_005_COLOR", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_COLOR)); } });
    AssetManager::getInstance().assets.insert({ "Lava_005_NORM", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_NORM)); } });
    AssetManager::getInstance().assets.insert({ "Lava_005_OCC", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_OCC)); } });
    AssetManager::getInstance().assets.insert({ "Lava_005_ROUGH", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Lava_005_ROUGH)); } });
}
