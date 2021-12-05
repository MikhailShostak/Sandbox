#include "OneStudioTextures.h"

AStaticRun(OneStudioTextures)
{

    AssetManager::getInstance().assets.insert({ "Light", []() { return AVariant(SharedReference<Legacy::Graphics::Texture>(Light)); } });

}
