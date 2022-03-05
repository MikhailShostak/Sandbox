#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_Mask = { "LavaTexture_Mask", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_MASK.png");
} };
