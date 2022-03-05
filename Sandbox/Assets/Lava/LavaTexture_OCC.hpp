#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_OCC = { "LavaTexture_OCC", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_OCC.png");
} };
