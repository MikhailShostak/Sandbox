#pragma once

#include <Foundation>

class AssetManager : public ASingleton<AssetManager>
{
public:
    Map<String, ADelegate<AVariant()>> assets;
};
